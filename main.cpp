#include <iostream>
#include "trie.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
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
    	    position += sizeof(line) + 1;
    	}
    }
    file.close();
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        cout << tree.count_prefix(word) << endl;
    }

    return 0;
}
