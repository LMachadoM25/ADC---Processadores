#include <iostream>
#include <sstream>
#include "UC.hpp"


int main() {
    Memoria mem(256);
    ULA ula;
    UnidadeDeControle controle(mem, ula);

    mem.escreverMemoriaDeDados(128, 10);
    mem.escreverMemoriaDeDados(129, 10);
    mem.escreverMemoriaDeDados(130, 10);
    
    std::string path = "algorithm/alg1.txt";
    controle.parser(path);

    mem.exibirMemoria();

    return 0;
}
