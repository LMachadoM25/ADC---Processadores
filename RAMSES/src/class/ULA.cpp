#include "../include/ULA.h"

int ULA::operar(int x, int y, Operacao op) {
    switch (op) {
        case SOMA: return x + y;
        case SUBTRACAO: return x - y;
        case AND: return x & y;
        case OR: return x | y;
        case XOR: return x ^ y;
    }
    return 0;
}