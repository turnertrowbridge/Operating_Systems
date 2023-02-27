//
// Created by Turner Trowbridge on 2/26/23.
//
#include <fstream>
#include <sys/stat.h>

#ifndef ASSIGNMENT_2_POPULATETREE_H
#define ASSIGNMENT_2_POPULATETREE_H

#define DELIMITERS "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~"


#include "shareddata.h"
#include "dictionarytree.h"



void *populateTree(void *threadarg);
//void populateTree(SHARED_DATA sharedData);





#endif //ASSIGNMENT_2_POPULATETREE_H
