//
// Created by Turner Trowbridge on 4/13/23.
//

#include "trade_service.h"

void* TradeService::startTradeService(void * arg){
    auto* trade = static_cast<TradeService*>(arg);
    cout << "Started trade service thread" << endl;
    trade->requestTrade();
    pthread_exit(NULL);
}


TradeService::TradeService(int coinCapacity, int sleepTime, SharedData *sharedData, Requests type) {
    this->coinCapacity = coinCapacity;
    this->sleepTime = sleepTime;
    this->sharedData = sharedData;
    this->type = type;
}



void TradeService::requestTrade() {
    sem_init(&sharedData->coinCapacity[type], 0, coinCapacity); // initialize semaphore for max coins allowed at once
    while (sharedData->requestsProduced[TOTAL_COUNTER] < sharedData->totalRequests){
        /* check if there is room for type of coin */
        sem_wait(&sharedData->coinCapacity[type]); // down

        /* check if there is space in the brokerage */
        sem_wait(&sharedData->availableSlots);


        /* access mutex */
        sem_wait(&sharedData->mutex); // lock
        sharedData->tradeRequestQueue.push(type); // add coin to queue
        cout << "Added " << type << endl;

        /* counters */
        sharedData->requestsProduced[type]++; // increase counter for type of coin
        sharedData->requestsProduced[TOTAL_COUNTER]++; // increase total counter of coins produced
        sharedData->requestsInQueue[type]++; // increase counter for type of coin in queue
        sharedData->requestsInQueue[TOTAL_COUNTER]++; // increase total counter of coins in queue


        log_request_added(type, &sharedData->requestsProduced[type],
                          &sharedData->requestsInQueue[type]);

        sem_post(&sharedData->unconsumed); // inform blockchain (consumer) that a new trade can be processed

        sem_post(&sharedData->mutex); // unlock
        /* end mutex access */




        usleep(sleepTime); // sleep for sleepTime ms
    }
}



