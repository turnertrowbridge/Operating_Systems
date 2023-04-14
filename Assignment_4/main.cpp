#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "blockchain.h"
#include "request_service.h"
#include "queue"
#include "shareddata.h"

using namespace std;

#define DEFAULT_NUM_REQUESTS 100
#define DEFAULT_X_TRANSACTION_SPEED 0
#define DEFAULT_Y_TRANSACTION_SPEED 0
#define DEFAULT_BITCOIN_REQUEST_SPEED 0
#define DEFAULT_ETHEREUM_REQUEST_SPEED 0
#define MAX_TRADE_REQUESTS 16
#define MAX_BITCOIN_REQUESTS 5



int main(int argc, char **argv) {
    int option; // opt arg checking

    int totalRequests = DEFAULT_NUM_REQUESTS;    // total number of trade requests
    int xTransactionSpeed = DEFAULT_X_TRANSACTION_SPEED;  // transaction speed of blockchain X
    int yTransactionSpeed = DEFAULT_Y_TRANSACTION_SPEED;  // transaction speed of blockchain Y
    int bitcoinRequestSpeed = DEFAULT_BITCOIN_REQUEST_SPEED;
    int ethereumRequestSpeed = DEFAULT_ETHEREUM_REQUEST_SPEED;

    while ((option = getopt(argc, argv, "r:x:y:b:e")) != -1){
        switch (option){
            case 'r':
                totalRequests = atoi(optarg);
                break;
            case 'x':
                xTransactionSpeed = atoi(optarg);
                break;
            case 'y':
                yTransactionSpeed = atoi(optarg);
                break;
            case 'b':
                bitcoinRequestSpeed = atoi(optarg);
                break;
            case 'e':
                ethereumRequestSpeed = atoi(optarg);
                break;
        }
    }

    SharedData sharedData;
    sharedData.totalRequests = totalRequests;
    sem_init(&sharedData.lastRequest, 0, 1);

    sem_init(&sharedData.maxCapacity, 0, MAX_TRADE_REQUESTS);

    sem_init(&sharedData.mutex, 0, 1);


    RequestService bitcoinService(MAX_BITCOIN_REQUESTS, bitcoinRequestSpeed, &sharedData, Bitcoin);
    RequestService ethereumService(MAX_TRADE_REQUESTS, ethereumRequestSpeed, &sharedData, Ethereum);

    // create threads for Bitcoin and Ethereum
    pthread_t bitcoinThread, ethereumThread;
    pthread_create(&bitcoinThread, NULL,  bitcoinService.startService, &sharedData);

    Blockchain blockchainX;
    Blockchain blockchainY;

    sem_wait(&sharedData.lastRequest);

    return EXIT_SUCCESS;
}