#ifndef LEVEL_H
#define LEVEL_H

#include "map.h"
#include "page_table.h"

using namespace std;

class PageTable; // declare PageTable data structure
class Map; // declare Map data structure

class Level {
public:
    /* pointer to nextLevel, used at interior nodes */
    Level **nextLevel; // size is allocated at runtime, i.e. new nextLevel[4]

    /* maps vpn to physical PFN, used at leaf nodes */
    Map* mapPtr; // size is allocated at runtime, i.e. new map[4]

    /* tracks the depth of the level */
    int depth;

    /* pointer to the corresponding PageTable */
    PageTable* pageTablePtr;

    Map* lookup_vpn2pfn(Level* levelPtr, unsigned int virtualAddress);

    void insert_vpn2pfn(Level* levelPtr, unsigned int virtualAddress, unsigned int *frameCounterPtr, unsigned int *pfnPtr);

    Level(PageTable* pageTablePtr, int curDepth);

    void get_bytes_used(Level * levelPtr, unsigned int* bytesUsedPtr);
};

#endif