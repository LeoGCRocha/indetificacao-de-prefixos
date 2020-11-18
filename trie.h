//! Copyright [2020] <Leonardo Rocha & Nicolas Vanz>
#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>
#include "linked_list.h"
#include <string>

namespace structures {
//! ...
class Trie {
 public:
    //! ...
    Trie();
    //! ...
    ~Trie();
    //! clear
    void clear();
    // insert
    void insert(const T& data);
    // track
    int* insert(char* string);
 private:
    class NoTrie {  // Elemento
     public:
        NoTrie() {
            position = 0;
            extension = 0;
            letter = " "; 
            for (int i = 0; i < 26; i++) {
                this->sons[i] = nullptr;
            }
        }
        
        explicit NoTrie(char letter, unsigned long position, unsigned long extension) {
            this->letter = letter;
            this->position = position;
            this->extension = extension;
            for (int i = 0; i < 26; i++) {
                this->sons[i] = nullptr;
            }
        }

        void insert(std::string *word, unsigned long position, unsigned long end);
        
        char data() {  // getter: data
            return data_;
        }

        const char data() const {  // getter const: data
            return data_;
        }
        
        unsigned long getPosition() {
            return this->position;
        }
        
        unsigned long getExtension() {
            return this->extension;
        }
        
       NoTrie* sons getSons() {
            return this->son;
        }

        char getLetter() {
            return this->letter;
        }
        
        void setPosition(unsigned long p) {
            this->position = p;
        }
        
        void setExtension(unsigned long e) {
            this->extension = e;
        }
        
        void setLetter(char l) {
            this->letter = l;
        }
     private:
        char letter;        
        NoTrie* sons[26];  
        unsigned long  position;
        unsigned long  extension; 
    };

    NoTrie* head;  // top
};

}   // namespace structures
#endif

structures::Trie::Trie() {
    NoTrie *b = new NoTrie;
    head = b;
}

structures::Trie::NoTrie::insert(std::string *word, unsigned long position, unsigned long end) {
    NoTrie *b = head;
    for (int i = 0; i < word.size(); i++ ) {
        int ascii = int(word[i]) - 97;
        if (!b->sons[ascii]) {
            b->sons[ascii] = new Node(word[i], 0, 0);
        } else {
            b = b->sons[ascii];
        }
    } 
    b->setPosition(position);
    b->setEnd(end);
}

structures::Trie::insert(std::string *data, int position) {
    if (head == nullptr) {
        throw std::out_of_range("nullptr error.");
    } else {
        unsigned long posEnd = (unsigned long) data.find("]");
        string *word = data.substr(1, posEnd - 1);
        unsigned long end = ((unsigned long) data.size()) - (posEnd); 
        head->insert(word, position, end); 
    }
}