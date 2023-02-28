//
// Created by Turner Trowbridge on 2/27/23.
//

#include "readprefix.h"

void* readPrefixToQueue(void *threadarg) {
    SHARED_DATA *sharedData;
    sharedData = (SHARED_DATA*) threadarg;
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

        // reads file line by line and counts the # of words in the tree based on prefixes supplied in file
        while (getline(countstream, line)) {
            char *line_c = const_cast<char *>(line.c_str());
            char *word = strtok(line_c, sharedData->delimiters);
            {
                pthread_mutex_lock(&sharedData->queue_mutex);  // lock the sharedData structure
                while (word != nullptr) {
                    if (strlen(word) >= sharedData->minNumOfWordsWithAPrefixForPrinting) {
                        sharedData->prefixQueue.push(word);
                    }
                        word = strtok(nullptr, sharedData->delimiters);
                        sharedData->wordCountInFile[SHARED_TEST_INDEX] += 1;
                }
                sharedData->numOfCharsReadFromFile[SHARED_TEST_INDEX] += line.size() + 1;
                pthread_mutex_unlock(&sharedData->queue_mutex);  // unlock the sharedData structure
            }
        }
    }
    sharedData->taskCompleted[SHARED_TEST_INDEX] = true;

    pthread_exit(0);
};