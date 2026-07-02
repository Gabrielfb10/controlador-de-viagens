//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_TRAJETO_HPP
#define CONTROLADOR_DE_VIAGENS_TRAJETO_HPP
#include <string>
#include "Cidade.hpp"

class Trajeto {
private:
    Cidade* origem;      // Cidade de partida
    Cidade* destino;     // Cidade de chegada
    char tipo;           // Tipo de trajeto (ex: 'T' Terrestre, 'A' Aquático)
    int distancia;       // Distância do trajeto em km
public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    
    Cidade* getOrigem();
    Cidade* getDestino();
    char getTipo();
    int getDistancia();
};

#endif //CONTROLADOR_DE_VIAGENS_TRAJETO_HPP
