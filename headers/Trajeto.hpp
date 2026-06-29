//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_TRAJETO_HPP
#define CONTROLADOR_DE_VIAGENS_TRAJETO_HPP
#include <string>
#include "Cidade.hpp"

class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo;
    int distancia;
public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    Cidade* getOrigem();
    Cidade* getDestino();
    char getTipo();
    int getDistancia();
};

#endif //CONTROLADOR_DE_VIAGENS_TRAJETO_HPP
