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
    sem_init(&coinCapacity, 0, slots);
    this->sleepTime = sleepTime;
    this->sharedData = sharedData;
    this->type = type;
}



void TradeService::requestTrade() {
     while (sharedData->requestsProduced < sharedData->totalRequests){
        // produce item
        /* check if there is room for type of coin */
        sem_wait(&coinCapacity); // down

        /* check if there is space in the brokerage */
        sem_wait(&sharedData->availableSlots);

        /* access mutex */
        sem_wait(&sharedData->mutex); // down
        sharedData->tradeRequestQueue.push(type);
        cout << "produced " << type << endl;
        sem_post(&sharedData->mutex); // up

        sem_post(&sharedData->unconsumed); // inform blockchain (consumer)

        usleep(sleepTime); // sleep for sleepTime ms
    }
}



