//! Copyright [2020] <Leonardo Rocha & Nicolas Vanz>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions

namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
// Destrutor
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}
// Construtor
template<typename T>
structures::LinkedList<T>::LinkedList() {
}
// Empty
template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}
// Size
template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
// Insert
template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) throw std::out_of_range("posicao invalida");
    size_++;
    Node *nodo = this->head;
    Node *b;
    for (int i = 0; i < index - 1; i++) {
        nodo = nodo->next();
    }
    b = new Node(data, nodo->next());
    nodo->next(b);
}
// Push back
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node *node = new Node(data, nullptr);
    if (!head) {
        head = node;
    } else {
        Node *fim = end();
        fim->next(node);
    }
    size_++;
}
// Push front
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node *n = new Node(data, head);
    head = n;
    size_++;
}
// At
template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index > size_) throw std::out_of_range("posicao invalida");
    Node *b = head;
    for (int i = 0; i < index; i++) {
        b = b->next();
    }
    return b->data();
}
// Contains
template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node *b = head;
    for (int i = 0; i < size_ - 1; i++) {
        if (b->data() == data) {
            return true;
        } else {
            b = b->next();
        }
    }
    return false;
}
// Find
template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty()) std::out_of_range("lista vazia");
    Node *b = head;
    for (int i = 0; i < size_; i++) {
        if (b->data() == data) {
            return i;
        } else {
            b = b->next();
        }
    }
    return size_;
}
// Clear
template<typename T>
void structures::LinkedList<T>::clear() {
    Node *n1, *n2;
    n1 = head;
    n2 = head;
    while (n2) {
        n2 = n2->next();
        delete n1;
        n1 = n2;
    }
    size_ = 0;
    head = nullptr;
}
// Pop
template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (index >= size_) throw std::out_of_range("posicao invalida");
    if (empty()) throw std::out_of_range("lista vazia");
    Node *ante, *atual = head;
    T retorno;
    for (int i = 0; i < index; i++) {
        ante = atual;
        atual = atual->next();
    }
    ante->next(atual->next());
    retorno = atual->data();
    size_--;
    delete atual;
    return retorno;
}
// Pop front
template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) throw std::out_of_range("lista vazia");
    Node *n = head;
    T t;
    head = head->next();
    t = n->data();
    size_--;
    delete n;
    return t;
}
// Pop back
template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) throw std::out_of_range("lista vazia");
    Node *backup = end();
    if (size_ == 1) {
        return pop_front();
    } else {
        Node *p = head;
        for (int i = 0; i < size_ - 1; i++) {
            p = p->next();
        }
        p->next(nullptr);
        size_--;
    }
    return backup->data();
}
// Remove
template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}
// Insert sorted
template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node *inicio = head;
    int cont = 0;
    while (inicio) {
        if (inicio->data() >= data) {
            break;
        } else {
            inicio = inicio->next();
            cont++;
        }
    }
    if (cont == 0) {
        push_front(data);
    } else {
        insert(data, cont);
    }
}
