#ifndef UNIDADE_DE_CONTROLE_H
#define UNIDADE_DE_CONTROLE_H

#include "Registrador.h"
#include "ULA.h"
#include "Mem.h"
#include "Mux.h"

class UnidadeDeControle {
private:
    Registrador ra, rb, rx;
    ULA ula;
    Memoria memoria;
    MUX mux;
    int pc; // Program Counter

public:
    UnidadeDeControle(int tamanhoMemoria);
    void executarInstrucao(int opcode);
};

#endif