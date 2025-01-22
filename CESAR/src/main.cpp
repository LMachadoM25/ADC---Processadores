#include "MEM.hpp"
#include "ULA.hpp"
#include "Registradores.hpp"
#include "UC.hpp"
#include "Parser.hpp"

#include <iostream>
#include <random>

int main()
{
    Memoria memoria(1024);
    Registradores regs(8);
    ULA ula;
    UnidadeDeControle uc(memoria, regs, ula);
    Parser parser;

    // Carregar o programa
    parser.carregarPrograma("algorithms/alg3.txt", memoria); //Alternar entre os arquivos txt da pasta algorithms para rodar os testes

    /* 

    //Descomentar se quiser fazer um teste com valores aleatórios com dados
    até o valor 128 da memória.

    // Carregar valores iniciais na memória
       // Carregar valores iniciais na memória
    std::random_device rd;  // Gera uma semente aleatória
    std::mt19937 gen(rd()); // Inicializa o gerador Mersenne Twister

    // Definir o intervalo de números
    std::uniform_int_distribution<> distrib(1, 100); // Inteiros de 1 a 100

    // Gerar e imprimir 10 números aleatórios
    for (int i = 0; i < 128; ++i)
    {
        memoria.escreverEndereco(i, distrib(gen));
    }

    //Comentar as duas linhas seguintes para fazer o teste com numeros aleatórios.
    */
    memoria.escreverEndereco(10, 10); // Valor no endereço 10
    memoria.escreverEndereco(11, 20); // Valor no endereço 11

    // Executar o programa
    uc.executarPrograma();

    // Exibir o estado final dos registradores
    memoria.exibirMemoria(32); //Digitar quantos dados de memória devem ser mostrados
    uc.exibirEstado();
    return 0;
}
