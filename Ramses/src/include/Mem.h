#ifndef MEMORIA_H
#define MEMORIA_H

#include <vector>

class Memoria {
private:
    std::vector<int> dados;

public:
    Memoria(int tamanho);
    void escrever(int endereco, int valor);
    int ler(int endereco) const;
};
#endif