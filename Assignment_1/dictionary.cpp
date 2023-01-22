//
// Created by Turner Trowbridge on 1/21/23.
//

#include "dictionary.h"

// convert char to it's corresponding int
int dictionary::getHashMapValue(char c) {
    return wordHashTable.at((c));
};

// insert new word
bool dictionary::add(const char *wordBeingInserted) {

};

// find node that ends in the prefix
dictNode* dictionary::findEndingNodeOfAStr(const char *strBeingSearched) {

};

// count number of words in a tree that start from a node
void dictionary::countWordsStartingFromANode(int &count) {

};
