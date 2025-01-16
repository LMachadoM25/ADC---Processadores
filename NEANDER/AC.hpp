#include "iostream"

class Acumulador {
private:
    int valor;

public:
    Acumulador() : valor(0) {}

    int getValor() const {
        return valor;
    }

    void setValor(int v) {
        valor = v;
    }

    void exibirEstado() const {
        std::cout << "Acumulador: " << valor << "\n";
    }
};
