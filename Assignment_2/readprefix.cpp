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
                while (word != nullptr) {
                    int count = 0;
                    dictNode *end = sharedData->dictRootNode->findEndingNodeOfAStr(word);
                    end->countWordsStartingFromANode(count);
//                    cout << word << " " << count << endl;
                    word = strtok(nullptr, sharedData->delimiters);
                    sharedData->wordCountInFile[SHARED_TEST_INDEX] += 1;
                }
                sharedData->numOfCharsReadFromFile[SHARED_TEST_INDEX] += line.size() + 1;
            }
        }
    }

//    cout << "There are " << sharedData->wordCountInFile[SHARED_TEST_INDEX]
//         << " words in " << sharedData->filePath[SHARED_TEST_INDEX] << endl;
//
//    cout << "Read " << sharedData->numOfCharsReadFromFile[SHARED_TEST_INDEX]
//         << " chars out of " << sharedData->totalNumOfCharsInFile[SHARED_TEST_INDEX] << endl;
    pthread_exit(0);
};