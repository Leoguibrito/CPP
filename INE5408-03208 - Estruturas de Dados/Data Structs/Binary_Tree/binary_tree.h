//! Copyright [2022] <Leonardo G de M Brito>
#include "array_list.h"
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* right):
            data_{data},
            right_{right}
        {}

        Node(const T& data, Node* left, Node* right):
            data_{data},
            right_{right},
            left_{left}
        {}


        T& data() {
            return data_;
        }

        Node* left() {
            return left_;
        }

        Node* right() {
            return right_;
        }

        T data_;
        Node* left_;
        Node* right_;


        void insert(const T& data_);

        bool remove(const T& data_);

        bool contains(const T& data_) const;

        void pre_order(ArrayList<T>& v) const;

        void in_order(ArrayList<T>& v) const;

        void post_order(ArrayList<T>& v) const;
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

#endif

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    Node* pointer = root;
    while (!empty) {
        remove(pointer);
        pointer = root;
    }
    size_ = 0
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {

}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {

}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {

}

template<typename T>
bool structures::BinaryTree<T>::empty() const {

}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}


template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {  // Chamar e implementar no struct
    ArrayList<T> lista;
    //Alguma Coisa
    return lista;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {  // Chamar e implementar no struct

}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {  // Chamar e implementar no struct

}