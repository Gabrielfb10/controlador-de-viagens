//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_PASSAGEIRO_HPP
#define CONTROLADOR_DE_VIAGENS_PASSAGEIRO_HPP

#include <string>

#include "Cidade.hpp"

class Passageiro {
private:
    static int contadorID; // Gerador automático de IDs
    int id;                // Identificador único do passageiro
    std::string nome;      // Nome do passageiro
    Cidade* localAtual;    // Ponteiro para a cidade onde o passageiro se encontra atualmente
public:
    // Cria um novo passageiro com ID gerado automaticamente
    Passageiro(std::string nome, Cidade* localAtual);
    // Cria um passageiro com ID existente (usado no carregamento de dados)
    Passageiro(int idExistente, std::string nome, Cidade* localAtual);
    
    int getId() const;
    static void setContadorID(int novoValor);
    std::string getNome();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};

#endif //CONTROLADOR_DE_VIAGENS_PASSAGEIRO_HPP
