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
    char tipo;                     // Tipo do transporte (ex: 'T', 'A')
    int capacidade;                // Capacidade máxima de passageiros
    int velocidade;                // Velocidade de cruzeiro
    int distancia_entre_descansos; // Distância limite antes de precisar descansar
    int tempo_de_descanso_atual;   // Tempo em horas de descanso necessario
    int distancia_percorrida;      // Distância percorrida desde o último descanso
    int horas_descansadas;         // Horas de descanso já realizadas
    Cidade* localAtual;            // Localização atual do transporte
public:
    // Construtor para novo transporte
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso_atual, Cidade* localAtual);
    // Construtor para carregar transporte salvo
    Transporte(int idExistente, std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso_atual, Cidade* localAtual);
    
    int getId() const;
    static void setContadorID(int novoValor);
    std::string getNome();
    char getTipo();
    int getCapacidade();
    int getVelocidade();
    int getDistanciaEnteDescansos();
    int getTempoDeDescansoAtual();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
    int getDistanciaPercorrida();
    void setDistanciaPercorrida(int dist);
    void adicionarDistancia(int dist);
    int getHorasDescansadas();
    void setHorasDescansadas(int horas);
    void adicionarHoraDescanso();
    void resetarDescanso();
};
#endif //CONTROLADOR_DE_VIAGENS_TRANSPORTE_HPP
