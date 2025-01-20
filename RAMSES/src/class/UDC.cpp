// UnidadeDeControle.cpp
#include "../include/UDC.h"
#include <iostream>

UnidadeDeControle::UnidadeDeControle(int tamanhoMemoria) : memoria(tamanhoMemoria), pc(0) {}

void UnidadeDeControle::executarInstrucao(int opcode) {
    switch (opcode) {
        case 0: // Exemplo: Soma
            ra.setValor(10);
            rb.setValor(20);
            rx.setValor(ula.operar(ra.getValor(), rb.getValor(), ULA::SOMA));
            std::cout << "Resultado da soma: " << rx.getValor() << std::endl;
            break;
        case 1: // Exemplo: Armazena na memória
            memoria.escrever(pc, rx.getValor());
            std::cout << "Valor armazenado na memoria: " << memoria.ler(pc) << std::endl;
            break;
        default:
            std::cout << "Opcode desconhecido: " << opcode << std::endl;
    }
}

int main() {
    UnidadeDeControle uc(256);

    // Exemplo de execução
    uc.executarInstrucao(0); // Soma
    uc.executarInstrucao(1); // Armazena na memória

    return 0;
}
