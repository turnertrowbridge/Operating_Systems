#include <unordered_map>
#include <iostream>
#include <string>
//
// Created by Turner Trowbridge on 1/21/23.
//
using namespace std;

#ifndef ASSIGNMENT_1_DICTIONARY_H
#define ASSIGNMENT_1_DICTIONARY_H
#define NCHILD 30 /* a-z, ', -, _, terminator of word */


class dictNode {
private:
    // children
    dictNode *next[NCHILD];
//    dictNode* findEndRecursively(dictNode *node, const char *strBeingSearched);
public:
    // default constructor
    dictNode(){
        for(int i = 0; i < NCHILD; i++){
            this->next[i] = nullptr;
        }
    };

    // add new word
    bool add(const char *wordBeingInserted = nullptr);

    // find end node
    dictNode *findEndingNodeOfAStr(const char *strBeingSearched);

};

class dictionary {
private:
    static unordered_map<char, int> wordHashTable;

public:

    static int getHashMapValue(char c);
    void countWordsStartingFromANode(int &count);
};


#endif //ASSIGNMENT_1_DICTIONARY_H
