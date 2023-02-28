//
// Created by Turner Trowbridge on 2/27/23.
//

#include <fstream>
#include <sys/stat.h>
#include "shareddata.h"
#include "dictionarytree.h"

#ifndef ASSIGNMENT_2_READPREFIX_H
#define ASSIGNMENT_2_READPREFIX_H
#define DELIMITERS "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~"


void* readPrefixToQueue(void *threadarg);


#endif //ASSIGNMENT_2_READPREFIX_H
