//
// Created by Turner Trowbridge on 2/27/23.
//

#include "countprefix.h"

void* dequeuePrefixAndCount(void *threadarg) {
    SHARED_DATA *sharedData;
    sharedData = (SHARED_DATA *) threadarg;
    ofstream outputFile("countprefix_output.txt");
//    cout << "taskcompleted for readprefix: " << sharedData->taskCompleted[SHARED_TEST_INDEX] << endl;
    while(sharedData->prefixQueue.size() > 0 || sharedData->taskCompleted[SHARED_TEST_INDEX] != true) {
        if(sharedData->prefixQueue.size() > 0) {
            pthread_mutex_lock(&sharedData->queue_mutex);
            int count = 0;
            string front = sharedData->prefixQueue.front();
            char frontChar[sharedData->prefixQueue.front().size()];
            strcpy(frontChar, sharedData->prefixQueue.front().c_str());
            const char *word = frontChar;
//            if (sharedData->numOfCharsReadFromFile[SHARED_TEST_INDEX] > 14000) {
//                cout << "popped: " << word << " " << sharedData->numOfCharsReadFromFile[SHARED_TEST_INDEX] << endl;
//            }
            sharedData->prefixQueue.pop();
            dictNode *end = sharedData->dictRootNode->findEndingNodeOfAStr(word);
            end->countWordsStartingFromANode(count);
            if (count >= sharedData->minNumOfWordsWithAPrefixForPrinting){
                outputFile << word << " " << count << endl;
            }
            pthread_mutex_unlock(&sharedData->queue_mutex);
        }
    }

    outputFile.close();
    pthread_exit(0);
};