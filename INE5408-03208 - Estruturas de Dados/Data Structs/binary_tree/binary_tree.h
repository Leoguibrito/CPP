// COPYRIGHT [2022] <Leonardo G de M Brito>
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "array_list.h"

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
        explicit Node(const T& data) {
            data_ = data;
            left = nullptr;
            right = nullptr;
        }

        T data_;
        Node* left;
        Node* right;

        Node* minimum() {
            if (left)
                return left -> minimum();
            else
                return this;
        }

        Node* maximum() {
            if (right)
                return right -> maximum();
            else
                return this;
        }

        void insert(const T& data) {
            if (data_ > data) {
                if (!left)
                    left = new Node(data);
                else
                    left -> insert(data);
            } else {
                if (!right)
                    right = new Node(data);
                else
                    right -> insert(data);
            }
        }

        Node* remove(const T& data) {
            if (data_ > data) {
                if (left) {
                    left = left -> remove(data);
                    return this;
                } else {
                    return nullptr;
                }
            } else if (data_ < data) {
                if (right) {
                    right = right -> remove(data);
                    return this;
                } else {
                    return nullptr;
                }
            } else {
                if (right && left) {
                    Node* tmp = right -> minimum();
                    data_ = tmp -> data_;
                    right = right -> remove(data);
                    return this;
                } else if (right) {
                    Node* tmp = right;
                    delete this;
                    return tmp;
                } else if (left) {
                    Node* tmp = left;
                    delete this;
                    return tmp;
                } else {
                    delete this;
                    return nullptr;
                }
            }
        }

        bool contains(const T& data) const {
            if (data == data_)
                return true;
            else if (data < data_ && left)
                return left -> contains(data);
            else if (data > data_ && right)
                return right -> contains(data);
            
            return false;
            
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left)
                left -> pre_order(v);
            if (right)
                right -> pre_order(v);
        }

        void in_order(ArrayList<T>& v) const {
            if (left)
                left -> in_order(v);
            v.push_back(data_);
            if (right)
                right -> in_order(v);
        }

        void post_order(ArrayList<T>& v) const {
            if (left)
                left -> post_order(v);
            if (right)
                right -> post_order(v);
            v.push_back(data_);
        }
    };

    Node* root;
    std::size_t size_;
};

} // namespace structures

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    if (root) {
        structures::ArrayList<T> nodes_list = pre_order();

        while (size_)
            remove(nodes_list.pop_back());
    }
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (root)
        root -> insert(data);
    else
        root = new Node(data);
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Árvore vazia");
    if (!contains(data)) {
        throw std::out_of_range("O dado não existe");
    } 

    root -> remove(data);
    size_--;
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root)
        return root -> contains(data);
    return false;
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return (static_cast<int>(size_) == 0);
}

template<typename T>
size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    if (!root)
        throw std::out_of_range("Árvore vazia");

    structures::ArrayList<T> final_list;
    root -> pre_order(final_list);

    return final_list;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    if (!root)
        throw std::out_of_range("Árvore vazia");

    structures::ArrayList<T> final_list;
    root -> in_order(final_list);

    return final_list;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    if (!root)
        throw std::out_of_range("Árvore vazia");

    structures::ArrayList<T> final_list;
    root -> post_order(final_list);

    return final_list;
}

#endif 


/*bool remove(const T& data) {
    if (data_ > data) {
        if (left) {
            return left -> remove(data);
        } else {
            return false;
        }

    } else if (data_ < data) {
        if (right) {
            return right -> remove(data);
        } else {
            return false;
        }
    
    } else { // Caso o nó contenha o dado
        if (right && left) {
            Node* pointer = right -> minimum();
            data_ = pointer -> data_;
            delete pointer;
            return true;
        } else if (left) {
            Node* pointer = left;
            if (left -> right) {
                right = left -> right;
            }
            if (left -> left) {
                left = left -> left;
            }
            data_ = left -> data_;
            delete pointer;
            return true;
        } else if (right) {
            Node* pointer = right;
            if(right -> right) {
                right = right -> right;
            }
            if (right -> left) {
                left = right -> left;
            }
            data_ = right -> data_;
            delete pointer;
            return true;
        } else {
            delete this;
            return true;
        }
    }
}*/
