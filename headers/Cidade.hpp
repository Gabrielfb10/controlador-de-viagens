//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_CIDADE_HPP
#define CONTROLADOR_DE_VIAGENS_CIDADE_HPP

#include <string>

class Cidade {
private:
    std::string nome; // Nome da cidade
public:
    // Construtor
    Cidade(std::string nome);

    // Retorna o nome da cidade
    std::string getNome();
};

#endif //CONTROLADOR_DE_VIAGENS_CIDADE_HPP
