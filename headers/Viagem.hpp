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
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem *proxima;
    int horasEmTransito;
    bool emAndamento;
public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    bool isEmAndamento();
};


#endif //CONTROLADOR_DE_VIAGENS_VIAGEM_HPP
