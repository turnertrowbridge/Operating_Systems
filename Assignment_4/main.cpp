#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "blockchain.h"
#include "trade_service.h"
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

    unsigned int totalRequests = DEFAULT_NUM_REQUESTS;    // total number of trade requests
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
    cout << totalRequests << endl;
//    cout << sharedData.requestsProduced[0] << endl;
    sem_init(&sharedData.lastRequest, 0, 0);

    sem_init(&sharedData.availableSlots, 0, MAX_TRADE_REQUESTS);

    sem_init(&sharedData.mutex, 0, 1);

    sem_init(&sharedData.unconsumed, 0, MAX_TRADE_REQUESTS);


    TradeService bitcoinService(MAX_BITCOIN_REQUESTS, bitcoinRequestSpeed, &sharedData, Bitcoin);
    TradeService ethereumService(MAX_TRADE_REQUESTS, ethereumRequestSpeed, &sharedData, Ethereum);

    // create threads for Bitcoin and Ethereum
    pthread_t bitcoinThread, ethereumThread;
    pthread_create(&bitcoinThread, NULL, startTradeService, &bitcoinService);

    Blockchain blockchainX(xTransactionSpeed, &sharedData, BlockchainX);
    Blockchain blockchainY(yTransactionSpeed, &sharedData, BlockchainY);

    // create threads for Blockchain X and Y
    pthread_t blockchainXThread, blockchainYThread;
    pthread_create(&blockchainXThread, NULL, startProcessTrade, &blockchainX);


    sem_wait(&sharedData.lastRequest);
    cout << "lastrequest done" << endl;

    return EXIT_SUCCESS;
}
