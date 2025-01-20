#include <vector>
#include <iostream>
#include <stdexcept>

class Memoria {
private:
    std::vector<int> memoria;  // Memória de dados
    std::vector<int> mem_inst; // Memória de instruções

public:
    Memoria(size_t tamanho) : memoria(tamanho, 0), mem_inst(tamanho, 0) {}

    // Métodos para acessar memória de dados
    int lerMemoriaDeDados(int endereco) const {
        if (endereco >= 0 && endereco < memoria.size())
            return memoria[endereco];
        throw std::out_of_range("Endereço inválido na memória de dados!");
    }

    void escreverMemoriaDeDados(int endereco, int valor) {
        if (endereco >= 0 && endereco < memoria.size())
            memoria[endereco] = valor;
        else
            throw std::out_of_range("Endereço inválido na memória de dados!");
    }

    // Métodos para acessar memória de instruções
    int lerMemoriaDeInstrucoes(int endereco) const {
        if (endereco >= 0 && endereco < mem_inst.size())
            return mem_inst[endereco];
        throw std::out_of_range("Endereço inválido na memória de instruções!");
    }

    void escreverMemoriaDeInstrucoes(int endereco, int valor) {
        if (endereco >= 0 && endereco < mem_inst.size())
            mem_inst[endereco] = valor;
        else
            throw std::out_of_range("Endereço inválido na memória de instruções!");
    }

    // Exibir conteúdo da memória (para depuração)
    void exibirMemoria() const {
        std::cout << "Memória de Dados:\n";
        for (size_t i = 0; i < memoria.size(); ++i)
            std::cout << "Endereço " << i << ": " << memoria[i] << "\n";
    }
};
