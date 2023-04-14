//
// Created by Turner Trowbridge on 4/13/23.
//

#ifndef ASSIGNMENT_4_REQUEST_SERVICE_H
#define ASSIGNMENT_4_REQUEST_SERVICE_H

#include <semaphore.h>
#include "cryptoexchange.h"
#include "shareddata.h"
#include <queue>


class RequestService{
    sem_t coinCapacity; // used for tracking capacity
    int sleepTime;
    SharedData* sharedData;
    Requests type;

public:
    RequestService(int coinCapacity, int sleepTime, SharedData *sharedData, Requests type);
    void* startService(void *arg);
    void requestCoin();
};




#endif //ASSIGNMENT_4_REQUEST_SERVICE_H
