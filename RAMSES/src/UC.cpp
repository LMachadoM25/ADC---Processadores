#include <iostream>
#include <string>
#include <vector>

// Função que interpreta o valor da instrução e retorna a operação correspondente
std::string interpretarValor(int valor, int adress, int& registradorA, int& registradorB, int& registradorX, std::vector<int>& memoria) {

    // Mapeamento das instruções
    std::vector<std::string> instrucoes = {
        "NOP", "STR", "LDR", "ADD", "OR", "AND", "NOT", "SUB", "JMP", "JN", "JZ", "JC", "JSR", "NEG", "SHR", "HLT"
    };

    // Mapeamento dos registradores
    std::vector<std::string> registradores = {"A", "B", "X"};

    // Modos possíveis
    std::vector<std::string> modos = {"Dir", "Ind", "Imd", "Idx"};
    
    // Extração de bits:
    // A instrução ocupa os 4 bits mais significativos
    int instr = (valor >> 4) & 0xF; // Desloca 4 bits e aplica máscara 0xF (1111 em binário)
    
    // O registrador ocupa os 2 bits seguintes
    int reg = (valor >> 2) & 0x3; // Desloca 2 bits e aplica máscara 0x3 (11 em binário)
    int registrador = 0;
    reg = registrador;
    
    // O modo ocupa os 2 bits menos significativos
    int modo = valor & 0x3; // Aplica máscara 0x3 para obter os 2 bits mais baixos
    int modotrue = 0;
    modo = modotrue;
    
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

    // Verifica a instrução para somar
    std::string instrucao = instrucoes[instr] + " " + registradores[reg] + " " + modos[modo];
    std::cout << "Instrução: " << instr << ", Registrador: " << reg << ", Modo: " << modo << std::endl;

    // Executa operações específicas, como somar para ADD
    if (instr == 3) { // ADD
    if (modo == 0) { // Direto
        if (reg == 0) registradorA += memoria[adress];
        else if (reg == 1) registradorB += memoria[adress];
        else if (reg == 2) registradorX += memoria[adress];
    } else if (modo == 1) { // Indireto
        if (reg == 0) registradorA += memoria[memoria[adress]];
        else if (reg == 1) registradorB += memoria[memoria[adress]];
        else if (reg == 2) registradorX += memoria[memoria[adress]];
    } else if (modo == 2) { // Imediato
        if (reg == 0) registradorA += adress;
        else if (reg == 1) registradorB += adress;
        else if (reg == 2) registradorX += adress;
    } else if (modo == 3) { // Indexado
        if (reg == 0) registradorA += memoria[adress + registradorX];
        else if (reg == 1) registradorB += memoria[adress + registradorX];
        else if (reg == 2) registradorX += memoria[adress + registradorX];
        }
    }

    if (instr == 7) { // SUB
    if (modo == 0) { // Direto
        if (reg == 0) registradorA -= memoria[adress];
        else if (reg == 1) registradorB -= memoria[adress];
        else if (reg == 2) registradorX -= memoria[adress];
    } else if (modo == 1) { // Indireto
        if (reg == 0) registradorA -= memoria[memoria[adress]];
        else if (reg == 1) registradorB -= memoria[memoria[adress]];
        else if (reg == 2) registradorX -= memoria[memoria[adress]];
    } else if (modo == 2) { // Imediato
        if (reg == 0) registradorA -= adress;
        else if (reg == 1) registradorB -= adress;
        else if (reg == 2) registradorX -= adress;
    } else if (modo == 3) { // Indexado
        if (reg == 0) registradorA -= memoria[adress + registradorX];
        else if (reg == 1) registradorB -= memoria[adress + registradorX];
        else if (reg == 2) registradorX -= memoria[adress + registradorX];
        }
    }

    return instrucao;
}


int main() {
    std::string input;
    int valor, endereco, valorEndereco;

    // Registradores para armazenar resultados
    int registradorA = 0;
    int registradorB = 20;
    int registradorX = 0;

    // Criando a memória com 255 posições (inicializadas com 0)
    std::vector<int> memoria(255, 0);

    // Laço de repetição até que o usuário digite "240"
    while (true) {
        std::cout << "Digite o valor da instrução (ou '240' para sair): ";
        std::cin >> input;
        
        // Verifica se o usuário digitou 240 para sair
        if (input == "240") {
            std::cout << "Saindo..." << std::endl;
            break;
        }

        // Tenta converter o input para um valor inteiro
        try {
            valor = std::stoi(input);

            // Pede o endereço e o valor do endereço
            std::cout << "Digite o endereço de memória: ";
            std::cin >> endereco;

            std::cout << "Digite o valor armazenado no endereço " << endereco << ": ";
            std::cin >> valorEndereco;

            // Armazena o valor no endereço especificado
            memoria[endereco] = valorEndereco;

            // Processa a instrução
            std::string instrucao = interpretarValor(valor, endereco, registradorA, registradorB, registradorX, memoria);
            std::cout << instrucao << std::endl;
            
            // Exibe o valor do registrador A após a operação
            std::cout << "Valor de A após operação: " << registradorA << std::endl;
            std::cout << "Valor de B após operação: " << registradorB << std::endl;
            std::cout << "Valor de X após operação: " << registradorX << std::endl;

        } catch (const std::invalid_argument& e) {
            std::cout << "Entrada inválida, por favor digite um número inteiro ou '240' para sair." << std::endl;
        }
    }
    
    return 0;
}