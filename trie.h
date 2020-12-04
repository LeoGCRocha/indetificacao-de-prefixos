// Copyright [2020] <Leonardo Rocha & Nicolas Vanz>

#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <cstdint>
#include <stdexcept>
#include <cstring>
#include <string>

namespace structures {
//! Árvore
class Trie {
 public:
    //! Construtor
    Trie();
    //! Destrutor
    ~Trie();
    //! Limpar
    void clear();
    //! Inserir elemento
    void insert(std::string data, int position);
    //! Verifica se a palavra está na árvore
    bool isWord(std::string word);
    //! Dados da palavra
    int *position(std::string word);
    //! Contador de prefixos
    int count_prefix(std::string word);
 private:
    //! Nó da árvore
    class NoTrie {
     public:
        //! Construtor
        NoTrie() {
            position = 0;
            extension = 0;
            letter = '#';
            for (int i = 0; i < 26; i++) {
                this->sons[i] = nullptr;
            }
        }
        //! Construtor explícito
        explicit NoTrie(char letter, unsigned long position, unsigned long extension) {
            this->letter = letter;
            this->position = position;
            this->extension = extension;
            for (int i = 0; i < 26; i++) {
                this->sons[i] = nullptr;
            }
        }
        //! Inserir elemento
        void insert(std::string word, unsigned long position, unsigned long end, NoTrie* head);
        //! Contador de prefixos
        int count_prefix(int &counter, NoTrie *node);
        //! Identificador de bifurcação
        NoTrie *branch_point(std::string word, NoTrie *node);
        //! getter: posição
        unsigned long getPosition() {
            return this->position;
        }
        //! getter: extensão
        unsigned long getExtension() {
            return this->extension;
        }
        //! getter: letra
        char getLetter() {
            return this->letter;
        }
        //! getter: filhos
        NoTrie** getSons() {
            return this->sons;
        }
        //! setter: posição
        void setPosition(unsigned long p) {
            this->position = p;
        }
        //! setter: extenção
        void setExtension(unsigned long e) {
            this->extension = e;
        }
        //! setter: letra
        void setLetter(char l) {
            this->letter = l;
        }

     private:
        char letter;               //!< Letra
        NoTrie* sons[26];          //!< Filhos
        unsigned long  position;   //*< Posição
        unsigned long  extension;  //*< Extensão
    };

    NoTrie* head;  //!< Raiz
};

}   // namespace structures

structures::Trie::~Trie() {
    free(head);
}

structures::Trie::Trie() {
    NoTrie *b = new NoTrie();
    head = b;
}

/*!
 * Verifica se a sequência de caracteres inserida como argumento é uma palavra
 * e se está na árvore
 *
 * \param word Sequência de caracteres a ser verificada
 *
 * \return True se a sequência está na árvore e é uma palavra
 * \return False se a sequência não está na árvore ou não é uma palavra
 */
bool structures::Trie::isWord(std::string word) {
    if (head == nullptr) {
        throw std::out_of_range("empty tree");
    }
    NoTrie *b = head;
    for (char letter : word) {
        int ascii = letter - 'a';
        if (!(b = b->getSons()[ascii])) {
            return false;
        }
    }
    if (b->getExtension() != 0) {
        return true;
    } else {
        return false;
    }
}

/*!
 * Insere uma palavra na árvore
 *
 * \param word Palavra a ser inserida
 * \param position Posição da palavra no arquivo
 * \param end Quantidade de caracteres da palavra e sua definição
 * \param node Raiz da árvore onde será inserida a nova palavra
 *
 * \note Essa é uma função do nó da árvore e deve ser chamada por funções
 * da árvore
 */
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

/*!
 * Insere uma palavra na árvore
 *
 * \param data Linha inteira da palavra e sua definição
 * \param position Posição no arquivo do primeiro caracter de data
 *
 * \note Essa é uma função da árvore e chama a função de inserção específica
 * do nó da árvore
 */
void structures::Trie::insert(std::string data, int position) {
    if (head == nullptr) {
        throw std::out_of_range("empty tree");
    } else {
        unsigned long posEnd = (unsigned long) data.find("]");
        std::string word = data.substr(1, posEnd - 1);
        head->insert(word, position, data.size(), head);
    }
}

/*!
 * Retorna a extensão e posição da palavra no arquivo
 *
 * \param word Palavra a ser analisada
 *
 * \return Um array de duas posições contendo a posição e extensão da palavra
 * (nessa ordem)
 */
int * structures::Trie::position(std::string word) {
    int * array = new int[2];
    if(this->count_prefix(word) >= 1) {
        NoTrie *branch = head;
        for (int i = 0; i < word.size(); i++ ){
            int ascii = word[i] - 'a';
            branch = branch->getSons()[ascii];
        }
        array[0] = branch->getPosition();
        array[1] = branch->getExtension();
    }
    return array;
}

/*!
 * Conta quantas palavras são derivadas do prefixo inserido como argumento
 *
 * \param word Prefixo a ser analisado
 *
 * \return Quantas palavras são derivadas do prefixo
 *
 * \note Essa é uma função da árvore e chama funções auxiliares do nó da árvore
 *
 * \see structures::Trie::NoTrie::branch_point()
 * \see structures::Trie::NoTrie::count_prefix()
 */
int structures::Trie::count_prefix(std::string word) {
    NoTrie *branch = head;
    int counter = 0;
    if (!head) throw std::out_of_range("empty tree");
    branch = head->branch_point(word, head);
    if (branch) return branch->count_prefix(counter, branch);
    return 0;
}

/*!
 * Percorre a árvore de acordo com os caracteres do prefixo inserido
 * como argumento
 *
 * \param word Prefixo a ser analisado
 * \param node Nó a partir do qual árvore deve ser percorrida
 *
 * \return Nó da árvore correspondente ao último caracter do prefixo
 *
 * \note Essa função é do nó da árvore e é chamada por funções da árvore
 * \note Todos as palavras encontradas abaixo do nó retornado são derivadas do
 * prefixo inserido como argumento
 */
structures::Trie::NoTrie *structures::Trie::NoTrie::branch_point(std::string word, NoTrie *node) {
    NoTrie *branch = node;
    for (int i = 0; i < word.size(); i++) {
        if (branch->sons[word[i] - 'a']) branch = branch->sons[word[i] - 'a'];
        else
        return nullptr;
    }
    return branch;
}

/*!
 * Conta quantas palavras válidas há a partir do nó inserido como argumento
 *
 * \param counter Contador de palavras válidas
 * \param node Raiz da subarvore a ser analisada
 *
 * \return Quantas palavras são derivadas do prefixo
 *
 * \note Essa é uma função do nó da árvore e é chamada por funções da árvore
 * \note A raiz da subárvore é calculada pela função branch_point()
 *
 * \see structures::Trie::NoTrie::branch_point()
 */
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

#endif
