#include <iostream>
#include "trie.h"
#include <stdio.h>

int main() {
    
    using namespace std;
    structures::Trie tree;
    
    string filename;
    string word;
    FILE *arq; /* File to read. */

    cin >> filename;  // Input
    arq = fopen(filename.c_str(), "rt");
    char *result;
    char line[100]; // Existe uma maneira de pegar o tamanho?
    if (arq == NULL)  {
        cout << "Error" << endl;
    } else {
        int i = 1;
        int position = 0;
        while (!feof(arq)){
              result = fgets(line, sizeof(line), arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        	  string textVal; // COMO PEGAR FRASE A FRASE DO ARQUIVO ?
        	  for(int j = 0; j < sizeof(line); j++ ) {
        	      cout << line[j];
        	  }
        	  trie.insert(textVal, position, sizeof(textVal))
        	  position = position + sizeof(textVal) + 1;
              i++;
              cout << endl;
        }
        fclose(arq);
    }
    
    // Devemos percorrer o arquivo .dic, para receber todas definições. 
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        } 
        cout << word+" is prefix of 1 words"<< endl;
    }

    return 0;
}
