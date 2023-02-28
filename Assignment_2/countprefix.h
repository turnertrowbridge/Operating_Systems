//
// Created by Turner Trowbridge on 2/27/23.
//

#include <fstream>
#include <sys/stat.h>
#include "shareddata.h"
#include "dictionarytree.h"

#ifndef ASSIGNMENT_2_COUNTPREFIX_H
#define ASSIGNMENT_2_COUNTPREFIX_H

#define OUTPUTFILE_NAME "countprefix_output.txt"


void* dequeuePrefixAndCount(void *threadarg);


#endif //ASSIGNMENT_2_COUNTPREFIX_H
