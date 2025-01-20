#ifndef ULA_H
#define ULA_H

class ULA {
public:
    enum Operacao { SOMA, SUBTRACAO, AND, OR, XOR };

    int operar(int x, int y, Operacao op);
};

#endif