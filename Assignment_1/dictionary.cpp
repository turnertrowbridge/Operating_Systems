//
// Created by Turner Trowbridge on 1/21/23.
//

#include "dictionary.h"

// convert char to it's corresponding int
int dictionary::getHashMapValue(char c) {
    return wordHashTable.at((c));
};

// insert new word
bool dictNode::add(const char *wordBeingInserted) {
    // convert char in word to predefined int
    int charIndex = dictionary::getHashMapValue(*wordBeingInserted);

    // if end of string character found, add word terminator and return
    if(charIndex == 29){
        this->next[charIndex] = new dictNode();
        return true;
    }

    // create new node at charIndex if no node already exists
    if (this->next[charIndex] == nullptr){
        this->next[charIndex] = new dictNode();
    }

    // recursive call to add next char in word
    this->next[charIndex]->add(++wordBeingInserted);
    return true;
};


// find node that ends in the prefix
//dictNode* dictNode::findEndingNodeOfAStr(const char *strBeingSearched) {
//    if (strlen(strBeingSearched) == 0){
//        return nullptr;
//    }
//    int charIndex = dictionary::getHashMapValue(*strBeingSearched);
//
//    dictNode* node = node->next[charIndex];
//    findEndingNodeOfAStr(++strBeingSearched);
//    return node;
//};

//dictNode* dictNode::findEndRecursively(dictNode *node, const char *strBeingSearched){
//    int charIndex = dictionary::getHashMapValue(*strBeingSearched);
//
//    // if end of string character found, add word terminator and return
//    if(charIndex == 29){
//        return node;
//    }
//
//    // check if word has no more matches
//    if (node->next[charIndex] == nullptr){
//        return nullptr;
//    }
//
//    // recursive call to find next char in word
//    findEndRecursively(node->next[charIndex], ++strBeingSearched);
//    return node;
//};




// count number of words in a tree that start from a node
void dictionary::countWordsStartingFromANode(int &count) {

};


unordered_map<char, int> dictionary::wordHashTable = {
        {'A', 0},
        {'a', 0},
        {'B', 1},
        {'b', 1},
        {'C', 2},
        {'c', 2},
        {'D', 3},
        {'d', 3},
        {'E', 4},
        {'e', 4},
        {'F', 5},
        {'f', 5},
        {'G', 6},
        {'g', 6},
        {'H', 7},
        {'h', 7},
        {'I', 8},
        {'i', 8},
        {'J', 9},
        {'j', 9},
        {'K', 10},
        {'k', 10},
        {'L', 11},
        {'l', 11},
        {'M', 12},
        {'m', 12},
        {'N', 13},
        {'n', 13},
        {'O', 14},
        {'o', 14},
        {'P', 15},
        {'p', 15},
        {'Q', 16},
        {'q', 16},
        {'R', 17},
        {'r', 17},
        {'S', 18},
        {'s', 18},
        {'T', 19},
        {'t', 19},
        {'U', 20},
        {'u', 20},
        {'V', 21},
        {'v', 21},
        {'W', 22},
        {'w', 22},
        {'X', 23},
        {'x', 23},
        {'Y', 24},
        {'y', 24},
        {'Z', 25},
        {'z', 25},
        {',', 26},
        {'-', 27},
        {'_', 28},
        {'\0', 29}
};