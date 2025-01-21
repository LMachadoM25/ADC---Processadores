#ifndef MEM_HPP
#define MEM_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

class Memoria {
private:
    std::vector<int> memoria;

public:
    // Construtor: Inicializa a memória com tamanho específico
    Memoria(size_t tamanho) : memoria(tamanho, 0) {}

    // Ler um valor de um endereço da memória
    int lerEndereco(int endereco) const {
        if (endereco >= 0 && endereco < memoria.size())
            return memoria[endereco];
        throw std::out_of_range("Endereço inválido!");
    }

    // Escrever um valor em um endereço da memória
    void escreverEndereco(int endereco, int valor) {
        if (endereco >= 0 && endereco < memoria.size())
            memoria[endereco] = valor;
        else
            throw std::out_of_range("Endereço inválido!");
    }

    // Exibir a memória para depuração
    void exibirMemoria(size_t limite) const {
        for (size_t i = 0; i < limite; ++i) {
            std::cout << "Memória[" << i << "] = " << memoria[i] << "\n";
        }
    }
};

#endif // MEM_HPP
