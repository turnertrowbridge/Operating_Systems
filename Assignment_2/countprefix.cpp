//
// Created by Turner Trowbridge on 2/27/23.
//

#include "countprefix.h"

void* dequeuePrefixAndCount(void *threadarg) {
    auto start = std::chrono::steady_clock::now();
    SHARED_DATA *sharedData;
    sharedData = (SHARED_DATA *) threadarg;
    ofstream outputFile("countprefix_output.txt");
//    cout << "taskcompleted for readprefix: " << sharedData->taskCompleted[SHARED_TEST_INDEX] << endl;
    while(sharedData->prefixQueue.size() > 0 || !sharedData->taskCompleted[SHARED_TEST_INDEX]) {
        if(sharedData->prefixQueue.size() > 0) {
            pthread_mutex_lock(&sharedData->queue_mutex); // lock the sharedData structure
            int count = 0;
            string front = sharedData->prefixQueue.front();
            char frontChar[sharedData->prefixQueue.front().size()];
            strcpy(frontChar, sharedData->prefixQueue.front().c_str());
            const char *word = frontChar;
//            cout << word << " , " << strlen(word) << endl;
                sharedData->prefixQueue.pop();
                dictNode *end = sharedData->dictRootNode->findEndingNodeOfAStr(word);
                end->countWordsStartingFromANode(count);
                if (count >= sharedData->minNumOfWordsWithAPrefixForPrinting) {
                    outputFile << word << " " << count << endl;
                }
            pthread_mutex_unlock(&sharedData->queue_mutex); // unlock the sharedData structure
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto runtime_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "\nThread runtime count: " << runtime_ns << " ns" << std::endl;

    outputFile.close();
    pthread_exit(0);
};