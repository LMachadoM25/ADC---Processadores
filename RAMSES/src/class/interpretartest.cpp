#include <iostream>
#include <string>
#include <vector>

// Função que interpreta o valor e retorna a instrução correspondente
std::string interpretarValor(int valor) {
    // Mapeamento das instruções
    std::vector<std::string> instrucoes = {
        "NOP", "STR", "LDR", "ADD", "OR", "AND", "NOT", "SUB", "JMP", "JN", "JZ", "JC", "JSR", "NEG", "SHR", "HLT"
    };

    // Mapeamento dos registradores
    std::vector<std::string> registradores = {"A", "B", "X"};

    // Modos possíveis
    std::vector<std::string> modos = {"Dir", "Ind", "Imd", "Idx"};
    
    // Para determinar a instrução, registrador e modo
    int instr = valor / 16;  // Determina a instrução dividindo por 16
    int reg = (valor % 16) / 4;  // Determina o registrador com base no valor restante
    int modo = valor % 4;  // Modo determinado pelo resto da divisão

    // Verifica se o valor está no intervalo válido das instruções
    if (instr < 0 || instr > 15) {
        return "Valor inválido";
    }

    // Verifica se o registrador está dentro do intervalo válido
    if (reg < 0 || reg > 2) {
        return "Registrador inválido";
    }

    // Verifica se o modo está dentro do intervalo válido
    if (modo < 0 || modo > 3) {
        return "Modo inválido";
    }

    // Monta a instrução com base nos cálculos
    std::string instrucao = instrucoes[instr] + " " + registradores[reg] + " " + modos[modo];
    return instrucao;
}

int main() {
    int valor;
    
    std::cout << "Digite um valor inteiro: ";
    std::cin >> valor;
    
    std::cout << "Instrução interpretada: " << interpretarValor(valor) << std::endl;
    
    return 0;
}
