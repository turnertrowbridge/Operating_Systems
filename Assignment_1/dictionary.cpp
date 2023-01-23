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
    if(dictionary::isInHashMap(*wordBeingInserted)){
        int charIndex = dictionary::getHashMapValue(*wordBeingInserted);



    // if end of string character found, add word terminator and return
    if(charIndex == 29){
        if (this->next[charIndex]){
            return false;
        } else {
        this->next[charIndex] = new dictNode();
        return true;
        }
    }

    // create new node at charIndex if no node already exists
    if (this->next[charIndex] == nullptr){
        this->next[charIndex] = new dictNode();
    }

    // recursive call to add next char in word
    this->next[charIndex]->add(++wordBeingInserted);
    return true;

    } else {
        return false;
    }
};

dictNode* dictNode::findEndingNodeOfAStr(const char *strBeingSearched){
    // convert char in word to predefined int
    int charIndex = dictionary::getHashMapValue(*strBeingSearched);

    // bug if word isn't in tree
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
    // checks to stop a search from happening if word was not found
    if (this == nullptr){
        return;
    }

    // count if word terminator is found
    if (this->next[29]){
        count++;
    }

    for(auto node : this->next){
        if (node){
            node->countWordsStartingFromANode(count);
        }
    }
};

void dictionary::setWordHashTable() {
    string letters = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

    for (int i = 0, j = 0; i < letters.length() && j < letters.length() + 1; i += 2, j++) {
        cout << "{'" << letters[i] << "', " << j << "}, ";
        cout << "{'" << letters[i + 1] << "', " << j << "}, ";
        wordHashTable.insert({letters.at(i), j});
        wordHashTable.insert({letters.at(i + 1), j});
    }
};

bool dictionary::isInHashMap(char c) {
    if (wordHashTable.find(c) == wordHashTable.end()){
        return false;
    }
    return true;
}
