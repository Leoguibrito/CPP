#include <iostream>
#include <fstream>
#include <string>
#include "./linked_stack.h"
using namespace std;

bool stack_verification (int pos, std::string linha, structures::LinkedStack<std::string> &pilha);

int main() {
    structures::LinkedStack<string> pilha;
    string line;
    bool error = false;
    char xmlfilename[100];

    cin >> xmlfilename;  // entrada

    ifstream xmlfile;
    xmlfile.open(xmlfilename);

    if (xmlfile.is_open()) {
        while (!xmlfile.eof() && !error) {
            getline (xmlfile,line);
            if (line[0] == '0' || line[0] == '1') {
                std::cout << "Até aqui foi 3" << std::endl;
                continue;
            }
            cout << "Até aqui foi 1" << std::endl;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '<') {
                    error = stack_verification(i, line, pilha);   // Checa o que vai fazer com relacao a pilha :D
                }
            }
        }
        xmlfile.close();
    } else {
        throw out_of_range("Arquivo xml não existente");
    }

    if (!pilha.empty()) {
        error = true;
    }
    
    if (!error) {  //Exercicio 2
        cout << "Sucesso!";
    } else {
        cout << "error" << std::endl;
    }

    return 0;
}

bool stack_verification (int pos, string linha, structures::LinkedStack<string> &pilha) {
    std::cout << "Até aqui foi 2" << std::endl;
    bool deu_erro = false;
    int pos_fim = pos;
    while (linha[pos_fim] != '>') {
        pos_fim++;
    }
    if (linha[pos+1] != '/') { 
        string result = linha.substr(pos+1, pos_fim-pos);
        pilha.push(result);
    } else {
        string result = linha.substr(pos+2, pos_fim-pos);
        string comp = pilha.pop();
        if (comp.compare(result) != 0) {
            deu_erro = true;
        }
    }
    return deu_erro;
}