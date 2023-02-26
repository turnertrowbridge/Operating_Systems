/*
 * Single Programmer Affidavit
 * I the undersigned promise that the submitted assignment is my own work. While I was free to discuss ideas with
 * others, the work contained is my own. I recognize that should this not be the case; I will be subject to penalties
 * as outlined in the course syllabus.
 * Name: Turner Trowbridge Red ID: 827959204
 * Date: 01/25/2023
 */
#include "dictionary.h"
#include <fstream>
#include <cstring>
#include <unistd.h>

using namespace std;


int main(int argc, char **argv) {
    int opt;
    optind = 3;
    int numOfPrefixes = 1; // default value of 1
    int numOfHashMarkSpaces = 10; // default value of 10
    int numOfProgressMarks = 50; // default value of 50

    while((opt = getopt(argc, argv, "p:h:n:")) != -1){
        switch (opt){
            case 'p':
                numOfProgressMarks = atoi(optarg);
                cout << "num of progress marks: " << optarg << endl;
                break;
            case 'h':
                numOfHashMarkSpaces = atoi(optarg);
                cout << "num of hash marks spaces: " << optarg << endl;
                break;
            case 'n':
                numOfPrefixes = atoi(optarg);
                cout << "prefix count: " << optarg << endl;
                break;
            default:
                cout << "Error, check optional arguments" << endl;
                exit(EXIT_FAILURE);
        }
    }


    // check if valid number of arguments
    if (argc > 2){
        dictNode *root = new (dictNode); // create root node and initialize pointers to nullptr

        const char *delimiters = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";  // separates words
        string line;    // stores line data

        // reads the second command line argument
        ifstream addstream(argv[1]);

        if (addstream.fail()){
            cout << "Unable to open <<" << argv[1] << ">>" << endl;
            exit(EXIT_FAILURE);
        } else {

            // reads file line by line and adds to tree word by word
            while (getline(addstream, line)) {
                char *line_c = const_cast<char *>(line.c_str());
                char *word = strtok(line_c, delimiters);
                {
                    while (word != nullptr) {
                        root->add(word);
                        word = strtok(nullptr, delimiters);
                    }
                }
            }
        }

        // reads the third command line argument
        ifstream countstream(argv[2]);

        if (countstream.fail()){
            cout << "Unable to open <<" << argv[2] << ">>" << endl;
            exit(EXIT_FAILURE);
        } else {

            // reads file line by line and counts the # of words in the tree based on prefixes supplied in file
            while (getline(countstream, line)) {
                char *line_c = const_cast<char *>(line.c_str());
                char *word = strtok(line_c, delimiters);
                {
                    while (word != nullptr) {
                        int count = 0;
                        dictNode *end = root->findEndingNodeOfAStr(word);
                        end->countWordsStartingFromANode(count);
                        cout << word << " " << count << endl;
                        word = strtok(nullptr, delimiters);
                    }
                }
            }
        }

    } else{
        cout << "Invalid amount of arguments" << endl;
    }
};