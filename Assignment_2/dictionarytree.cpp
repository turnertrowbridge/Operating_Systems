//
// Created by Turner Trowbridge on 1/21/23.
// Updated 2/26/23
//
#include "dictionarytree.h"


// convert char to its corresponding int
int hashTable::getHashMapValue(char c) {
    return wordHashTable.at((c));
};


// insert new word
bool dictNode::add(const char *wordBeingInserted) {
    // convert char in word to predefined int
    int charIndex = hashTable::getHashMapValue(*wordBeingInserted);

    // if end of string character found, add word terminator and return
    if(charIndex == hashTable::getHashMapValue('\0')){
        if (this->next[charIndex]){
            return false;
        } else {
            return this->next[charIndex] = new dictNode();
        }
    }

    // create new node at charIndex if no node already exists
    if (this->next[charIndex] == nullptr){
        this->next[charIndex] = new dictNode();
    }

    // recursive call to add next char in word
    return this->next[charIndex]->add(++wordBeingInserted);
};


dictNode* dictNode::findEndingNodeOfAStr(const char *strBeingSearched){
    // convert char in word to predefined int
    int charIndex = hashTable::getHashMapValue(*strBeingSearched);

    // return node if end of word
    if (strlen(strBeingSearched) == 0){
        return this;
    }

    // check if word has no more matches
    if (this->next[charIndex] == nullptr){
        return nullptr;
    }

    // recursive call to find next char in word
    return this->next[charIndex]->findEndingNodeOfAStr(++strBeingSearched);
}


void dictNode::countWordsStartingFromANode(int &count) {
    // stops a search from happening if word was not found
    if (this == nullptr){
        return;
    }

    // increase count if word terminator is found
    if (this->next[hashTable::getHashMapValue('\0')]){
        count++;
    }

    // loop through all child nodes to check to see if they have their own child nodes
    for(auto node : this->next){
        // if a child node is found, recurse to search no more can be found
        if (node){
            node->countWordsStartingFromANode(count);
        }
    }
};


const unordered_map<char, int> hashTable::wordHashTable = {
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
        {APOSTROPHE, 26},
        {'-', 27},
        {'_', 28},
        {WORD_TERMINATOR, 29}
};
