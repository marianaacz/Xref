//
//  main.cpp
//  xref
//
//  Created by Mariana on 4/01/19.
//  Copyright © 2019 Mariana. All rights reserved.

// Project:  XML Parser
// Name: Mariana Acosta
// Submitted: 02/21/19
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student,
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class.
/* Reflection:
 This program was challenging but also very doable and simple. I did learn a lot of thins which is also amazing because
 projects don't need to be hard to be able to learn. I think it has a lot of things that will help me in the future.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <map>
#include <iterator>
#include <regex>

using namespace std;

auto compare = [](string keyOne, string keyTwo) {
    string wordOne(keyOne);
    string wordTwo(keyTwo);
    transform(wordOne.begin(), wordOne.end(), wordOne.begin(), ::tolower);
    transform(wordTwo.begin(), wordTwo.end(), wordTwo.begin(), ::tolower);
    if (wordOne == wordTwo)
        return keyOne < keyTwo;
    else
        return wordOne < wordTwo;
};

int buildMap(istream &is, map<string, map<int, int>, decltype(compare)>& wordMap) {
    string line;
   int noLine = 0;
    int width = 0;
    regex x("([a-zA-Z'-]+)");
    
    while (getline(is, line)) {
        if (line == "^Z") {
            break;
        }
        noLine++;
        
        for (auto mymatch = sregex_iterator(begin(line), end(line), x); mymatch != sregex_iterator(); ++mymatch) {
            wordMap[mymatch->str()][noLine]++;
            
            if (sizeof(mymatch->str()) > width)
                width = sizeof(mymatch->str());
        }
    }
    return width;
}

std::regex_iterator<string::iterator> regexIter;
int main(int argc, const char * argv[]) {
    ifstream is;
    ofstream os("xref.txt");
    int biggestWord = 0;
    string data;
    map<string, map<int, int>, decltype(compare)> wordMap(compare);
    
    if (argc > 1) {
        is.open(argv[1]);
        if (is.good()) {
            biggestWord = buildMap(is, wordMap);
        }
        else {
            cout << "Failed open file" << endl;
            return 0;
        }
    }
    else {
        cout << "Type  whatever you want. When finished type ^Z in a new line." << endl;
        biggestWord = buildMap(cin, wordMap);
    }
    
    for (const auto& key : wordMap) {
        int pairs = 0;
        cout  << setw(biggestWord) << left << key.first << " " << ":";
        for (const auto& pair : key.second) {
            if (key.second.size() < 2) {
                os  << pair.first << ":" << pair.second << " ";
            }
            else {
                os  << pair.first << ":" << pair.second << ", ";
            }
            ++pairs;
            if ((pairs % 9) == 0 && pairs != key.second.size()) {
                os  << endl << setw(biggestWord + 3) << right << " ";
            }
        }
        os << endl;
    }
}


