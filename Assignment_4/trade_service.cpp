//
// Created by Turner Trowbridge on 4/13/23.
//

#include "trade_service.h"

void* startTradeService(void * arg){
    auto* trade = static_cast<TradeService*>(arg);
    cout << "Started trade service thread" << endl;
    trade->requestTrade();
    pthread_exit(NULL);
}


TradeService::TradeService(int slots, int sleepTime, SharedData *sharedData, Requests type) {
//    sem_init(&coinCapacity, 0, slots);
    this->sleepTime = sleepTime;
    this->sharedData = sharedData;
    this->type = type;
}



void TradeService::requestTrade() {
     while (sharedData->requestsProduced < sharedData->totalRequests){
        // produce item
        /* check if there is room for type of coin */
//        sem_wait(&coinCapacity); // down

        /* check if there is space in the brokerage */
        sem_wait(&sharedData->availableSlots);

        /* access mutex */
        sem_wait(&sharedData->mutex); // lock
        sharedData->tradeRequestQueue.push(type); // add coin to queue
        sharedData->requestsProduced++; // increase total counter of coins produced
        cout << "produced " << type << " # " << sharedData->requestsProduced << endl;
        sem_post(&sharedData->mutex); // unlock
        /* end mutex access */


        sem_post(&sharedData->unconsumed); // inform blockchain (consumer) that a new trade can be processed

        usleep(sleepTime); // sleep for sleepTime ms
    }
}



