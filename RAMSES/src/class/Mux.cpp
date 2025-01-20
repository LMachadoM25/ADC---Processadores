#include "../include/Mux.h"

int MUX::selecionar(int entrada1, int entrada2, bool seletor) {
    return seletor ? entrada2 : entrada1;
}