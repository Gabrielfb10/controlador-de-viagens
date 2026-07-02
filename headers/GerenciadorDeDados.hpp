//
// Created by gabig on 01/07/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_GERENCIADORDEDADOS_HPP
#define CONTROLADOR_DE_VIAGENS_GERENCIADORDEDADOS_HPP

#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"
#include "Transporte.hpp"
#include "Viagem.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class GerenciadorDeDados {
public:
    // Métodos estáticos para carregar os arquivos de texto e instanciar os objetos
    static std::vector<Cidade*> carregarCidades(std::string nomeArquivo);
    static std::vector<Passageiro*> carregarPassageiros(std::string nomeArquivo, const std::vector<Cidade*>& cidades);
    static std::vector<Trajeto*> carregarTrajetos(std::string nomeArquivo, std::vector<Cidade*>& cidades);
    static std::vector<Transporte*> carregarTransportes(std::string nomeArquivo, const std::vector<Cidade*>& cidades);
    static std::vector<Viagem*> carregarViagens(std::string nomeArquivo, const std::vector<Transporte*>& transportes, const std::vector<Passageiro*>& passageiros, const std::vector<Cidade*>& cidades);

    // Métodos estáticos para salvar o estado atual do sistema de volta para os arquivos de texto
    static void salvarCidades(std::string nomeArquivo, const std::vector<Cidade*>& cidades);
    static void salvarPassageiros(std::string nomeArquivo, const std::vector<Passageiro*>& passageiros);
    static void salvarTrajetos(std::string nomeArquivo, const std::vector<Trajeto*>& trajetos);
    static void salvarTransportes(std::string nomeArquivo, const std::vector<Transporte*>& transportes);
    static void salvarViagens(std::string nomeArquivo, const std::vector<Viagem*>& viagens);
};

#endif //CONTROLADOR_DE_VIAGENS_GERENCIADORDEDADOS_HPP
