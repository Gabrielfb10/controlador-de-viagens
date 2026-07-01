//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_TRANSPORTE_HPP
#define CONTROLADOR_DE_VIAGENS_TRANSPORTE_HPP

#include <string>
#include "Cidade.hpp"

class Transporte {
private:
    static int contadorID;
    int id;
    std::string nome;
    char tipo;
    int capacidade;
    int velocidade;
    int distancia_entre_descansos;
    int tempo_de_descanso_atual;
    Cidade* localAtual;
public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso_atual, Cidade* localAtual);
    Transporte(int idExistente, std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso_atual, Cidade* localAtual);
    int getId() const;
    static void setContadorID(int novoValor);
    std::string getNome();
    int getCapacidade();
    int getVelocidade();
    int getDistanciaEnteDescansos();
    int getTempoDeDescansoAtual();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};
#endif //CONTROLADOR_DE_VIAGENS_TRANSPORTE_HPP
