//
// Created by Turner Trowbridge on 4/13/23.
//

#ifndef ASSIGNMENT_4_SHAREDDATA_H
#define ASSIGNMENT_4_SHAREDDATA_H

#include <semaphore.h>
#include "cryptoexchange.h"
#include "queue"

using namespace std;


#define UNIQUE_COIN_TYPES 2
#define REQUESTS_COUNTERS 3 // bitcoin, ethereum, total
#define NUM_BLOCKCHAINS 2


struct SharedData {

    sem_t availableSlots; // semaphore for slots available for producing coins
    sem_t mutex; // semaphore for sharedData access
    sem_t unconsumed; // semaphore for coins ready to be processed
    sem_t lastRequest;  // semaphore to signal all coins have been processed

    sem_t coinCapacity[UNIQUE_COIN_TYPES]; // create multiple semaphores for the different unique coins

    queue<Requests> tradeRequestQueue;  // queue for requests

    unsigned int totalRequests;
    unsigned int requestsInQueue[REQUESTS_COUNTERS]; // track items in queue
    unsigned int requestsProduced[REQUESTS_COUNTERS];  // track total requests produced
    unsigned int requestsConsumed[REQUESTS_COUNTERS];  // track total requests consumed
    unsigned int **requestsConsumedPerBlockchain; // 2D array to store stats
};


#endif //ASSIGNMENT_4_SHAREDDATA_H
