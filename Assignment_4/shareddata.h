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

struct SharedData {

    sem_t maxCapacity;
    sem_t mutex;
    sem_t unconsumed;
    sem_t lastRequest;
    queue<Requests> tradeRequestQueue;
    int requestsProduced = 0;
    int totalRequests = 0;
};


#endif //ASSIGNMENT_4_SHAREDDATA_H
