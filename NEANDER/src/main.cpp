#include <iostream>
#include <sstream>
#include "UC.hpp"


int main() {
    Memoria mem(256);
    ULA ula;
    UnidadeDeControle controle(mem, ula);

    mem.escreverEndereco(128, 10);
    mem.escreverEndereco(129, 10);
    mem.escreverEndereco(130, 10);
    
    std::string path = "algorithm/alg1.txt";
    controle.parser(path);

    mem.exibirMemoria();

    return 0;
}
