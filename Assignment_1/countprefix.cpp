//
// Created by Turner Trowbridge on 1/21/23.
//
#include "dictionary.h"

using namespace std;


int main(int argc, char **argv) {
//    string letters = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
//    int j = 0;
//    for (int i = 0; i < letters.length(); i += 2) {
//        cout << "{'" << letters[i] << "', " << j << "}, ";
//        cout << "{'" << letters[i + 1] << "', " << j << "}, ";
//        j++;
//    }
    const char* word = "batman";
    dictNode *head = new dictNode();
    cout << head->add("batman") << endl;
    cout << "Found " << head->findEndingNodeOfAStr("bat");
    cout << "hi";

};