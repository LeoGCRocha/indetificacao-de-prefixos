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
    void insert(std::string data, int position);
    //
    int count_prefix(std::string word);
    void display(void);
 private:
    class NoTrie {  // Elemento
     public:
        NoTrie() {
            position = 0;
            extension = 0;
            letter = '#';
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

        void insert(std::string word, unsigned long position, unsigned long end, NoTrie* head);

        int count_prefix(int &counter, NoTrie *node);

        NoTrie *branch_point(std::string word, NoTrie *node);

        void display(NoTrie* node, std::string word);

        unsigned long getPosition() {
            return this->position;
        }

        unsigned long getExtension() {
            return this->extension;
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

    NoTrie* head;
};

}   // namespace structures

structures::Trie::~Trie() {
    free(head);
}

structures::Trie::Trie() {
    NoTrie *b = new NoTrie();
    head = b;
}

void structures::Trie::NoTrie::insert(std::string word, unsigned long position, unsigned long end, NoTrie* node) {
    NoTrie *b = node;
    int ascii;
    for (int i = 0; i < word.size(); i++ ) {
        ascii = word[i] - 'a';
        if (!b->sons[ascii]) {
            b->sons[ascii] = new NoTrie(word[i], 0, 0);
        }
        b = b->sons[ascii];
    }
    b->setPosition(position);
    b->setExtension(end);
}

void structures::Trie::insert(std::string data, int position) {
    if (head == nullptr) {
        throw std::out_of_range("empty tree");
    } else {
        unsigned long posEnd = (unsigned long) data.find("]");
        std::string word = data.substr(1, posEnd - 1);
        unsigned long end = ((unsigned long) data.size()) - (posEnd);
        head->insert(word, position, end, head);
    }
}

int structures::Trie::count_prefix(std::string word) {
    NoTrie *branch = head;
    int counter = 0;
    if (!head) throw std::out_of_range("empty tree");
    branch = head->branch_point(word, head);
    if (branch) return branch->count_prefix(counter, branch);
    std::cout << "no branch point" << std::endl;
    return 0;
}

structures::Trie::NoTrie *structures::Trie::NoTrie::branch_point(std::string word, NoTrie *node) {
    NoTrie *branch = node;
    for (int i = 0; i < word.size(); i++) {
        if (branch->sons[word[i] - 'a']) branch = branch->sons[word[i] - 'a'];
        else
        return nullptr;
    }
    return branch;
}

int structures::Trie::NoTrie::count_prefix(int &counter, NoTrie *node) {
    if (!node) throw std::invalid_argument("invalid node specified");
    if (node->extension) counter++;
    for (int i = 0; i < 26; i++) {
        if (node->sons[i]) {
            count_prefix(counter, node->sons[i]);
        }
    }
    return counter;
}


void structures::Trie::display(void) {
    if (!head) throw std::out_of_range("empty tree");
    std::string word = "\0";
    head->display(head, word);
}

void structures::Trie::NoTrie::display(NoTrie* node, std::string word) {
    bool flag = false;
    for (int i = 0; i < 26; i++) {
        if (!flag) {
            word.append(&node->letter);
            flag = true;
        }
        if (node->sons[i]) {
            display(node->sons[i], word);
        }
    }
    if (node->extension) {
        std::cout << word << std::endl;
    }
}

#endif
