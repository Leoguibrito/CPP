// Copyright [2019] <Leonardo G de M Brito>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho
    std::size_t size();
    //! metodo retorna capacidade maxima
    std::size_t max_size();
    //! verifica se esta vazia
    bool empty();
    //! verifica se esta cheia
    bool full();

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

// Cria Pilha Genérica
template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

// Cria Pilha de Tamanho Específico
template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    // COLOQUE SEU CODIGO AQUI...
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

// Deleta a Memoria Alocada para a Pilha
template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

// Adiciona um Conteudo ao Topo da Pilha
template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        // COLOQUE SEU CODIGO AQUI...
        top_++;
        contents[top_] = data;
    }
}

// Pega o Conteudo do Topo da Pilha
template<typename T>
T structures::ArrayStack<T>::pop() {
    // COLOQUE SEU CODIGO AQUI...
    if (empty()) {
        throw std::out_of_range("Pilha Vazia");
    }
    T data = contents[top_];
    top_--;
    return data;
}

// Copia o Conteudo do Topo da Pilha
template<typename T>
T& structures::ArrayStack<T>::top() {
    // COLOQUE SEU CODIGO AQUI...
    if (empty()) {
        throw std::out_of_range("Pilha Cheia");
    }
    return contents[top_];
}

// Remove o Conteudo do Topo da Pilha
template<typename T>
void structures::ArrayStack<T>::clear() {
    // COLOQUE SEU CODIGO AQUI...
    top_ = -1;
}

// Checa o Tamanho da Pilha
template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    // COLOQUE SEU CODIGO AQUI..
    int size_ = top_ + 1;
    return size_;
}

// Checa o Tamanho Máximo que a Pilha pode ter
template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    // COLOQUE SEU CODIGO AQUI...
    return max_size_;
}

// Checa se a Pilha está Vazia
template<typename T>
bool structures::ArrayStack<T>::empty() {
    // COLOQUE SEU CODIGO AQUI...
    if (top_ == -1) {
        return true;
    } else {
        return false;
    }
}

// Checa se a Pilha está Cheia
template<typename T>
bool structures::ArrayStack<T>::full() {
    // COLOQUE SEU CODIGO AQUI...
    if (top_ == static_cast<int>(max_size_ - 1)) {
        return true;
    } else {
        return false;
    }
}
