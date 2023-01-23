//
// Created by Turner Trowbridge on 1/21/23.
//
#include "dictionary.h"
#include <fstream>
#include <cstring>
#include <exception>

using namespace std;


int main(int argc, char **argv) {

    if (argc == 3){
        const char *delimiters = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";
        dictNode *root = new dictNode();
        ifstream dictstream(argv[1]);
        string line;
        while(getline(dictstream, line)){
            char* line_c = const_cast<char*>(line.c_str());
            char* word = strtok(line_c, delimiters);
            {
                while (word != nullptr){
                    try{
                        int count = 0;
                        root->add(word);
                    }catch(exception e) {
                    }
                    word = strtok(nullptr, delimiters);
                }
            }
        }

        ifstream readstream(argv[2]);
        string line1;
        while(getline(readstream, line1)){
            char* line_c = const_cast<char*>(line1.c_str());
            char* word = strtok(line_c, delimiters);
            {
                while (word != nullptr){
                    try{
                        int count = 0;
                        dictNode *end = root->findEndingNodeOfAStr(word);
                        end->countWordsStartingFromANode(count);
                        cout << word << " " << count << endl;
                    }catch(exception e) {
                    }
                    word = strtok(nullptr, delimiters);
                }
            }
        }





    } else{
        cout << "Invalid amount of arguments" << endl;
    }
};