//! Copyright [2022] <Leonardo G de M Brito>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
 public:
    CircularList();
    ~CircularList();

    void clear();  // limpar lista

    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem

    T& at(std::size_t index);  // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const;  // versão const do acesso ao indice

    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover dado específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // lista contém determinado dado?
    std::size_t find(const T& data) const;  // posição de um item na lista

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
        auto it = head -> next();
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

template<typename T>
structures::CircularList<T>::CircularList() {
    head = new Node (0, nullptr);
    size_ = 0;
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    Node* pointer = end();
    Node* New_Node = new Node(data, nullptr);
    if (!empty()) {
        pointer -> next(New_Node);
        New_Node -> next(head);
    } else {
        New_Node -> next(head);
        head -> next(New_Node);
    }
    size_++;
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node* New_Node = new Node(data, nullptr);
    New_Node -> next(head -> next());
    head -> next(New_Node);
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw::std::out_of_range("Index Fora de Alcance");
    } else if (index == 0) {
        return push_front(data);
    }

    Node* pointer = head -> next();
    Node* New_Node = new Node(data, nullptr);
    for (size_t i = 0; i < index-1; i++) {
        pointer = pointer -> next();
    }
    New_Node -> next(pointer -> next());
    pointer -> next(New_Node);
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    if (size_ == 0) {
        return push_front(data);
    }

    Node* pointer = head-> next();
    for (size_t i = 0; i < size_; i++) {
        if (data < pointer -> data()) {
            return insert(data, i);
        }
        pointer = pointer -> next();
    }
    return insert(data, size_);
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (index >= size_) {
        throw::std::out_of_range("Index Fora de Alcance");
    }
    Node* pointer = head -> next();
    for (size_t i = 0; i < index; i++) {
        pointer = pointer -> next();
    }
    return pointer -> data();
}

template<typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    Node* pointer = head -> next();
    for (size_t i = 0; i < index; i++) {
        pointer = pointer -> next();
    }
    return pointer -> data();
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (index >= size_ || empty()) {
        throw::std::out_of_range("Index Fora de Alcance");
    }
    if (index == 0 || size_ == 1) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    }

    Node* aux;
    T aux_val;
    Node* pointer = head -> next();
    for (size_t i = 0; i < index-1; i++) {
        pointer = pointer -> next();
    }
    aux = pointer -> next();
    aux_val = aux -> data();
    pointer -> next(pointer -> next() -> next());
    delete aux;
    size_--;
    return aux_val;
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw::std::out_of_range("Lista Vazia");
    }

    Node* aux;
    T aux_val;

    aux = head -> next();
    aux_val = aux -> data();
    head -> next(aux -> next());

    delete aux;
    size_--;
    return aux_val;
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    if (empty()) {
        throw::std::out_of_range("Lista Vazia");
    } else if (size_ == 1) {
        return pop_front();
    }

    T aux_val;
    Node* pointer = head -> next();
    for (size_t i = 0; i < size_ - 2; i++) {
        pointer = pointer -> next();
    }
    aux_val = pointer -> next() -> data();
    delete pointer -> next();
    pointer -> next(head);
    size_--;
    return aux_val;
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    if (empty()) {
        throw::std::out_of_range("Lista Vazia");
    }

    size_t i = find(data);
    if (i != size_) {
        pop(i);
    }
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    }
    Node* pointer = head -> next();
    for (size_t i = 0; i < size_; i++) {
        if (pointer -> data() == data) {
            return true;
        }
        pointer = pointer -> next();
    }
    return false;
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    Node* pointer = head -> next();
    for (size_t i = 0; i < size_; i++) {
        if (pointer -> data() == data) {
            return i;
        }
        pointer = pointer -> next();
    }
    return size_;
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
