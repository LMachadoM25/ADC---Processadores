#ifndef ULA_HPP
#define ULA_HPP

class ULA {
public:
    // Soma
    int somar(int a, int b) {
        return a + b;
    }

    // Subtração
    int subtrair(int a, int b) {
        return a - b;
    }

    // Operação AND
    int andBitwise(int a, int b) {
        return a & b;
    }

    // Operação OR
    int orBitwise(int a, int b) {
        return a | b;
    }
};

#endif // ULA_HPP
