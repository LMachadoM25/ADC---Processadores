#ifndef REGISTRADOR_H
#define REGISTRADOR_H

class Registrador {
private:
    int valor; // Armazena o valor do registrador

public:
    Registrador();
    void setValor(int v);
    int getValor() const;
};
#endif