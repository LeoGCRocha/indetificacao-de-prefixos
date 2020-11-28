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
    cin >> filename;  /* Input */
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
        } else {
            int * pos_vector = tree.position(word);
            cout << word + " ";
            int contPrefix = tree.count_prefix(word);
            if (contPrefix == 1) {
                cout << " is prefix of " << contPrefix << " words."  << endl;
                cout << word + " is at (" << pos_vector[0] <<"," << pos_vector[1] << ")" << endl;
            } else if (contPrefix == 0){
                std::cout << "is not prefix" << std::endl;
            } else {
                cout << " is prefix of " << contPrefix << " words."  << endl;
            }
        }
    }
    return 0;
}
