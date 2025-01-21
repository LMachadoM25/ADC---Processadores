#ifndef REGISTRADORES_HPP
#define REGISTRADORES_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

class Registradores {
private:
    std::vector<int> regs;

public:
    // Construtor inicializa os registradores
    Registradores(size_t tamanho = 8) : regs(tamanho, 0) {}

    // Ler o valor de um registrador
    int ler(int indice) const {
        if (indice >= 0 && indice < regs.size())
            return regs[indice];
        throw std::out_of_range("Registrador inválido!");
    }

    // Escrever um valor em um registrador
    void escrever(int indice, int valor) {
        if (indice >= 0 && indice < regs.size())
            regs[indice] = valor;
        else
            throw std::out_of_range("Registrador inválido!");
    }

    // Exibir o estado dos registradores
    void exibir() const {
        for (size_t i = 0; i < regs.size(); ++i) {
            std::cout << "R" << i << ": " << regs[i] << "\n";
        }
    }
};

#endif // REGISTRADORES_HPP
