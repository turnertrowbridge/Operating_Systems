#include <iostream>
#include <unistd.h>

using namespace std;

#define DEFAULT_NUM_REQUESTS 100;
#define DEFAULT_X_TRANSACTION_SPEED 0;
#define DEFAULT_Y_TRANSACTION_SPEED 0;
#define DEFAULT_BITCOIN_REQUEST_SPEED 0;
#define DEFAULT_ETHEREUM_REQUEST_SPEED 0;


int main(int argc, char **argv) {
    int option; // opt arg checking

    int numRequests = DEFAULT_NUM_REQUESTS;    // total number of trade requests
    int xTransactionSpeed = DEFAULT_X_TRANSACTION_SPEED;  // transaction speed of blockchain X
    int yTransactionSpeed = DEFAULT_Y_TRANSACTION_SPEED;  // transaction speed of blockchain Y
    int bitcoinRequestSpeed = DEFAULT_BITCOIN_REQUEST_SPEED;
    int ethereumRequestSpeed = DEFAULT_ETHEREUM_REQUEST_SPEED;

    while ((option = getopt(argc, argv, "r:x:y:b:e")) != -1){
        switch (option){
            case 'r':
                numRequests = atoi(optarg);
                break;

        }
    }
    cout << "hI" << endl;
}
