//
// Created by Turner Trowbridge on 4/13/23.
//

#ifndef ASSIGNMENT_4_TRADE_REQUEST_H
#define ASSIGNMENT_4_TRADE_REQUEST_H

#include <semaphore.h>
#include "cryptoexchange.h"
#include "shareddata.h"
#include <queue>
#include <unistd.h>
#include <iostream>

void* startTradeService(void *arg);

class TradeService{
    sem_t coinCapacity; // used for tracking capacity
    int sleepTime;
    SharedData* sharedData;
    Requests type;

public:
    TradeService(int coinCapacity, int sleepTime, SharedData *sharedData, Requests type);
    void requestTrade();
};




#endif //ASSIGNMENT_4_TRADE_REQUEST_H
