//
// Created by Turner Trowbridge on 1/21/23.
//
#include "dictionary.h"
#include "map"

using namespace std;

class wordHashTable {
public:
    unordered_map<char, int> getWordHashTable() {
           unordered_map<char, int> wordHashTable = {
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
           return wordHashTable;
    };

};

int main(int argc, char **argv) {
    wordHashTable wht;
    unordered_map<char, int> wordHT = wht.getWordHashTable();
//    string letters = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
//    int j = 0;
//    for (int i = 0; i < letters.length(); i += 2) {
//        cout << "{'" << letters[i] << "', " << j << "}, ";
//        cout << "{'" << letters[i + 1] << "', " << j << "}, ";
//        j++;
//    }
    dictNode(wordHT.at('\0'));


};