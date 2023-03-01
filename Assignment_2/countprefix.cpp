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
    sharedData->numOfProcessedPrefixes = 0;
    while(sharedData->prefixQueue.size() > 0 || !sharedData->taskCompleted[SHARED_TEST_INDEX]) {
        if(sharedData->prefixQueue.size() > 0) {

            // lock sharedData to access queue
            pthread_mutex_lock(&sharedData->queue_mutex);

            // get prefix from front of queue and copy it to word
            string front = sharedData->prefixQueue.front();
            char frontChar[sharedData->prefixQueue.front().size()];
            strcpy(frontChar, sharedData->prefixQueue.front().c_str());
            const char *prefix = frontChar;
            sharedData->prefixQueue.pop();

            // count number of words that start with prefix
            int count = 0;
            dictNode *end = sharedData->dictRootNode->findEndingNodeOfAStr(prefix);
            end->countWordsStartingFromANode(count);

            // output words to file if the count is greater than or equal to specified minNumOfWordsWithPrefix
            if (count >= sharedData->minNumOfWordsWithAPrefixForPrinting){
                outputFile << prefix << " " << count << endl;
            }

            // count prefixes searched
            sharedData->numOfProcessedPrefixes += 1;

            // unlock sharedData
            pthread_mutex_unlock(&sharedData->queue_mutex);
        }
    }
    outputFile.close();
    pthread_exit(0);
};