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
#include <unistd.h>
#include "log.h"
#include "pthread.h"


class Blockchain{
    int sleepTime; // simulate time it takes to process trade
    SharedData* sharedData;
    Consumers consumer; // blockchainX, blockChainY

public:
    Blockchain(int sleepTime, SharedData* sharedData, Consumers consumer);
    static void* startProcessTrade(void* arg); // function for thread starting
    void processTrade();
};


#endif //ASSIGNMENT_4_BLOCKCHAIN_H
