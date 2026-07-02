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
    static std::vector<Cidade*> carregarCidades(std::string nomeArquivo);

    static std::vector<Passageiro*> carregarPassageiros(std::string nomeArquivo, std::vector<Cidade*>& cidades);

    static std::vector<Trajeto*> carregarTrajetos(std::string nomeArquivo, std::vector<Cidade*>& cidades);

    static std::vector<Transporte*> carregarTransportes(std::string nomeArquivo, const std::vector<Cidade*>& cidades);

    static std::vector<Viagem*> carregarViagens(std::string nomeArquivo, const std::vector<Transporte*>& transportes, const std::vector<Passageiro*>& passageiros, const std::vector<Cidade*>& cidades);
};

#endif //CONTROLADOR_DE_VIAGENS_GERENCIADORDEDADOS_HPP
