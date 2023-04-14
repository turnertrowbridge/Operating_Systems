//
// Created by Turner Trowbridge on 4/13/23.
//

#include "request_service.h"


RequestService::RequestService(int slots, int sleepTime, SharedData *sharedData, Requests type) {
    sem_init(&coinCapacity, 0, slots);
    this->sleepTime = sleepTime;
    this->sharedData = sharedData;
    this->type = type;
}

void* RequestService::startService(void * arg){
    this->requestCoin();
    pthread_exit(NULL);
}

void RequestService::requestCoin() {
    // item type? bitcoin?
     while (sharedData->requestsProduced < sharedData->totalRequests){
        // produce item
        /* check if there is room for type of coin */
        sem_wait(&coinCapacity); // down

        /* check if there is space in the brokerage */
        sem_wait(&sharedData->maxCapacity);

        /* access mutex */
        sem_wait(&sharedData->mutex); // down
        sharedData->tradeRequestQueue.push(type);
        sem_post(&sharedData->mutex); // up

        sem_post(&sharedData->unconsumed); // inform blockchain (consumer)
    }
}


