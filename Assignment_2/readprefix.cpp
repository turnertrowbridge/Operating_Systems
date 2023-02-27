//
// Created by Turner Trowbridge on 2/27/23.
//

#include "readprefix.h"

void* readPrefixToQueue(void *threadarg) {
    SHARED_DATA *sharedData;
    sharedData = (SHARED_DATA*) threadarg;
    string line;    // stores line data

    // reads the third command line argument
    ifstream countstream(sharedData->filePath[SHARED_TEST_INDEX]);

    if (countstream.fail()){
        cout << "Unable to open <<" << sharedData->filePath[SHARED_TEST_INDEX] << ">>" << endl;
        exit(EXIT_FAILURE);
    } else {

        // reads file line by line and counts the # of words in the tree based on prefixes supplied in file
        while (getline(countstream, line)) {
            char *line_c = const_cast<char *>(line.c_str());
            char *word = strtok(line_c, sharedData->delimiters);
            {
                while (word != nullptr) {
                    int count = 0;
                    dictNode *end = sharedData->dictRootNode->findEndingNodeOfAStr(word);
                    end->countWordsStartingFromANode(count);
                    cout << word << " " << count << endl;
                    word = strtok(nullptr, sharedData->delimiters);
                }
            }
        }
    }
    pthread_exit(0);
};