//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_CONTROLADORDETRANSITO_HPP
#define CONTROLADOR_DE_VIAGENS_CONTROLADORDETRANSITO_HPP
#include <vector>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"
#include "Viagem.hpp"
#include "Transporte.hpp"


class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;
public:
    std::vector<Trajeto*> melhorTrajeto(Cidade* origem, Cidade* destino);
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);
    void iniciarViagem(int idTransporte, std::vector<int> idsPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado();
};
#endif //CONTROLADOR_DE_VIAGENS_CONTROLADORDETRANSITO_HPP
