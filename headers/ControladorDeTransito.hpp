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
    // Armazenamento central de todos os dados do sistema
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;
public:
    // Algoritmo de busca para encontrar o melhor trajeto (menor distância) entre duas cidades usando o tipo de transporte
    std::vector<Trajeto*> melhorTrajeto(Cidade* origem, Cidade* destino, char tipoTransporte);
    
    // Cadastros
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);
    
    // Controle de viagens e simulação do tempo
    void iniciarViagem(int idTransporte, std::vector<int> idsPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado();
    
    // Getters para salvar/carregar dados
    std::vector<Cidade*> getCidades() const { return cidades; }
    std::vector<Trajeto*> getTrajetos() const { return trajetos; }
    std::vector<Transporte*> getTransportes() const { return transportes; }
    std::vector<Passageiro*> getPassageiros() const { return passageiros; }
    std::vector<Viagem*> getViagens() const { return viagens; }

    // Setters para inicialização de dados lidos dos arquivos
    void setCidades(const std::vector<Cidade*>& c) { cidades = c; }
    void setTrajetos(const std::vector<Trajeto*>& t) { trajetos = t; }
    void setTransportes(const std::vector<Transporte*>& tr) { transportes = tr; }
    void setPassageiros(const std::vector<Passageiro*>& p) { passageiros = p; }
    void setViagens(const std::vector<Viagem*>& v) { viagens = v; }
};
#endif //CONTROLADOR_DE_VIAGENS_CONTROLADORDETRANSITO_HPP
