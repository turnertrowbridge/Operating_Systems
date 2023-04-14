//
// Created by Turner Trowbridge on 4/13/23.
//

#ifndef ASSIGNMENT_4_SHAREDDATA_H
#define ASSIGNMENT_4_SHAREDDATA_H

#include <semaphore.h>
#include "cryptoexchange.h"
#include "queue"

using namespace std;

#define MAX_CAPACITY 16
#define MAX_BITCOINS 5
#define REQUESTS_COUNTERS 3 // bitcoin, ethereum, total

struct SharedData {

    sem_t availableSlots; // semaphore for slots available for producing coins
    sem_t mutex; // semaphore for sharedData access
    sem_t unconsumed; // semaphore for coins ready to be processed
    sem_t lastRequest;  // semaphore to signal all coins have been processed

    queue<Requests> tradeRequestQueue;  // queue for requests

    unsigned int totalRequests;
    unsigned int requestsInQueue[REQUESTS_COUNTERS] = {0}; // track items in queue
    unsigned int requestsProduced[REQUESTS_COUNTERS] = {0};  // track total requests produced
    unsigned int requestsConsumed[REQUESTS_COUNTERS] = {0};  // track total requests consumed
};


#endif //ASSIGNMENT_4_SHAREDDATA_H
