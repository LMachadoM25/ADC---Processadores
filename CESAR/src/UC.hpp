#ifndef UC_HPP
#define UC_HPP

#include <iostream>
#include "MEM.hpp"
#include "ULA.hpp"
#include "Registradores.hpp"
#include "MUX.hpp"

class UnidadeDeControle
{
private:
    int pc;              // Contador de Programa
    Memoria &memoria;    // Referência à memória
    Registradores &regs; // Referência aos registradores
    ULA &ula;            // Referência à ULA
    int ciclos;
    MUX mux;

public:
    // Construtor
    UnidadeDeControle(Memoria &mem, Registradores &regs, ULA &ula)
        : pc(128), memoria(mem), regs(regs), ula(ula), ciclos(0) {}

    // Executar o programa armazenado na memória
    void executarPrograma()
    {
        bool rodando = true;

        while (rodando)
        {
            int instrucao = memoria.lerEndereco(pc++);
            int opcode = (instrucao >> 12) & 0xF;    // 4 bits mais altos
            int regDestino = (instrucao >> 8) & 0xF; // Próximos 4 bits
            int operando = instrucao & 0xFF;         // Últimos 8 bits
            ciclos++;
            switch (opcode)
            {
            case 0x1: // LDR: Carregar valor da memória para um registrador
                regs.escrever(regDestino, memoria.lerEndereco(operando));
                break;

            case 0x2:
            { // STR: Armazenar valor do registrador na memória
                int resultado = regs.ler(regDestino);
                int destino = mux.selecionar(regDestino, operando, true); // Escolhe entre memória e registrador
                memoria.escreverEndereco(destino, resultado);
                ciclos += 2;
                break;
            }

            case 0x3:
            {                                                                             // ADD: Soma entre registrador e memória
                int operandoA = regs.ler(regDestino);                                     // Valor do registrador de destino
                int operandoB = mux.selecionar(memoria.lerEndereco(operando), 10, false); // Seleciona memória
                regs.escrever(regDestino, ula.somar(operandoA, operandoB));
                ciclos += 1;
                break;
            }

            case 0x4:
            { // SUB: Subtração entre registrador e memória
                regs.escrever(regDestino, ula.subtrair(regs.ler(regDestino), memoria.lerEndereco(operando)));
                break;
            }

            case 0xF: // HLT: Finaliza o programa
                rodando = false;
                break;

            default:
                rodando = false;
                break;
            }
        }
    }

    // Exibir o estado dos registradores
    void exibirEstado() const
    {
        regs.exibir();
        std::cout << "Tempo de execução (em ciclos de relógio): " << ciclos << std::endl;
    }
};

#endif // UC_HPP