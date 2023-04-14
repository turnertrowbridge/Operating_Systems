//
// Created by Turner Trowbridge on 4/13/23.
//

#ifndef ASSIGNMENT_4_BLOCKCHAIN_H
#define ASSIGNMENT_4_BLOCKCHAIN_H

#define TOTAL_COUNTER 2

#include <semaphore.h>
#include "cryptoexchange.h"
#include "shareddata.h"
#include <queue>
#include <iostream>
#include <unistd.h>
#include "log.h"


void* startProcessTrade(void *arg);


class Blockchain{
    int sleepTime;
    SharedData* sharedData;
    Consumers consumer;

public:
    Blockchain(int sleepTime, SharedData* sharedData, Consumers consumer);
    void processTrade();
};


#endif //ASSIGNMENT_4_BLOCKCHAIN_H
