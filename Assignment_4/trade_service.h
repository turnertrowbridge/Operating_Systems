//
// Created by Turner Trowbridge on 4/13/23.
//

#ifndef ASSIGNMENT_4_TRADE_REQUEST_H
#define ASSIGNMENT_4_TRADE_REQUEST_H

#define TOTAL_COUNTER 2

#include <semaphore.h>
#include "cryptoexchange.h"
#include "shareddata.h"
#include <queue>
#include <unistd.h>
#include <iostream>
#include "log.h"

void* startTradeService(void *arg);

class TradeService{
    int coinCapacity; // total coins of a type allowed on blockchain at a time
    int sleepTime;  // simulate time it takes for a trade to complete
    SharedData* sharedData;
    Requests type;  // bitcoin, ethereum

public:
    TradeService(int coinCapacity, int sleepTime, SharedData *sharedData, Requests type);
    void requestTrade();
    static void* startTradeService(void * arg);
};




#endif //ASSIGNMENT_4_TRADE_REQUEST_H
