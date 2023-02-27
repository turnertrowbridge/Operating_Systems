/*
 * Single Programmer Affidavit
 * I, the undersigned promise that the submitted assignment is my own work. While I was free to discuss ideas with
 * others, the work contained is my own. I recognize that should this not be the case; I will be subject to penalties
 * as outlined in the course syllabus.
 * Name: Turner Trowbridge Red ID: 827959204
 * Date: 01/25/2023
 */
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <queue>

#include "dictionarytree.h"
#include "shareddata.h"
#include "populatetree.h"

using namespace std;

int main(int argc, char **argv) {
    SHARED_DATA sharedData;  // shared data data structure

    int opt;
    optind = OPT_ARG_START_IDX; // get optional arguments starting at fourth index
    sharedData.numOfProgressMarks = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;  // set by -p, default value of 1
    sharedData.hashmarkInterval = DEFAULT_HASHMARKINTERVAL;  // set by -h, default value of 10
    sharedData.numOfProcessedPrefixes = DEFAULT_NUMOF_MARKS;  // set by -n, default value of 50

    // get optional arguments
    while((opt = getopt(argc, argv, "p:h:n:")) != -1){\

        // make sure there is an argument after last option
        if (optarg == NULL){
            cout << "Error, include argument after option" << endl;
            exit(EXIT_FAILURE);
        }

        int optargInt = atoi(optarg);

        switch (opt){
            case 'p':
                if (optargInt >= MIN_NUMOF_MARKS) {  // min of 10
                    sharedData.numOfProgressMarks = optargInt;
                } else {
                    cout << "Number of progress marks must be a number and at least 10" << endl;
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                if (optargInt > MIN_HASHMARKINTERVAL && optargInt <= MAX_HASHMARKINTERVAL) { // greater than 0 less than or equal to 10
                    sharedData.hashmarkInterval = optargInt;
                } else {
                    cout << "Hash mark interval for progress must be a number, greater than 0,"
                            " and less than or equal to 10";
                    exit(EXIT_FAILURE);
                }
                break;
            case 'n':
                if (optargInt >= DEFAULT_MINNUM_OFWORDS_WITHAPREFIX) {  // greater than or equal to 0
                    sharedData.numOfProcessedPrefixes = optargInt;
                    break;
                } else {
                    cout << "Prefix print count must be a number greater than or equal to 1";
                    exit(EXIT_FAILURE);
                }
            default:
                cout << "Error, check optional arguments." << endl;
                exit(EXIT_FAILURE);
        }
    }


    // get manual arguments
    if (argc > NUMOFFILES){
        sharedData.dictRootNode = new dictNode; // create root node and initialize pointers to nullptr
        sharedData.filePath[SHARED_VOCAB_INDEX] = argv[VOCAB_FILE_INDEX];
        sharedData.filePath[SHARED_TEST_INDEX] = argv[TEST_FILE_INDEX];


        pthread_t populateTreeThread;

        if (pthread_create(&populateTreeThread, NULL, &populateTree, &sharedData)){
            cout << "populateTreeThread error" << endl;
            exit(EXIT_FAILURE);
        }

//        populateTree(sharedData);


        string line;    // stores line data

        // reads the third command line argument
        ifstream countstream(sharedData.filePath[SHARED_TEST_INDEX]);

        if (countstream.fail()){
            cout << "Unable to open <<" << sharedData.filePath[SHARED_TEST_INDEX] << ">>" << endl;
            exit(EXIT_FAILURE);
        } else {

            // reads file line by line and counts the # of words in the tree based on prefixes supplied in file
            while (getline(countstream, line)) {
                char *line_c = const_cast<char *>(line.c_str());
                char *word = strtok(line_c, sharedData.delimiters);
                {
                    while (word != nullptr) {
                        int count = 0;
                        dictNode *end = sharedData.dictRootNode->findEndingNodeOfAStr(word);
                        end->countWordsStartingFromANode(count);
                        cout << word << " " << count << endl;
                        word = strtok(nullptr, sharedData.delimiters);
                    }
                }
            }
        }

    } else{
        cout << "Invalid amount of arguments" << endl;
    }



    exit(EXIT_SUCCESS);
};