#include <iostream>
#include "trie.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

int main() {
    
    using namespace std;
    structures::Trie tree;
    
    string filename;
    string word;
    FILE *arq; /* File to read. */

    cin >> filename;  // Input
    
    ifstream file(filename.c_str());
    if (file.is_open()){
    	string line;
    	int position = 0;
    	while (getline(file, line)){
        	tree.insert(line, position);
    	    position = position + sizeof(line) + 1;
    	}
    }
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        } 
        cout << word+" is prefix of 1 words"<< endl;
    }

    return 0;
}
