#ifndef TLB_H
#define TLB_H
#include "page_table.h"
#include <unordered_map>
#include <cstdint>

#define RECENTLY_ACCESSED_SIZE 8

using namespace std;

class TLB {
  // VPN -> PFN
  unordered_map<unsigned int, unsigned int> tlb_cache;

  // VPN -> Access Time
  unordered_map<unsigned int, unsigned int> LRU_map;
  
  int cacheSize;

  int maxRecentlyAccessedSize;

public:
  explicit TLB(int cacheSize);

  bool lookUpPage(unsigned int vAddr, unsigned int shift);

  void addPage(unsigned int vAddr, unsigned int PFN, int accessTime, unsigned int shift);

  unsigned int getPFN(unsigned int vAddr, unsigned int shift);

  unsigned int findLeastRecentVPN();

  static unsigned int getVPN(unsigned int vAddr, unsigned int shift);

  void printTLB();
};


#endif
