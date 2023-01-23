//
// Created by Turner Trowbridge on 1/21/23.
//
#include "dictionary.h"
#include <fstream>
#include <cstring>
#include <exception>

using namespace std;


int main(int argc, char **argv) {
//    const char* word = "batman";
//    dictNode *head = new dictNode();
//    head->add("batman");
//    head->add("batdog");
//    head->add("batdude");
//    head->add("bat");
//    head->add("mike");
//    head->add("tyson");
//    dictNode* bat = head->findEndingNodeOfAStr("bat");
//    int count = 0;
//    bat->countWordsStartingFromANode(count);
//    cout << "bat " << count << endl;

    if (argc == 3){
        const char *delimiters = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";
        ifstream dictstream(argv[1]);
        string line;


        while(getline(dictstream, line)){
            char* line_c = const_cast<char*>(line.c_str());
            char* word = strtok(line_c, delimiters);
            {
                while (word != nullptr){
                    try{
                        int count = 0;
                        dictNode *head;
                        head->add(word);
                        dictNode *end = head->findEndingNodeOfAStr(word);
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