//
// Created by Turner Trowbridge on 2/26/23.
//

#include "populatetree.h"

void populatetree::populateTree(SHARED_DATA sharedData) {
    // reads the second command line argument
    string line;    // stores line data
    struct stat byteCount;

    ifstream addstream(sharedData.filePath[SHARED_VOCAB_INDEX]);

    if (addstream.fail()){
        cout << "Unable to open <<" << sharedData.filePath[SHARED_VOCAB_INDEX] << ">>" << endl;
        exit(EXIT_FAILURE);
    } else {
        // get num of bytes
        stat(sharedData.filePath[SHARED_VOCAB_INDEX], &byteCount);
        sharedData.totalNumOfCharsInFile[SHARED_VOCAB_INDEX] = byteCount.st_size;
        cout << sharedData.totalNumOfCharsInFile[SHARED_VOCAB_INDEX] << endl;

        // reads file line by line and adds to tree word by word
        while (getline(addstream, line)) {
            char *line_c = const_cast<char *>(line.c_str());
            char *word = strtok(line_c, sharedData.delimiters);
            {
                while (word != nullptr) {
                    sharedData.dictRootNode->add(word);
                    word = strtok(nullptr, sharedData.delimiters);
                }
            }
        }
    }
}
