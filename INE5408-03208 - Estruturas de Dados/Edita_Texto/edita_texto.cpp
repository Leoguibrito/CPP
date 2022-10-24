// Copyright [2022] <Leonardo G de M Brito>
#include <string>
#include "./array_queue.h"

structures::ArrayQueue<char> editaTexto(std::string texto) {
    structures::ArrayQueue<char> fila(500);
    //COLOCAR SEU CÓDIGO AQUI...
    int size = texto.length();
    char end_text;
    char last_el;

    for (int i = 0; i < size; i++) {
        if (texto[i] == '<') {
            fila.dequeue();
        } else if (texto[i] == '>') {
            last_el = fila.back();
            fila.enqueue(last_el);
        } else fila.enqueue(texto[i]);
    }

    return fila;
}