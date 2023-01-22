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
    int val;
    dictNode *next[NCHILD] = {};

public:
    explicit dictNode(int val) {
        this->val = val;
    }

};


#endif //ASSIGNMENT_1_DICTIONARY_H
