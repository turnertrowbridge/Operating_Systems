#include "page_table.h"

PageTable::PageTable(int levelCount, unsigned int* bitMaskArr, int* bitShiftArr, int* entryCountArr) {
  this->levelCount = levelCount;
  this->bitMaskArr = bitMaskArr;
  this->bitShiftArr = bitShiftArr;
  this->entryCountArr = entryCountArr;

  // create rootLevelPtr that stores pageTablePtr, with depth 0, and the entry count stored at index 0
  this->rootLevelPtr = new Level(this, 0);
}


unsigned int PageTable::virtualAddressToVPN(unsigned int virtualAddress, unsigned int mask, unsigned int shift) {
  unsigned int VPN;
  VPN = mask & virtualAddress; // apply mask
  VPN = VPN >> shift; // Shift right into appropriate position
  return VPN;
}

Map* PageTable::lookup_vpn2pfn(unsigned int virtualAddress) {
  // recursive DFS call
  return rootLevelPtr->lookup_vpn2pfn(rootLevelPtr, virtualAddress);
}


unsigned int PageTable::insert_vpn2pfn(unsigned int virtualAddress, unsigned int &frame) {
  // recursive DFS call
  unsigned int PFN;
  rootLevelPtr->insert_vpn2pfn(this->rootLevelPtr, virtualAddress, &frame, &PFN);
  return PFN;
}

unsigned int PageTable::get_bytes_used() {
  unsigned int bytesUsed = 0;
  rootLevelPtr->get_bytes_used(this->rootLevelPtr, &bytesUsed);
  return bytesUsed;
}

