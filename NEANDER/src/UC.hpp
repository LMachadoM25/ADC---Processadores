#include <fstream>
#include <sstream>
#include <unordered_map>
#include "MEM.hpp"
#include "ULA.hpp"
#include "AC.hpp"


class UnidadeDeControle {
private:
    int pc;  // Contador de programa
    int ri;  // Registrador de instrução
    int acumulador;  // O único registrador do Neander
    Memoria& memoria;  // Agora só uma instância de Memoria
    ULA& ula;

public:
    std::unordered_map<std::string, int> instr_map {
        {"NOP", 0x00},
        {"LDA", 0x01},
        {"STA", 0x02},
        {"ADD", 0x03},
        {"SUB", 0x04},
        {"AND", 0x05},
        {"OR",  0x06},
        {"NOT", 0x07},
        {"JMP", 0x08},
        {"JN",  0x09},
        {"HLT", 0xFF}
    };

    void parser(const std::string& filePath) {
        std::ifstream file(filePath); 

        if (!file.is_open()) {
            std::cout << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }
        
        std::string line;
        std::string instruction;
        int word;
        int operand;
        int contador = 0;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> instruction >> operand;

            auto it = instr_map.find(instruction);
            int opcode = it->second;

            word = (opcode << 8) | (operand & 0xFF);

            // Usando a memória de instruções diretamente
            memoria.escreverMemoriaDeInstrucoes(contador, word);
            contador++;
        }
    }

    // Construtor
    UnidadeDeControle(Memoria& mem, ULA& u) : pc(0), ri(0), acumulador(0), memoria(mem), ula(u) {}

    void executarPrograma() {
        bool rodando = true;
        while (rodando) {
            // Fetch: Busca a próxima instrução na memória de instruções
            ri = memoria.lerMemoriaDeInstrucoes(pc);

            // Decode & Execute: Decodifica e executa a instrução
            rodando = decodificarInstrucao();

            // Incrementa o PC
            pc++;
        }
    }

    bool decodificarInstrucao() {
        int opcode = (ri >> 8) & 0xFF;  
        int operando = ri & 0xFF;       

        switch (opcode) {
            case 0x00:  // NOP
                return true;
            case 0x01:  // LOAD
                acumulador = memoria.lerMemoriaDeDados(operando);
                return true;
            case 0x02:  // STORE
                memoria.escreverMemoriaDeDados(operando, acumulador);
                return true;
            case 0x03:  // ADD
                acumulador = ula.somar(acumulador, memoria.lerMemoriaDeDados(operando));
                return true;
            case 0x04:  // SUB
                acumulador = ula.subtrair(acumulador, memoria.lerMemoriaDeDados(operando));
                return true;
            case 0x05:  // AND
                acumulador = ula.andBitwise(acumulador, memoria.lerMemoriaDeDados(operando));
                return true;
            case 0xFF:  // HALT
                return false;  
            default:
                std::cerr << "Instrução inválida: " << opcode << "\n";
                return false;
        }
    }
};
