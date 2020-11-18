#include <iostream>
#include "trie.h"

int main() {
    
    using namespace std;

    string filename;
    string word;

    cin >> filename;  // entrada

    cout << filename << endl;  // esta linha deve ser removida
    
    structures::Trie<char> tree;
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        cout << word << endl;
    }

    return 0;
}
