//
// Created by Turner Trowbridge on 2/26/23.
//

#include <iostream>
#include <cstring>

using namespace std;

#ifndef ASSIGNMENT_2_DICTIONARYTREE_H
#define ASSIGNMENT_2_DICTIONARYTREE_H


#define NCHILD 30 /* a-z, ', -, _, terminator of word */
#define APOSTROPHE 39
#define WORD_TERMINATOR '\0'

#define APOSTROPHE_INDEX 26
#define HYPHEN_INDEX 27
#define UNDERSCORE_INDEX 28
#define WORD_TERMINATOR_INDEX 29


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

    int getValueForChar(char c);
};


#endif //ASSIGNMENT_2_DICTIONARYTREE_H
