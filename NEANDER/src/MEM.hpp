#include <vector>
#include <iostream>
#include <stdexcept>

class Memoria {
private:
    std::vector<int> memoria;  // Vetor que representa a memória
    std::vector<int> mem_inst; // Vetor que representa a memória que vai ser utilizada apenas para armazenar as palavras de instrução 

public:
    // Construtor com tamanho definido
    Memoria(size_t tamanho) : memoria(tamanho, 0), mem_inst(tamanho, 0) {}

    // Ler valor de um endereço
    int lerEndereco(int endereco) const {
        if (endereco >= 0 && endereco < memoria.size())
            return memoria[endereco];
        throw std::out_of_range("Endereço inválido!");
    }

    // Escrever valor em um endereço
    void escreverEndereco(int endereco, int valor) {
        if (endereco >= 0 && endereco < memoria.size())
            memoria[endereco] = valor;
        else
            throw std::out_of_range("Endereço inválido!");
    }

    // Exibir conteúdo da memória (para depuração)
    void exibirMemoria() const {
        std::cout << "Memória:\n";
        for (size_t i = 0; i < memoria.size(); ++i)
            std::cout << "Endereço " << i << ": " << memoria[i] << "\n";
    }
};
