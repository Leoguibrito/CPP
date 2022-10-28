//! Copyright [2022] <Leonardo G de M Brito>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
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
        Node(const T& data);
        Node(const T& data, Node* next);
        Node(const T& data, Node* prev, Node* next);

        T& data();
        const T& data() const;

        Node* prev();
        const Node* prev() const;

        void prev(Node* node);

        Node* next();
        const Node* next() const;

        void next(Node* node);
     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
   head = nullptr;
   size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
   clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
   while (!empty()) {
      pop_front();
   }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
   if (empty()) {
      return push_front(data);
   }

   Node* New_Node = new Node(data, nullptr);
   New_Node -> next(nullptr)
   New_Node -> prev(tail);

   tail -> next(New_Node);
   tail = New_Node;
   size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
   Node* New_Node = new Node(data, nullptr);
   New_Node -> next(head);
   New_Node -> prev(nullptr);
   
   if (size() > 0) {
      tail = head;
      tail -> prev(New_Node);
   } else {
      tail = New_Node;
   }
   head = New_Node;
   size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
   if (index > size()) {
      throw::std::out_of_range("Index Fora de Alcance");
   } else if (index == 0) {
      return push_front(data);
   } else if (index == size_ - 1) {
      return push_back(data);
   }

   Node* New_Node = new Node(data, nullptr);
   Node* pointer;
   if (index > (size()/2) {
      pointer = tail;
      for (size_t i = size_ - 1; i > index; i--) {
         pointer = pointer -> prev();
      }
      New_Node -> prev(pointer -> prev());
      pointer -> prev() -> next(New_Node);
      New_Node -> next(pointer);
      pointer -> prev(New_Node);
   
   } else {
      pointer = head;
      for (size_t i = 0; i < index - 1; i++) {
         pointer = pointer -> next();
      }
      New_Node -> prev(pointer);
      pointer -> next() -> prev(New_Node) 
      New_Node -> next(pointer -> next());
      pointer -> next(New_Node);
   }
   size_++;
}
   
template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
   if (empty()) {
      return push_front(data);
   }

   Node* New_Node = new Node(data, nullptr);
   size_t i;
      Node* pointer = head;
      for (i = 0; i < size_; i++) {
         if (data < pointer -> data()) {
               return insert(data, i);
         }
         pointer = pointer -> next();
   } 
   return insert(data, i);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
   if (index >= size_ || empty()) {
      throw::std::out_of_range("Index Fora de Alcance");
   } else if (index == 0 || size_ == 1) {
      pop_front();
   } else if (index == size_ - 1) {
      pop_back();
   }

   T pointer_val;
   Node* pointer = head;

   if (index > (size()/2) {
      pointer = tail;
      for (size_t i = size_ - 1; i > index; i--) {
         pointer = pointer -> prev();
      }
   } else {
      pointer = head;
      for (size_t i = 0; i < index; i++) {
         pointer = pointer -> next();
      }
   }
   pointer -> prev() -> next(pointer -> next());
   pointer -> next() -> prev(pointer -> prev());
   pointer_val = pointer -> data();

   delete pointer;
   size_--;
   return aux_val;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {



}


template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
   return size_;
}

#endif
