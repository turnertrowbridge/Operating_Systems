#include "level.h"

Level::Level(PageTable* pageTablePtr, int curDepth){
  this->pageTablePtr = pageTablePtr;
  this->nextLevel= nullptr;
  this->depth = curDepth;
  this->mapPtr = nullptr;

  int entryCount = pageTablePtr->entryCountArr[depth];

  if (curDepth == pageTablePtr->levelCount) { // check if at leaf level
    // create leaf node to hold map objects
    this->mapPtr = new Map[entryCount];
  } else {
    // make interior level node that holds level objects
    this->nextLevel = new Level*[entryCount];
    // add level objects to interior node
  }
};


Map* Level::lookup_vpn2pfn(Level* levelPtr, unsigned int virtualAddress) {
  unsigned int VPN = PageTable::virtualAddressToVPN(virtualAddress,
                                                    pageTablePtr->bitMaskArr[levelPtr->depth],
                                                    pageTablePtr->bitShiftArr[levelPtr->depth]);
  // check if leaf node
  if (levelPtr->mapPtr) {
    return levelPtr->mapPtr;
  } else {
    // check if a nextLevel exists
    if (levelPtr->nextLevel) {
      if (levelPtr->nextLevel[VPN]) {
        // traverse to next level
        return lookup_vpn2pfn(levelPtr->nextLevel[VPN], virtualAddress);
      }
    }
  }
  // no next level found
  return nullptr;
};


void Level::insert_vpn2pfn(Level* levelPtr, unsigned int virtualAddress, unsigned int *frameCounterPtr, unsigned int *pfnPtr){
  int curDepth = levelPtr->depth;
  unsigned int VPN = PageTable::virtualAddressToVPN(virtualAddress,
                                                    pageTablePtr->bitMaskArr[curDepth],
                                                    pageTablePtr->bitShiftArr[curDepth]);
  // check if at leaf node
  if (levelPtr->mapPtr) {
    // check if PFN has been set
    if (!int(levelPtr->mapPtr->isValid)){
      levelPtr->mapPtr->PFN = *frameCounterPtr; // set the map PFN
      levelPtr->mapPtr->isValid = true; // says that the PFN number has been set for this VPN
      *frameCounterPtr +=1;
    }
    levelPtr->mapPtr[VPN].PFN = levelPtr->mapPtr->PFN; // store PFN
    levelPtr->mapPtr[VPN].physicalAddress = (levelPtr->mapPtr[VPN].PFN << pageTablePtr->bitShiftArr[curDepth - 1]) | VPN; // store VPN at physicalAddress
    *pfnPtr = levelPtr->mapPtr[VPN].PFN;  // used to retrieve PFN associated with recent entry to store in cache
    levelPtr->mapPtr[VPN].isValid = true;

  } else {
    // create new level at VPN index if no new level exists at VPN index
    if (!levelPtr->nextLevel[VPN]) {
      levelPtr->nextLevel[VPN] = new Level(pageTablePtr, curDepth + 1);
    }
    // traverse into next level at VPN index
    insert_vpn2pfn(levelPtr->nextLevel[VPN], virtualAddress, frameCounterPtr, pfnPtr);
  }
};

void Level::get_bytes_used(Level *levelPtr, unsigned int* bytesUsedPtr) {
  int entryCount = pageTablePtr->entryCountArr[levelPtr->depth];

  // check if at leaf node
  if (levelPtr->mapPtr) {
    *bytesUsedPtr += entryCount * sizeof(Map);
  } else {
    // check if a nextLevel exists
    if (levelPtr->nextLevel) {
      *bytesUsedPtr += entryCount * sizeof(Level); // count all level objects stored in interior nodes
      // traverse all next levels if non-null
      for (int i = 0; i < entryCount; i++) {
        if (levelPtr->nextLevel[i]) {
          get_bytes_used(levelPtr->nextLevel[i], bytesUsedPtr);
        }
      }
    }
  }
};