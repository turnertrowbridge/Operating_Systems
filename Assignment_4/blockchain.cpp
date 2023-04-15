//
// Created by Turner Trowbridge on 4/13/23.
//

#include "blockchain.h"

void* Blockchain::startProcessTrade(void* arg){
    auto* trade = static_cast<Blockchain*>(arg);
    trade->processTrade();
    pthread_exit(NULL);
}

Blockchain::Blockchain(int sleepTime, SharedData *sharedData, Consumers consumer) {
    this->sleepTime = sleepTime;
    this->sharedData = sharedData;
    this->consumer = consumer;
}

void Blockchain::processTrade() {
    while (sharedData->requestsConsumed[TOTAL_COUNTER] < sharedData->totalRequests){
        /* block until something to consume */
        sem_wait(&sharedData->unconsumed); // down


        /* access mutex */
        sem_wait(&sharedData->mutex); // lock

        Requests type = sharedData->tradeRequestQueue.front(); // store the front of queue
        sharedData->tradeRequestQueue.pop(); // remove front of queue

        /* counters */
        sharedData->requestsConsumed[type]++; // increase counter for type of coin
        sharedData->requestsConsumed[TOTAL_COUNTER]++; // increase total counter for requests consumed
        sharedData->requestsInQueue[type]--; // decrease counter for type of coin in queue
        sharedData->requestsInQueue[TOTAL_COUNTER]--; // decrease total counter of coins in queue
        sharedData->requestConsumedPerBlockchain[consumer][type]++; // increase counter for requests consumed in blockchain


        log_request_removed(consumer, type, sharedData->requestConsumedPerBlockchain[consumer],
                            sharedData->requestsInQueue);


        sem_post(&sharedData->mutex); // unlock
        /* end mutex access */

        sem_post(&sharedData->coinCapacity[type]); // open spot for coin on blockchain
        sem_post(&sharedData->availableSlots); // open a spot on blockchain for new coin



        usleep(sleepTime); // sleep for sleepTime ms, simulate time it would take to process and finish trade
    }
    sem_post(&sharedData->lastRequest);
}
