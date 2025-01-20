#include <fstream>
#include <sstream>
#include <unordered_map>
#include <regex>
#include "MEM.hpp"
#include "ULA.hpp"
#include "AC.hpp"


class UnidadeDeControle {
private:
    int pc;  // Contador de programa
    int ri;  // Registrador de instrução
    int acumulador;
    Memoria& memoria;  // Agora só uma instância de Memoria
    ULA& ula;

public:

    // Construtor
    UnidadeDeControle(Memoria& mem, ULA& u) : pc(0), ri(0), acumulador(0), memoria(mem), ula(u) {}

    void parser(const std::string& filePath) {
        std::cout << "Chegou aqui!";
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
    }

    void busca() {
        //busca uma informação na memória
        int rdm_value = memoria.lerMemoria(pc); //rdm está guardando a variável lida na memória
        executarPrograma(rdm_value);
        //carga_rdm = ?

    }

    void executarPrograma(int rdm) {
        bool rodando = true;
        while (rodando) {
            // Fetch: Busca a próxima instrução na memória de instruções
            ri = rdm;
            // Decode & Execute: Decodifica e executa a instrução
            //rodando = decodificarInstrucao();

            // Incrementa o PC
            pc++;
        }
    }
    /*
    bool decode(int opcode) {
  
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
    */
};
