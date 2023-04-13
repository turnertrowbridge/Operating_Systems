#ifndef MAP_H
#define MAP_H


class Map {
public:
  unsigned int physicalAddress;
  bool isValid; // valid bit
  int PFN;

  Map();
};

#endif