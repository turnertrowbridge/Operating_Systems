//
// Created by Turner Trowbridge on 1/21/23.
//
#include "dictionary.h"
#include <fstream>
#include <cstring>

using namespace std;


int main(int argc, char **argv) {
    // check if valid number of arguments
    if (argc == 3){
        dictNode *root = new (dictNode); // create root node and initialize pointers to nullptr

        const char *delimiters = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";  // separates words
        string line;    // stores line data

        // reads the second command line argument
        ifstream addstream(argv[1]);

        if (addstream.fail()){
            cout << "File could not be opened" << endl;
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
            cout << "File could not be opened" << endl;
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