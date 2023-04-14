//
// Created by Turner Trowbridge on 4/13/23.
//

#ifndef ASSIGNMENT_4_BLOCKCHAIN_H
#define ASSIGNMENT_4_BLOCKCHAIN_H

#include <semaphore.h>
#include "cryptoexchange.h"
#include "shareddata.h"
#include <queue>


class Blockchain{
    sem_t capacity; // used for tracking capacity
    sem_t bitcoins; // used for tracking current bitcoins
    sem_t ethereum; // used for tracking current ethereum
    sem_t mutex; // used for locking SharedData

    int totalProcessed = 0;
};


#endif //ASSIGNMENT_4_BLOCKCHAIN_H
