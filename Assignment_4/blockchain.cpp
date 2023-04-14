//
// Created by Turner Trowbridge on 4/13/23.
//

#include "blockchain.h"

void* startProcessTrade(void* arg){
    auto* trade = static_cast<Blockchain*>(arg);
    cout << "startedProcessTrade thread" << endl;
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
        cout << "QUEUE: " << sharedData->tradeRequestQueue.front() << endl;
        sharedData->tradeRequestQueue.pop(); // remove front of queue

        /* counters */
        sharedData->requestsConsumed[type]++; // increase counter for type of coin
        sharedData->requestsConsumed[TOTAL_COUNTER]++; // increase total counter for requests consumed
        cout << "TYPE " << type << endl;
        sharedData->requestsInQueue[type]--; // decrease counter for type of coin in queue
        sharedData->requestsInQueue[TOTAL_COUNTER]--; // decrease total counter of coins in queue

        log_request_removed(consumer, type, &sharedData->requestsConsumed[type],
                            &sharedData->requestsInQueue[type]);

        sem_post(&sharedData->coinCapacity[type]); // open spot for coin on blockchain
        sem_post(&sharedData->availableSlots); // open a spot on blockchain for new coin

        sem_post(&sharedData->mutex); // unlock
        /* end mutex access */




        usleep(sleepTime); // sleep for sleepTime ms
    }
    sem_post(&sharedData->lastRequest);
}
