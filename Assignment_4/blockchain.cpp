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

Blockchain::Blockchain(int sleepTime, SharedData *sharedData) {
    this->sleepTime = sleepTime;
    this->sharedData = sharedData;
}

void Blockchain::processTrade() {
    while (sharedData->requestsConsumed < sharedData->totalRequests){
        /* block until something to consume */
        sem_wait(&sharedData->unconsumed); // down

        /* access mutex */
        sem_wait(&sharedData->mutex); // lock
        Requests type = sharedData->tradeRequestQueue.front(); // store the front of queue
        sharedData->tradeRequestQueue.pop(); // remove front of queue
        sharedData->requestsConsumed++; // increase total counter for requests consumed
        cout << "consumed " << type << " # " << sharedData->requestsConsumed << endl;
        sem_post(&sharedData->mutex); // unlock
        /* end mutex access */

        sem_post(&sharedData->availableSlots); // open a spot on blockchain for new coin

        usleep(sleepTime); // sleep for sleepTime ms
    }
    sem_post(&sharedData->lastRequest);
}
