#include "MEM.hpp"
#include "ULA.hpp"
#include "Registradores.hpp"
#include "UC.hpp"
#include "Parser.hpp"

int main() {
    Memoria memoria(1024);
    Registradores regs(8);
    ULA ula;
    UnidadeDeControle uc(memoria, regs, ula);
    Parser parser;

    // Carregar o programa
    parser.carregarPrograma("programa.txt", memoria);

    // Carregar valores iniciais na memória
    memoria.escreverEndereco(10, 10);  // Valor no endereço 10
    memoria.escreverEndereco(11, 20);  // Valor no endereço 11

    // Executar o programa
    uc.executarPrograma();

    // Exibir o estado final dos registradores
    uc.exibirEstado();
    memoria.exibirMemoria(32);

    return 0;
}
