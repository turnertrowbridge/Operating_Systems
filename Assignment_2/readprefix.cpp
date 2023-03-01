//
// Created by Turner Trowbridge on 2/27/23.
//

#include "readprefix.h"
#include <cstring>

void* readPrefixToQueue(void *threadarg) {
    SHARED_DATA *sharedData;
    sharedData = (SHARED_DATA*) threadarg;


    // busy wait
    while(!sharedData->taskCompleted[SHARED_VOCAB_INDEX]) {
    }

    // create stat struct
    struct stat fileStats;
    string line;    // stores line data

    // reads the third command line argument
    ifstream countstream(sharedData->filePath[SHARED_TEST_INDEX]);
    if (countstream.fail()){
        cout << "Unable to open <<" << sharedData->filePath[SHARED_TEST_INDEX] << ">>" << endl;
        exit(EXIT_FAILURE);
    } else {
        // get num of chars (bytes)
        stat(sharedData->filePath[SHARED_TEST_INDEX], &fileStats);
        sharedData->totalNumOfCharsInFile[SHARED_TEST_INDEX] = fileStats.st_size;

        long wordCount = 0;

        // reads file line by line, gets words and counts total words
        while (getline(countstream, line)) {
            char *line_c = const_cast<char *>(line.c_str());
            char *word = strtok(line_c, sharedData->delimiters);
            {
                while (word != nullptr) {

                    // lock sharedData, push word to queue, and re-lock sharedData
                    pthread_mutex_lock(&sharedData->queue_mutex);
                    sharedData->prefixQueue.push(word);
                    pthread_mutex_unlock(&sharedData->queue_mutex);

                    word = strtok(nullptr, sharedData->delimiters);
                    wordCount++;
                    sharedData->wordCountInFile[SHARED_TEST_INDEX]++;
                }
                sharedData->numOfCharsReadFromFile[SHARED_TEST_INDEX] += line.size() + 1;
            }
        }
        sharedData->taskCompleted[SHARED_TEST_INDEX] = true;
        pthread_exit(0);
    }
};