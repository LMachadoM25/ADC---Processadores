#ifndef MUX_HPP
#define MUX_HPP

#include <vector>
#include <iostream>

class MUX {
public:
    // Seleciona entre 2 entradas
    int selecionar(int entrada0, int entrada1, bool seletor) const {
        return seletor ? entrada1 : entrada0;
    }

    // Seleciona entre múltiplas entradas
    int selecionar(const std::vector<int>& entradas, int seletor) const {
        if (seletor >= 0 && seletor < entradas.size()) {
            return entradas[seletor];
        }
        throw std::out_of_range("Seletor inválido para o MUX!");
    }
};

#endif // MUX_HPP
