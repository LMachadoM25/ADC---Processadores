#include <iostream>
#include <sstream>
#include "UC.hpp"   


int main() {
    Memoria mem(256);
    ULA ula;
    UnidadeDeControle controle(mem, ula);
    
    std::string path = "algorithm/alg3.txt";
    controle.parser(path);

    mem.exibirMemoria();

    std::cout << std::endl;
    std::cout << std::endl;

    controle.executar();
    mem.exibirMemoria();

    return 0;
}
