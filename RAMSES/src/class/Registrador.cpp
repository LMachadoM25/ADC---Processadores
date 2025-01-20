#include "../include/Registrador.h"

Registrador::Registrador() : valor(0) {}

void Registrador::setValor(int v) {
    valor = v;
}

int Registrador::getValor() const {
    return valor;
}
