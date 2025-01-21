#include <iostream>

class ULA {
private:
    unsigned int resultado;  // Resultado da última operação
    bool flagZero;  // Flag: resultado igual a zero
    bool flagNegativo;  // Flag: resultado negativo

public:
    ULA() : resultado(0), flagZero(false), flagNegativo(false) {}

    // Operação ADD (Soma)
    int somar(int acumulador, int valorMemoria) {
        resultado = acumulador + valorMemoria;
        atualizarFlags(resultado);
        return resultado;
    }

    // Operação AND (Lógica)
    int andOp(int acumulador, int value) {
        resultado = acumulador & value;
        atualizarFlags(resultado);
        return resultado;
    }

    int orOp(int acumulador, int value) {
        resultado = acumulador | value;
        atualizarFlags(resultado);
        return resultado;
    }

    int notOp(unsigned int acumulador) {
        resultado = ~acumulador;
        atualizarFlags(resultado);
        return resultado;
    }

    int LDA(int acumulador, int value) {
        acumulador = value;
        resultado = acumulador;
        atualizarFlags(resultado);
        return resultado;
    }
    //acumulador = memoria.read(operand); //carrega o acumulador com o valor em MEM[operand]

    // Atualizar Flags (Zero e Negativo)
    void atualizarFlags(int resultado) {
        if (resultado == 0) {
            flagZero = true;
        }
        if (resultado < 0) {
            flagNegativo = true;
        }
    }

    // Getters para Flags
    bool getFlagZero() const {
        return flagZero;
    }

    bool getFlagNegativo() const {
        return flagNegativo;
    }

};
