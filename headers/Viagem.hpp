//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_VIAGEM_HPP
#define CONTROLADOR_DE_VIAGENS_VIAGEM_HPP

#include <vector>
#include "Passageiro.hpp"
#include "Transporte.hpp"

class Viagem {
private:
    static int contadorID;
    int id;
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem *proxima;            // Ponteiro para a próxima viagem (conexão)
    int horasEmTransito;        // Horas já gastas na viagem
    int distancia;              // Distância total da viagem
    bool emAndamento;           // Indica se a viagem começou e ainda não terminou
    bool ocorreu;               // Indica se a viagem já foi concluída
public:
    // Cria uma nova viagem sem conexão
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
    // Cria uma viagem já estabelecendo uma conexão
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia, Viagem* proxima);
    // Cria uma viagem a partir de dados salvos
    Viagem(int idExistente, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, Viagem* proxima, int horasEmTransito, bool emAndamento, bool ocorreu, int distancia);
    
    // Métodos de controle do ciclo de vida da viagem
    void iniciarViagem();
    void avancarHoras();
    void relatarEstado();
    
    int getId() const;
    Transporte* getTransporte();
    std::vector<Passageiro*> getPassageiros();
    Cidade* getOrigem();
    Cidade* getDestino();
    Viagem* getProxima();
    int getHorasEmTransito();
    int getDistancia();
    void setProxima(Viagem* proxima);
    static void setContadorID(int novoValor);
    void setEmAndamento(bool estado);
    void setOcorreu(bool estado);
    bool isEmAndamento();
    bool isOcorreu();
};


#endif //CONTROLADOR_DE_VIAGENS_VIAGEM_HPP
