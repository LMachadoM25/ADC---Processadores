#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Algorithm>
#include <unordered_map>
#include "MEM.hpp"

class Parser {
private:
    std::unordered_map<std::string, int> instr_map {
        {"NOP", 0x0},
        {"LDR", 0x1},
        {"STR", 0x2},
        {"ADD", 0x3},
        {"SUB", 0x4},
        {"AND", 0x5},
        {"OR",  0x6},
        {"NOT", 0x7},
        {"JMP", 0x8},
        {"JN",  0x9},
        {"JZ",  0xA},
        {"HLT", 0xF}
    };

public:
    void carregarPrograma(const std::string& caminhoArquivo, Memoria& memoria) {
    std::ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << "\n";
        return;
    }

    std::string linhaInstrucao, linhaRegistrador, linhaOperando;
    int contador = 0;
    const int baseInstrucoes = 128;
    while (std::getline(arquivo, linhaInstrucao) && 
           std::getline(arquivo, linhaRegistrador) && 
           std::getline(arquivo, linhaOperando)) {

        // Remove espaços extras ou caracteres invisíveis
        linhaInstrucao.erase(std::remove_if(linhaInstrucao.begin(), linhaInstrucao.end(), ::isspace), linhaInstrucao.end());
        linhaRegistrador.erase(std::remove_if(linhaRegistrador.begin(), linhaRegistrador.end(), ::isspace), linhaRegistrador.end());
        linhaOperando.erase(std::remove_if(linhaOperando.begin(), linhaOperando.end(), ::isspace), linhaOperando.end());

        // Valida instrução
        auto it = instr_map.find(linhaInstrucao);
        if (it == instr_map.end()) {
            std::cerr << "Instrução inválida: " << linhaInstrucao << "\n";
            continue;
        }

        int opcode = it->second;

        // Valida registrador
        int reg = 0, operando = 0;
        try {
            reg = std::stoi(linhaRegistrador);
            operando = std::stoi(linhaOperando);
        } catch (const std::invalid_argument&) {
            std::cerr << "Erro: Argumento inválido em registrador ou operando.\n";
            continue;
        }

        if (reg > 7) {
            std::cerr << "Registrador inválido: " << reg << "\n";
            continue;
        }
        

        // Monta a palavra de instrução
        int palavraInstrucao = (opcode << 12) | (reg << 8) | (operando & 0xFF);

        // Escreve na memória
        memoria.escreverEndereco(baseInstrucoes + contador, palavraInstrucao);
        contador++;
    }

    arquivo.close();
}
};

