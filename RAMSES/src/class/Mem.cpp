#include "../include/Mem.h"

Memoria::Memoria(int tamanho) : dados(tamanho, 0) {}

void Memoria::escrever(int endereco, int valor) {
    if (endereco >= 0 && endereco < dados.size()) {
        dados[endereco] = valor;
    }
}

int Memoria::ler(int endereco) const {
    if (endereco >= 0 && endereco < dados.size()) {
        return dados[endereco];
    }
    return 0;
}