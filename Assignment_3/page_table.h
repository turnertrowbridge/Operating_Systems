#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include "map.h"
#include "level.h"
#include "TLB.h"
using namespace std;

class Level; // declare level data structure
class Map; // declare Map data structure

class PageTable {
public:

  Level* rootLevelPtr;

  int levelCount;

  unsigned int* bitMaskArr;

  int* bitShiftArr;

  int* entryCountArr;


  PageTable(int levelCount, unsigned int* bitMaskArr, int* bitShiftArr, int* entryCountArr); // default constructor that sets values

  static unsigned int virtualAddressToVPN(unsigned int virtualAddress, unsigned int mask, unsigned int shift);

  Map* lookup_vpn2pfn(unsigned int virtualAddress);

  unsigned int insert_vpn2pfn(unsigned int virtualAddress, unsigned int &frame);

  unsigned int get_bytes_used();
};

#endif