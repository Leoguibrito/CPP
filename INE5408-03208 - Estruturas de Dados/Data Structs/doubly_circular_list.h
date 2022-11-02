//! Copyright [2022] <Leonardo G de M Brito>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;  // primeiro da lista
    std::size_t size_;
};

}  // namespace structures

#endif

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    if (empty()) {
       return push_front(data);
    }

    Node* New_Node = new Node(data);
    New_Node -> prev(head -> prev());
    New_Node -> next(head);
    head -> prev() -> next(New_Node);
    head -> prev(New_Node);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* New_Node = new Node(data);

    if (!empty()) {
        New_Node -> next(head);
        New_Node -> prev(head -> prev());
        head -> prev() -> next(New_Node);
        head -> prev(New_Node);
    } else {
        New_Node -> next(New_Node);
        New_Node -> prev(New_Node);
    }

    head = New_Node;
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::
insert(const T& data, std::size_t index) {
    if (index > size()) {
       throw::std::out_of_range("Index Fora de Alcance");
    } else if (index == 0) {
       return push_front(data);
    } else if (index == size_) {
       return push_back(data);
    }

    Node* New_Node = new Node(data);
    Node* pointer = head;
    if (index > (size()/2)) {
        for (size_t i = size_; i > index; i--) {
            pointer = pointer -> prev();
        }
    } else {
        for (size_t i = 0; i < index; i++) {
            pointer = pointer -> next();
        }
    }

    New_Node -> prev(pointer -> prev());
    New_Node -> next(pointer);

    pointer -> prev() -> next(New_Node);
    pointer -> prev(New_Node);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
       return push_front(data);
    }

    Node* pointer = head;
    for (size_t i = 0; i < size_; i++) {
        if (data < pointer -> data()) {
            return insert(data, i);
        }
        pointer = pointer -> next();
    }

    return push_back(data);
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (index >= size() || empty()) {
        throw::std::out_of_range("Index Fora de Alcance");
    } else if (index == 0 || size_ == 1) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    }

    T pointer_val;
    Node* pointer = head;

    if (index > size()/2) {
        for (size_t i = size_; i > index; i--) {
            pointer = pointer -> prev();
        }
    } else {
        for (size_t i = 0; i < index; i++) {
            pointer = pointer -> next();
        }
    }
    pointer -> prev() -> next(pointer -> next());
    pointer -> next() -> prev(pointer -> prev());
    pointer_val = pointer -> data();

    delete pointer;
    size_--;
    return pointer_val;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
       throw::std::out_of_range("Lista Vazia");
    } else if (size() == 1) {
        return pop_front();
    }

    Node* pointer = head -> prev();
    T pointer_val = pointer -> data();
    pointer -> prev() -> next(head);
    head -> prev(pointer -> prev());

    size_--;
    delete pointer;
    return pointer_val;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
       throw::std::out_of_range("Lista Vazia");
    }

    Node* pointer = head;
    T pointer_val = pointer -> data();

    if (size() > 1) {
        pointer -> next() -> prev(pointer -> prev());
        pointer -> prev() -> next(pointer -> next());
        head = pointer -> next();
    } else if (size() == 1) {
        head = nullptr;
    }

    size_--;
    delete pointer;
    return pointer_val;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
	if (empty()) {
         throw std::out_of_range("Lista Vazia");
    }

	Node* pointer = head;
	for (size_t i = 0; i < size(); i++) {
		if (pointer -> data() == data) {
			pointer -> prev() -> next(pointer -> next());
			pointer -> next() -> prev(pointer -> prev());
			delete pointer;
			size_--;
		    break;
		}
		pointer = pointer -> next();
	}
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    if (size_ == 0) {
       return true;
    }
    return false;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    if (empty()) {
         throw std::out_of_range("Lista Vazia");
    }
    Node* pointer = head;
    for (size_t i = 0; i < size_; i++) {
        if (pointer -> data() == data) {
            return true;
        }
        pointer = pointer -> next();
    }
    return false;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (empty() || index > size_-1) {
        throw std::out_of_range("Index Fora de Alcance");
    }

    Node* pointer = head;
    for (size_t i = 0; i < index; i++) {
        pointer = pointer -> next();
    }
    return pointer -> data();
}

template<typename T>  // Igual o de Cima??
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
	if (empty() || index > size_-1) {
        throw std::out_of_range("Index Fora de Alcance");
    }

    Node* pointer = head;
    for (int i = 0; (std::size_t)i < index; i++) {
        pointer = pointer -> next();
    }
    return pointer -> data();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* pointer = head;
    for (size_t i = 0; i < size_; i++) {
        if (pointer -> data() == data) {
            return i;
        }
        pointer = pointer -> next();
    }
    return size_;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
