#include <iostream>

class ULA {
private:
    int resultado;  // Resultado da última operação
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

    // Operação SUB (Subtração)
    int subtrair(int acumulador, int valorMemoria) {
        resultado = acumulador - valorMemoria;
        atualizarFlags(resultado);
        return resultado;
    }

    // Operação AND (Lógica)
    int andBitwise(int acumulador, int valorMemoria) {
        resultado = acumulador & valorMemoria;
        atualizarFlags(resultado);
        return resultado;
    }

    // Atualizar Flags (Zero e Negativo)
    void atualizarFlags(int resultado) {
        flagZero = (resultado == 0);
        flagNegativo = (resultado < 0);
    }

    // Getters para Flags
    bool getFlagZero() const {
        return flagZero;
    }

    bool getFlagNegativo() const {
        return flagNegativo;
    }

};
