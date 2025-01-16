#include "MEM.hpp"
#include "ULA.hpp"

class UnidadeDeControle {
private:
    int pc;  // Contador de programa
    int ri;  // Registrador de instrução
    int acumulador;  // O único registrador do Neander
    Memoria& memoria;
    ULA& ula;

public:
    // Construtor
    UnidadeDeControle(Memoria& mem, ULA& u) : pc(0), ri(0), acumulador(0), memoria(mem), ula(u) {}

    // Executar o programa carregado na memória
    void executarPrograma() {
        bool rodando = true;
        while (rodando) {
            // Fetch: Busca a próxima instrução na memória
            ri = memoria.lerEndereco(pc);

            // Decode & Execute: Decodifica e executa a instrução
            rodando = decodificarInstrucao();

            // Incrementa o PC (exceto para instruções que alteram diretamente o PC)
            pc++;
        }
    }

    // Decodificar e executar uma instrução
    bool decodificarInstrucao() {
        int opcode = (ri >> 8) & 0xFF;  // Os 8 bits mais altos são o opcode
        int operando = ri & 0xFF;       // Os 8 bits mais baixos são o operando

        switch (opcode) {
            case 0x00:  // NOP
                return true;
            case 0x01:  // LOAD
                acumulador = memoria.lerEndereco(operando);
                return true;
            case 0x02:  // STORE
                memoria.escreverEndereco(operando, acumulador);
                return true;
            case 0x03:  // ADD
                acumulador = ula.somar(acumulador, memoria.lerEndereco(operando));
                return true;
            case 0x04:  // SUB
                acumulador = ula.subtrair(acumulador, memoria.lerEndereco(operando));
                return true;
            case 0x05:  // AND
                acumulador = ula.andBitwise(acumulador, memoria.lerEndereco(operando));
                return true;
            case 0xFF:  // HALT
                return false;  // Finaliza o programa
            default:
                std::cerr << "Instrução inválida: " << opcode << "\n";
                return false;
        }
    }
};
