//
// Created by Turner Trowbridge on 4/13/23.
//

/* Single Programmer Affidavit
 *       I, the undersigned promise that the submitted assignment is my own work. While I was
 *       free to discuss ideas with others, the work contained is my own. I recognize that
 *       should this not be the case; I will be subject to penalties as outlined in the course
 *       syllabus.
 *       Name: Turner Trowbridge
 *       Red ID: 827959204
 */

#include <unistd.h>
#include "stdlib.h"
#include <pthread.h>
#include <semaphore.h>
#include "blockchain.h"
#include "trade_service.h"
#include "queue"
#include "shareddata.h"
#include <iostream>

using namespace std;

#define DEFAULT_NUM_REQUESTS 100
#define DEFAULT_X_TRANSACTION_SPEED 0
#define DEFAULT_Y_TRANSACTION_SPEED 0
#define DEFAULT_BITCOIN_REQUEST_SPEED 0
#define DEFAULT_ETHEREUM_REQUEST_SPEED 0
#define MAX_TRADE_REQUESTS 16
#define MAX_BITCOIN_REQUESTS 5
#define NUM_OF_COINS 2
#define MICROSECONDS_IN_MILLISECONDS 1000



int main(int argc, char **argv) {
    int option; // opt arg checking

    unsigned int totalRequests = DEFAULT_NUM_REQUESTS;
    unsigned int xTransactionSpeed = DEFAULT_X_TRANSACTION_SPEED;  // transaction speed of blockchain X
    unsigned int yTransactionSpeed = DEFAULT_Y_TRANSACTION_SPEED;  // transaction speed of blockchain Y
    unsigned int bitcoinRequestSpeed = DEFAULT_BITCOIN_REQUEST_SPEED;
    unsigned int ethereumRequestSpeed = DEFAULT_ETHEREUM_REQUEST_SPEED;

    while ((option = getopt(argc, argv, "r:x:y:b:e:")) != -1){
        switch (option){
            case 'r':
                totalRequests = atoi(optarg);
                break;
            case 'x':
                xTransactionSpeed = atoi(optarg) * MICROSECONDS_IN_MILLISECONDS;
                break;
            case 'y':
                yTransactionSpeed = atoi(optarg) * MICROSECONDS_IN_MILLISECONDS;
                break;
            case 'b':
                bitcoinRequestSpeed = atoi(optarg) * MICROSECONDS_IN_MILLISECONDS;
                break;
            case 'e':
                ethereumRequestSpeed = atoi(optarg) * MICROSECONDS_IN_MILLISECONDS;
                break;
        }
    }

    /* initialize SharedData and it's values */
    SharedData sharedData;
    sharedData.totalRequests = totalRequests;
    for (int i =0; i < REQUESTS_COUNTERS; i++){
        sharedData.requestsInQueue[i] = 0;
        sharedData.requestsProduced[i] = 0;
        sharedData.requestsConsumed[i] = 0;
    }
    sharedData.requestsConsumedPerBlockchain = new unsigned int *[NUM_BLOCKCHAINS];


    /* initialize the semaphores */
    if (sem_init(&sharedData.lastRequest, 0, 0) != 0){ // barrier to stop main thread from existing too early
        cout << "Error: could not create lastRequest semaphore." << endl;
        exit(EXIT_FAILURE);
    };
    if (sem_init(&sharedData.availableSlots, 0, MAX_TRADE_REQUESTS) != 0){ // slots available for trade queue
        cout << "Error: could not create availableSlots semaphore." << endl;
        exit(EXIT_FAILURE);
    };
    if (sem_init(&sharedData.mutex, 0, 1) != 0){ // mutex for sharedData access
        cout << "Error: could not create mutex semaphore." << endl;
        exit(EXIT_FAILURE);
    };
    if (sem_init(&sharedData.unconsumed, 0, 0) != 0){  // tracks item how many items are ready on queue
        cout << "Error: could not create unconsumed semaphore." << endl;
        exit(EXIT_FAILURE);
    };


    /* initialize the trade services */
    TradeService bitcoinService(MAX_BITCOIN_REQUESTS, bitcoinRequestSpeed, &sharedData, Bitcoin);
    TradeService ethereumService(MAX_TRADE_REQUESTS, ethereumRequestSpeed, &sharedData, Ethereum);

    /* set the entries in the consumption stat 2D array to 0 */
    for (int i = 0; i < NUM_OF_COINS; i++) {
        sharedData.requestsConsumedPerBlockchain[i] = new unsigned int[NUM_OF_COINS];
        for (int j = 0; j < 2; j++) {
            sharedData.requestsConsumedPerBlockchain[i][j]= 0;
        }

    }

    /* create threads for Bitcoin and Ethereum */
    pthread_t bitcoinThread, ethereumThread;
    if (pthread_create(&bitcoinThread, NULL, TradeService::startTradeService, &bitcoinService) != 0){
        cout << "Error: could not create Bitcoin Trade Service thread." << endl;
        exit(EXIT_FAILURE);
    };

    if (pthread_create(&ethereumThread, NULL, TradeService::startTradeService, &ethereumService) != 0){
        cout << "Error: could not create Ethereum Trade Service thread." << endl;
        exit(EXIT_FAILURE);
    };


    /* initialize the blockchains */
    Blockchain blockchainX(xTransactionSpeed, &sharedData, BlockchainX);
    Blockchain blockchainY(yTransactionSpeed, &sharedData, BlockchainY);


    /* create threads for Blockchain X and Y */
    pthread_t blockchainXThread, blockchainYThread;
    if (pthread_create(&blockchainXThread, NULL, Blockchain::startProcessTrade, &blockchainX) != 0){
        cout << "Error: could not create Blockchain X thread." << endl;
        exit(EXIT_FAILURE);
    };
    if (pthread_create(&blockchainYThread, NULL, Blockchain::startProcessTrade, &blockchainY) != 0){
        cout << "Error: could not create Blockchain Y thread." << endl;
        exit(EXIT_FAILURE);
    };

    sem_wait(&sharedData.lastRequest); // barrier to prevent main thread from ending before trades are processed

    log_production_history(sharedData.requestsProduced,
                           sharedData.requestsConsumedPerBlockchain);


    return EXIT_SUCCESS;
}
