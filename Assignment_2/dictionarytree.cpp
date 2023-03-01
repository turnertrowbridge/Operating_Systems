//
// Created by Turner Trowbridge on 1/21/23.
// Updated 2/26/23
//
#include "dictionarytree.h"


// insert new word
bool dictNode::add(const char *wordBeingInserted) {
    // convert char in word to predefined int
    int charIndex = getValueForChar(*wordBeingInserted);

    // if end of string character found, add word terminator and return
    if(charIndex == getValueForChar(WORD_TERMINATOR)){
        if (this->next[charIndex]){
            return false;
        } else {
            return (this->next[charIndex] = new dictNode());
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
    int charIndex = getValueForChar(*strBeingSearched);
    if (*strBeingSearched == WORD_TERMINATOR){
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
    if (this->next[WORD_TERMINATOR_INDEX]){
        count++;
    }

    // loop through all child nodes to check to see if they have their own child nodes
    for(dictNode* node : this->next){
        // if a child node is found, recurse to search no more can be found
        if (node){
            node->countWordsStartingFromANode(count);
        }
    }
};

int dictNode::getValueForChar(char c){
    // gets the value for a char between 0 and 30
    if(c >= 'a' && c <= 'z'){
        return c - 'a';
    } else if (c >= 'A' && c <= 'Z'){
        return c - 'A';
    }else if (c == APOSTROPHE){
        return APOSTROPHE_INDEX;
    }else if (c == '-') {
        return HYPHEN_INDEX;
    }else if(c == '_'){
        return UNDERSCORE_INDEX;
    }else if (c == WORD_TERMINATOR){
        return WORD_TERMINATOR_INDEX;
    }else {
        cout << "Error at char " << c << endl;
        exit(EXIT_FAILURE);
    }
};
