/*
 * Single Programmer Affidavit
 * I, the undersigned promise that the submitted assignment is my own work. While I was free to discuss ideas with
 * others, the work contained is my own. I recognize that should this not be the case; I will be subject to penalties
 * as outlined in the course syllabus.
 * Name: Turner Trowbridge Red ID: 827959204
 * Date: 01/25/2023
 */
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <cstring>

#include "dictionarytree.h"
#include "shareddata.h"
#include "populatetree.h"
#include "readprefix.h"
#include "countprefix.h"

using namespace std;

void printProgressBar(double readChars, double totalChars, int *numMarksPrinted, int numReqMarks, int hashInterval){
    // calculate progress
    double percentage = readChars / totalChars;

    int numMarks = percentage * numReqMarks;
    int marksNeeded = numMarks - *numMarksPrinted;
    for (int i = 0; i < marksNeeded; i++, (*numMarksPrinted)++){
        if ((*numMarksPrinted + 1) % hashInterval == 0){
            cout << "#";
            fflush(stdout);
        }else {
            cout << "-";
            fflush(stdout);
        }
    }
}

int main(int argc, char **argv) {
    SHARED_DATA sharedData;  // shared data data structure

    int opt;
    optind = OPT_ARG_START_IDX; // get optional arguments starting at fourth index
    sharedData.numOfProgressMarks = DEFAULT_NUMOF_MARKS;  // set by -p, default value of 50
    sharedData.hashmarkInterval = DEFAULT_HASHMARKINTERVAL;  // set by -h, default value of 10
    sharedData.minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;  // set by -n, default value of 1

    // get optional arguments
    while((opt = getopt(argc, argv, "p:h:n:")) != -1){\

        // make sure there is an argument after last option
        if (optarg == NULL){
            cout << "Error, include argument after option" << endl;
            exit(EXIT_FAILURE);
        }

        int optargInt = atoi(optarg); // convert string to integer

        // set optional arguments values if specified
        switch (opt){
            case 'p':
                if (optargInt >= MIN_NUMOF_MARKS) {  // min of 10
                    sharedData.numOfProgressMarks = optargInt;
                } else {
                    cout << "Number of progress marks must be a number and at least 10" << endl;
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                if (optargInt > MIN_HASHMARKINTERVAL && optargInt <= MAX_HASHMARKINTERVAL) { // greater than 0 less than or equal to 10
                    sharedData.hashmarkInterval = optargInt;
                } else {
                    cout << "Hash mark interval for progress must be a number, greater than 0,"
                            " and less than or equal to 10";
                    exit(EXIT_FAILURE);
                }
                break;
            case 'n':
                if (optargInt >= DEFAULT_MINNUM_OFWORDS_WITHAPREFIX) {  // greater than or equal to 1
                    sharedData.minNumOfWordsWithAPrefixForPrinting = optargInt;
                    break;
                } else {
                    cout << "Prefix print count must be a number greater than or equal to 1";
                    exit(EXIT_FAILURE);
                }
            default:
                cout << "Error, check optional arguments." << endl;
                exit(EXIT_FAILURE);
        }
    }


    // get manual arguments
    if (argc > NUMOFFILES){
        sharedData.dictRootNode = new dictNode; // create root node and initialize pointers to nullptr

        // set file path names
        sharedData.filePath[SHARED_VOCAB_INDEX] = argv[VOCAB_FILE_INDEX];
        sharedData.filePath[SHARED_TEST_INDEX] = argv[TEST_FILE_INDEX];

        // set tasksCompleted to false
        sharedData.taskCompleted[SHARED_TEST_INDEX] = false;
        sharedData.taskCompleted[SHARED_VOCAB_INDEX] = false;

        // initialize threads and mutex
        pthread_t populateTreeThread;
        pthread_t readPrefixThread;
        pthread_t countPrefixThread;
        pthread_mutex_init(&sharedData.queue_mutex, NULL);


        // create a thread for populateTree
        if (pthread_create(&populateTreeThread, NULL, &populateTree, &sharedData)){
            cout << "populateTreeThread error" << endl;
            exit(EXIT_FAILURE);
        }


        // print progress bar for reading and counting prefix
        int numMarksPrinted = 0;    // counts num of progressMarks printed so far
        while (numMarksPrinted != sharedData.numOfProgressMarks) {
            printProgressBar((double)sharedData.numOfCharsReadFromFile[SHARED_VOCAB_INDEX],
                             (double)sharedData.totalNumOfCharsInFile[SHARED_VOCAB_INDEX],
                             &numMarksPrinted, sharedData.numOfProgressMarks,
                             sharedData.hashmarkInterval);
        }

        // join populateTreeThread back to main, then create other threads
        if (pthread_join(populateTreeThread, NULL)) {
            cout << "populateTreeThread join error" << endl;
        }else{
            // print out the amount of words in first file
            cout << "\nThere are " << sharedData.wordCountInFile[SHARED_VOCAB_INDEX]
                 << " words in " << sharedData.filePath[SHARED_VOCAB_INDEX] << "." << endl;

            // create readPrefixThread
            if (pthread_create(&readPrefixThread, NULL, &readPrefixToQueue, &sharedData)){
                    cout << "readPrefixThread error" << endl;
                    exit(EXIT_FAILURE);
            }

            // create countPrefixThread
            if (pthread_create(&countPrefixThread, NULL, &dequeuePrefixAndCount, &sharedData)){
                cout << "readPrefixThread error" << endl;
                exit(EXIT_FAILURE);
            }

            // print progress bar for reading and counting prefix
            numMarksPrinted = 0; // counts num of progressMarks printed so far
            while (numMarksPrinted != sharedData.numOfProgressMarks) {
                printProgressBar((double) sharedData.numOfCharsReadFromFile[SHARED_TEST_INDEX],
                                 (double) sharedData.totalNumOfCharsInFile[SHARED_TEST_INDEX],
                                 &numMarksPrinted, sharedData.numOfProgressMarks,
                                 sharedData.hashmarkInterval);
            }

            // join readPrefixThread back to main
            if(pthread_join(readPrefixThread, NULL)){
                cout << "readPrefixThread join error" << endl;
            }

            // join countPrefixThread back to main
            if(pthread_join(countPrefixThread, NULL)){
                cout << "countPrefixThread join error" << endl;
            }

            // print out the amount of words in second file
            cout << "\nThere are " << sharedData.wordCountInFile[SHARED_TEST_INDEX]
                 << " words in " << sharedData.filePath[SHARED_TEST_INDEX] <<  "." << endl;
        }
    } else{
        cout << "Invalid amount of arguments" << endl;
    }

    exit(EXIT_SUCCESS);
};