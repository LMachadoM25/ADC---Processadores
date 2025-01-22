#include <fstream>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <iomanip>
#include "MEM.hpp"
#include "ULA.hpp"
#include "AC.hpp"


class UnidadeDeControle {
private:
    int pc;  //contador de programa
    int ri;  //registrador de instrução
    unsigned int acumulador;    //variável acumulador 
    Memoria& memoria;  //instância de Memoria
    ULA& ula;

    int zeroflag;
    int negtflag;

    int clock = 0;

public:

    // Construtor
    UnidadeDeControle(Memoria& mem, ULA& u) : pc(0), ri(0), acumulador(0), memoria(mem), ula(u) {}

    //função responsável por receber a memória externa e transportar para a nossa memória interna
    void parser(const std::string& filePath) {
        std::ifstream file(filePath); 

        if (!file.is_open()) {
            std::cout << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }
        
        std::string line;
        while (std::getline(file, line)) {
        int index, value;

        // Verifica se a linha contém o formato "MEM[index] = value"
            if (line.find("MEM[") != std::string::npos && line.find("] =") != std::string::npos) {
                // Encontrar a posição do índice e valor
                size_t startIdx = line.find("[") + 1;
                size_t endIdx = line.find("]");

                // Extrair o índice e o valor
                std::string indexStr = line.substr(startIdx, endIdx - startIdx);
                std::string valueStr = line.substr(endIdx + 3); // Pular "] = "

                // Tentar converter para inteiros
                try {
                    index = std::stoi(indexStr); // Converte o índice
                    value = std::stoi(valueStr); // Converte o valor
                } catch (const std::invalid_argument& e) {
                    std::cout << "Erro na conversão de dados na linha: " << line << std::endl;
                    continue;
                }

            memoria.write(index, value);
            } 
        }
        file.close();
    }

    //Inicia o ciclo de busca de instrução.
    void executar() {
        busca();
    }

    //busca uma instrução e um endereço de dado na memória.
    void busca() {
        bool rodando = true;

        unsigned int opcode, operando;
        //clock
        while (rodando) {
            clock++;
            // Fetch: Busca a próxima instrução na memória de instruções
            opcode = memoria.read(pc);
            pc++;

            // Decode & Execute: Decodifica e executa a instrução
            operando = memoria.read(pc);
            pc++;

            output1(opcode, operando);
            rodando = decode(opcode, operando); //quando decode retornar false, quebra o while e cai na função end()
        }
        //clock

        memoria.exibirMemoria();
        end();
    }
    
    //decodifica e realiza a instrução
    bool decode(unsigned int opcode, unsigned int operand) {

        switch (opcode) {
            case 0:  // NOP
                output2();
                flags();
                return true;
            case 16:  // STA
                memoria.write(operand, acumulador);
                output2();
                flags();
                return true;
                clock++;
                clock++;
            case 32:  // LDA
                acumulador = ula.LDA(acumulador, memoria.read(operand)); //carrega o acumulador com o valor em MEM[operand]
                output2();
                flags();
                clock++;
                clock++;
                return true;
            case 48:  // ADD
                acumulador = ula.somar(acumulador, memoria.read(operand)); //soma no acumulador o valor em MEM[operand].
                output2();
                flags();
                return true;
            case 64:  // OR
                acumulador = ula.orOp(acumulador, memoria.read(operand)); //realiza no acumulador uma operação OR
                output2();
                flags();
                return true;
            case 80:  // AND
                acumulador = ula.andOp(acumulador, memoria.read(operand)); //realiza no acumulador uma operação AND
                output2();
                flags();
                return true;
            case 96:  // NOT
                acumulador = ula.notOp(acumulador);
                output2();
                flags();
                return true;
            case 128:  // JMP
                pc = operand;
                output2();
                flags();
                return true;
            case 144:  // JN
                if(ula.getFlagNegativo()) {
                    pc = operand;
                }
                output2();
                flags();
                return true;
            case 160:  // JZ
                if(ula.getFlagZero()) {
                    pc = operand;
                }
                output2();
                flags();
                return true;
            case 240:  // HALT
                output2();
                flags();
                return false;  
            default:
                std::cerr << "Instrução inválida: " << opcode << "\n";
                return false;
        }
    }

    //joga para a saída as variáveis solicitadas.
    void output1(int opcode, int adress) { //output inicial

        std::map<int, std::string> neanderInstructions = {
        {16, "STA"},
        {32, "LDA"},
        {48, "ADD"},
        {64, "OR"},
        {80, "AND"},
        {96, "NOT"},
        {128, "JMP"},
        {144, "JN"},
        {160, "JZ"},
        {240, "HLT"}
        };

        auto it = neanderInstructions.find(opcode);
        std::string instruction = it->second;

        std::cout << "---------------STATUS DO PROCESSADOR---------------" << std::endl;
        std::cout << "PC: " << pc/2 << std::endl;
        std::cout << "Instrução interpretada: " << instruction << std::endl;
        std::cout << "Conteudo da memória: " << memoria.read(adress) << std::endl;
        std::cout << "Acumulador: " << acumulador << std::endl; 
        std::cout << "Tempo de execução (em ciclos de execução): " << clock << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

    }

    void output2() { //mostra apenas o resultado do output 
        std::cout << "----------------STATUS DO ACUMULADOR---------------" << std::endl;
        std::cout << "Acumulador: " << acumulador << std::endl;
    }

    void flags() {
    
        std::cout << "CARGA_Z = " << ula.getFlagZero() << " ";
        std::cout << "CARGA_N = " << ula.getFlagNegativo() << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }

    //função de encerramento do programa.
    void end() {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Valor final do PC: " << pc << std::endl;
        std::cout << "Resultado final do acumulador: " << acumulador << std::endl;
        std::cout << "Tempo de execução(em ciclos de execução): " << clock << std::endl;
        std::cout << std::endl;
    }
};
