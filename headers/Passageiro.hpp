//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_PASSAGEIRO_HPP
#define CONTROLADOR_DE_VIAGENS_PASSAGEIRO_HPP

#include <string>

#include "Cidade.hpp"

class Passageiro {
private:
    static int contadorID;
    int id;
    std::string nome;
    Cidade* localAtual;
public:
    Passageiro(std::string nome, Cidade* localAtual);
    Passageiro(int idExistente, std::string nome, Cidade* localAtual);
    int getId() const;
    static void setContadorID(int novoValor);
    std::string getNome();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};

#endif //CONTROLADOR_DE_VIAGENS_PASSAGEIRO_HPP
