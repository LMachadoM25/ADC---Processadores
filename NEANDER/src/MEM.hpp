#include <vector>
#include <iostream>
#include <stdexcept>

class Memoria {
private:

    std::vector<int> memoria; //unico vector de memoria 

public:
    Memoria(size_t tamanho) : memoria(tamanho, 0) {}

    // Métodos para acessar memória de dados
    int read(int endereco) const {
        if (endereco >= 0 && endereco < memoria.size())
            return memoria[endereco];
        else
            throw std::out_of_range("Endereço inválido na memória de dados!");
    }
    // Método para escrever na memória
    void write(int endereco, int valor) {
        if (endereco >= 0 && endereco < memoria.size())
            memoria[endereco] = valor;
        else
            throw std::out_of_range("Endereço inválido na memória de dados!");
    }

    // Exibir conteúdo da memória (para depuração)
    void exibirMemoria() const {
        std::cout << "Memória de Dados:\n";
        for (size_t i = 0; i < memoria.size(); ++i)
            std::cout << "Endereço " << i << ": " << memoria[i] << "\n";
    }
};
