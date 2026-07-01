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
    Viagem *proxima;
    int horasEmTransito;
    int distancia;
    bool emAndamento;
    bool ocorreu;
public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia, Viagem* proxima);
    Viagem(int idExistente, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, Viagem* proxima, int horasEmTransito, bool emAndamento, bool ocorreu);
    void iniciarViagem();
    void avancarHoras();
    void relatarEstado();
    int getId() const;
    void setProxima(Viagem* proxima);
    static void setContadorID(int novoValor);
    void setEmAndamento(bool estado);
    void setOcorreu(bool estado);
    bool isEmAndamento();
    bool isOcorreu();
};


#endif //CONTROLADOR_DE_VIAGENS_VIAGEM_HPP
