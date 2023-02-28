//
// Created by Turner Trowbridge on 2/27/23.
//

#include "countprefix.h"

void* dequeuePrefixAndCount(void *threadarg) {
    // access sharedData struct
    SHARED_DATA *sharedData;
    sharedData = (SHARED_DATA *) threadarg;

    // set outPutFile
    ofstream outputFile(OUTPUTFILE_NAME);
    while(sharedData->prefixQueue.size() > 0 || sharedData->taskCompleted[SHARED_TEST_INDEX] != true) {
        if(sharedData->prefixQueue.size() > 0) {

            // lock sharedData to access queue
            pthread_mutex_lock(&sharedData->queue_mutex);

            // get prefix from front of queue and copy it to word
            string front = sharedData->prefixQueue.front();
            char frontChar[sharedData->prefixQueue.front().size()];
            strcpy(frontChar, sharedData->prefixQueue.front().c_str());
            const char *word = frontChar;
            sharedData->prefixQueue.pop();

            // count number of words with word
            int count = 0;
            dictNode *end = sharedData->dictRootNode->findEndingNodeOfAStr(word);
            end->countWordsStartingFromANode(count);

            // output words to file if the count is greater than or equal to specified minNumOfWordsWithPrefix
            if (count >= sharedData->minNumOfWordsWithAPrefixForPrinting){
                outputFile << word << " " << count << endl;
            }

            // unlock sharedData
            pthread_mutex_unlock(&sharedData->queue_mutex);
        }
    }
    outputFile.close();
    pthread_exit(0);
};