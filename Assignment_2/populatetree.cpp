//
// Created by Turner Trowbridge on 2/26/23.
//

#include "populatetree.h"


void* populateTree(void *threadarg) {
    SHARED_DATA *sharedData;
    sharedData = (SHARED_DATA*) threadarg;
    struct stat fileStats;
    string line;    // stores line data

    ifstream addstream(sharedData->filePath[SHARED_VOCAB_INDEX]);

    if (addstream.fail()){
        cout << "Unable to open <<" << sharedData->filePath[SHARED_VOCAB_INDEX] << ">>" << endl;
        exit(EXIT_FAILURE);
    } else {
        // get num of chars (bytes)
        stat(sharedData->filePath[SHARED_VOCAB_INDEX], &fileStats);
        sharedData->totalNumOfCharsInFile[SHARED_VOCAB_INDEX] = fileStats.st_size;


        // reads file line by line and adds to tree word by word
        while (getline(addstream, line)) {
            char *line_c = const_cast<char *>(line.c_str());
            char *word = strtok(line_c, sharedData->delimiters);
            while (word != nullptr) {
                sharedData->dictRootNode->add(word);
                word = strtok(nullptr, sharedData->delimiters);
            }
        }
    }

    sharedData->donePopulatingTree = true;
    pthread_exit(0);
}
