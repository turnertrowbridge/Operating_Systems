//
// Created by Turner Trowbridge on 1/21/23.
//
#include <unordered_map>
#include <iostream>
#include <cstring>

using namespace std;

#ifndef ASSIGNMENT_1_DICTIONARY_H
#define ASSIGNMENT_1_DICTIONARY_H
#define NCHILD 30 /* a-z, ', -, _, terminator of word */
#define APOSTROPHE 39
#define WORD_TERMINATOR '\0'



class dictNode {
private:
    // children
    dictNode *next[NCHILD];
public:
    // add new word
    bool add(const char *wordBeingInserted = nullptr);

    // find end node
    dictNode *findEndingNodeOfAStr(const char *strBeingSearched);

    // get all the number of words that branch off from a node
    void countWordsStartingFromANode(int &count);
};

class hashTable {
private:
     static const unordered_map<char, int> wordHashTable;
public:
    static int getHashMapValue(char c);
};

#endif //ASSIGNMENT_1_DICTIONARY_H
