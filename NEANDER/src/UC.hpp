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
    Memoria& memoria;
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

    void parser(const std::string& filePath) { //função que vai ler o arquivo de texto que contém o algoritmo e escrever na memória de instruções as palavras de instrução
        std::ifstream file(filePath); //inicializo um objeto da biblioteca ifstream

        if (!file.is_open()) {  //verifico se o arquivo foi aberto corretamente
            std::cout << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }
        
        std::string line;
        std::string instruction;
        int word;
        int operand;
        int contador = 0;

        while (std::getline(file, line)) { //enquanto line receber uma linha de file, preciso verificar qual a instrução recebida e colocá-la na memória
            std::istringstream iss(line);
            iss >> instruction >> operand; //separo a palavra de instrução do operando

            auto it = instr_map.find(instruction);
            int opcode = it->second;

            word = (opcode << 8) | (operand & 0xFF);

            memoria.escreverEndereco(contador, word);
            contador++;
        }
    }


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
