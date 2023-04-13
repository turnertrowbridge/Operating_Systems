#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdint>

#include "print_helpers.h"
#include "vaddr_tracereader.h"
#include "page_table.h"

using namespace std;

#define VIRTUAL_ADDRESS_SPACE 32
#define MAX_TOTAL_BITS_ACROSS_LEVELS 28
#define MIN_BITS_PER_LEVEL 1

unsigned int getBitMask(int bitShift, unsigned int bitsPerLevel);


int main(int argc, char **argv) {
  
  int option;
  int numOfMemoryAccess = INT32_MAX;
  int cacheCapacity = 0;
  string printModeType;
  bool pmtIsSpecified = false;

  // flags for print mode
  bool summary_flag = false;
  bool levelbitmasks_flag = false;
  bool va2pa_flag = false;
  bool va2pa_tlb_ptwalk_flag = false;
  bool vpn2pfn_flag = false;
  bool offset_flag = false;

  /* optional arguments */
  while ((option = getopt(argc, argv, "n:c:p:")) != -1) {
    switch (option) {
      case 'n':
        numOfMemoryAccess = atoi(optarg);
        if (numOfMemoryAccess < 0) {
          cerr << "Number of memory accesses must be a number, greater than or equal to 0" << endl;
          return (EXIT_FAILURE);
        }
        break;

      case 'c':
        cacheCapacity = atoi(optarg);
        if (cacheCapacity < 0) {
          cerr << "Cache capacity must be a number, greater than or equal to 0" << endl;
          return EXIT_FAILURE;
        }
        break;

      case 'p':
        printModeType = optarg;
        pmtIsSpecified = true;
        if (printModeType == "levelbitmasks") {
          levelbitmasks_flag = true;
        } else if (printModeType == "va2pa") {
          va2pa_flag = true;
        } else if (printModeType == "va2pa_tlb_ptwalk") {
          va2pa_tlb_ptwalk_flag = true;
        } else if (printModeType == "vpn2pfn") {
          vpn2pfn_flag = true;
        } else if (printModeType == "offset") {
          offset_flag = true;
        } else if (printModeType == "summary") {
          summary_flag = true;
        } else {
          cerr << "Incorrect print mode type" << endl;
          return EXIT_FAILURE;
        }
        break;
    }
  }

  // default print mode
  if (!pmtIsSpecified) {
    summary_flag = true;
  }


  /* mandatory arguments */
  int idx = optind;
  int levelCount = 0;
  unsigned int* pageSizeArr = nullptr;
  const char *traceFilePath;
  unsigned int totalBitsAcrossLevels = 0;
  int offset = VIRTUAL_ADDRESS_SPACE;
  int* bitShiftArr;
  unsigned int* bitMaskArr;
  int* entryCountArr;

  if (idx < argc) {
    traceFilePath = argv[idx];
    int i = 0;
    levelCount = argc - idx - 1;
    pageSizeArr = new unsigned int[levelCount];


    // allocate levelCount + 1 to store numbers related to offset
    bitShiftArr = new int[levelCount + 1];
    bitMaskArr = new unsigned int[levelCount + 1];
    entryCountArr = new int[levelCount + 1];

    while (idx < argc - 1) {
      idx++;
      pageSizeArr[i] = atoi(argv[idx]);
      i++;
    }
  }

  if (levelCount == 0){
    cerr << "No levels inputted" << endl; // added extra error checking
    return EXIT_FAILURE;
  }


  for (int i = 0; i < levelCount; i++) {
    if (pageSizeArr[i] < MIN_BITS_PER_LEVEL) {  // pointer won't be null since it's size = levelCount
      cerr << "Level " << i << " page table must be at least "<< MIN_BITS_PER_LEVEL << " bit" << endl;
      return EXIT_FAILURE;
    }

    totalBitsAcrossLevels += pageSizeArr[i];
    offset -= pageSizeArr[i];
    bitShiftArr[i] = offset;

    // end program if totalBitsAcrossLevels is too high
    if (totalBitsAcrossLevels > MAX_TOTAL_BITS_ACROSS_LEVELS) {
      cerr << "Too many bits used in page tables" << endl;
      return EXIT_FAILURE;
    }
  }
  bitShiftArr[levelCount] = 0; // store zero at the last index for offset access

  // set bit mask
  for (int i = 0; i < levelCount; i++) {
    bitMaskArr[i] = getBitMask(bitShiftArr[i], pageSizeArr[i]);
  }
  // store the offset mask at the last index
  bitMaskArr[levelCount] = getBitMask(bitShiftArr[levelCount], offset);


  /* entry count */
  for (int i = 0; i < levelCount; i++){
    entryCountArr[i] = pow(2, pageSizeArr[i]);
  }
  entryCountArr[levelCount] = pow(2, offset);

  /* Program Implementation */
  FILE* trace_file = fopen(traceFilePath, "r");
  if (!trace_file) {
    cerr << "Error: Unable to open <<" << traceFilePath << ">>" << endl;
    return EXIT_FAILURE;
  }


  /* PageTable creation */
  PageTable* pageTable = new PageTable(levelCount, bitMaskArr, bitShiftArr, entryCountArr);
  TLB tlb = TLB(cacheCapacity);

  p2AddrTr mtrace;
  unsigned int vAddr;
  unsigned int *VPN = new unsigned int[levelCount + 1];
  unsigned int PFN;
  unsigned int pageAddress;
  unsigned int frameCounter = 0;
  int counterOfAccesses = 0;
  int counterOfPageHits = 0;
  int counterOfTLBHits = 0;


  if (levelbitmasks_flag) {
    report_levelbitmasks(levelCount, bitMaskArr);
  }

  while ((NextAddress(trace_file, &mtrace))) {
    if (counterOfAccesses >= numOfMemoryAccess) {
      break;
    }
    vAddr = mtrace.addr;
    bool tlbHit = false;
    bool pHit = false;

    // TLB hit
    if(tlb.lookUpPage(vAddr, bitShiftArr[levelCount - 1]) && cacheCapacity > 0){  // if tlb is set
      PFN = tlb.getPFN(vAddr, bitShiftArr[levelCount - 1]); // get physicalAddress from TLB
      tlb.addPage(vAddr, PFN, counterOfAccesses, offset);
      counterOfTLBHits++;
      tlbHit = true;
    }
    // TLB miss and Page Table hit
    else if(pageTable->lookup_vpn2pfn(vAddr)){
      PFN = pageTable->insert_vpn2pfn(vAddr, frameCounter); // store VPN and return physicalAddress
      counterOfPageHits++;
      pHit = true;
      if (cacheCapacity > 0) { // if tlb is set
        tlb.addPage(vAddr, PFN, counterOfAccesses, offset);
      }
    }
    // TLB Miss and Page Table miss
    else if(!pageTable->lookup_vpn2pfn(vAddr)) {
      PFN = pageTable->insert_vpn2pfn(vAddr, frameCounter);  // store VPN and return physicalAddress
      if (cacheCapacity > 0) {  // if tlb is set
        tlb.addPage(vAddr, PFN, counterOfAccesses, offset);
      }
    }


    // store VPN used on each page
    for (int i = 0; i <= levelCount; i ++){
      VPN[i] = PageTable::virtualAddressToVPN(vAddr, bitMaskArr[i],bitShiftArr[i]);
    }

    // store the PA
    if(tlbHit){
      pageAddress = (PFN << bitShiftArr[levelCount - 1]) | VPN[levelCount]; // append offset to physicalAddress
    } else {
      pageAddress = pageTable->lookup_vpn2pfn(vAddr)[VPN[levelCount]].physicalAddress; // get physicalAddress
    }

    if (va2pa_flag) {
      report_virtualAddr2physicalAddr(vAddr,
                                      pageAddress);
    } else if (va2pa_tlb_ptwalk_flag) {
       report_va2pa_TLB_PTwalk(vAddr, pageAddress, tlbHit, pHit);
    } else if (vpn2pfn_flag) {
      report_pagetable_map(levelCount, VPN, pageTable->lookup_vpn2pfn(vAddr)[VPN[levelCount]].PFN);
    } else if (offset_flag) {
      hexnum(PageTable::virtualAddressToVPN(vAddr, bitMaskArr[levelCount], bitShiftArr[levelCount]));
    }

    // increase addresses processed
    counterOfAccesses += 1;
  }


  if (summary_flag) {
    report_summary(entryCountArr[levelCount], counterOfTLBHits,
                   counterOfPageHits, counterOfAccesses,
                   frameCounter, pageTable->get_bytes_used());
  }


  return EXIT_SUCCESS;
}

/* functions */
unsigned int getBitMask(int bitShift, unsigned int bitsPerLevel) {
  /* bit masking */
  unsigned int mask = 1;
  for (int b = 1; b < bitsPerLevel; b++) // bitShift + bitsPerLevel = start of bits we want to mask
  {
    mask = mask << 1; // bitwise and
    mask = mask | 1; // bitwise or
  }
  mask = mask << bitShift; // Shift left into appropriate position

  return mask;
};