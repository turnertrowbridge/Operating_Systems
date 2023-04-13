#include "TLB.h"


TLB::TLB(int cacheSize) {
  this->cacheSize = cacheSize;
  if (cacheSize < RECENTLY_ACCESSED_SIZE){
    this->maxRecentlyAccessedSize = cacheSize;
  } else{
    this->maxRecentlyAccessedSize = RECENTLY_ACCESSED_SIZE;
  }
};

unsigned int TLB::getVPN(unsigned int vAddr, unsigned int shift){
  return vAddr >> shift; // shift out the offset
};


bool TLB::lookUpPage(unsigned int vAddr, unsigned int shift) {
  unsigned int VPN = getVPN(vAddr, shift); // shift out the offset
  return tlb_cache.count(VPN);
};


void TLB::addPage(unsigned int vAddr, unsigned int PFN, int accessTime, unsigned int shift) {
    unsigned int VPN = getVPN(vAddr, shift); // shift out the offset
    if (LRU_map.count(VPN)) {
      LRU_map[VPN] = accessTime; // updates accessTime of VPN if it's already tracked

    } else {
      unsigned int leastRecentVPN = findLeastRecentVPN();
      // check if recently accessed entries is less than maxRecentlyAccessedSize
      if (LRU_map.size() < maxRecentlyAccessedSize) {
        LRU_map[VPN] = accessTime; // track access time of VPN
        tlb_cache[VPN] = PFN; // add to cache
      } else {
        // need to evict page from LRU_map
        LRU_map.erase(leastRecentVPN); // evict least recent VPN from recently accessed
        LRU_map[VPN] = accessTime; // track new VPN

        // evict leastAccessed VPN if cache is at capacity
        if (tlb_cache.size() >= cacheSize) {
          tlb_cache.erase(leastRecentVPN); // remove the leastAccessed from tlb_cache
        }
        tlb_cache[VPN] = PFN; // add new VPN to cache
      }
    }
};

unsigned int TLB::findLeastRecentVPN(){
  unsigned int leastRecentVPN;
  unsigned int leastRecentTime = INT32_MAX;  // set the least recent time to the highest possible int

  // find the least recently accessed
  for (auto entry: LRU_map) {
    if (entry.second < leastRecentTime) { // compare the accessTimes
      leastRecentVPN = entry.first; // store VPN name
      leastRecentTime = entry.second;  // store VPN access time
    }
  }
  return leastRecentVPN;
};


unsigned int TLB::getPFN(unsigned int vAddr, unsigned int shift) {
  unsigned int VPN = getVPN(vAddr, shift); // shift out the offset
  return tlb_cache[VPN]; // return PFN
};

