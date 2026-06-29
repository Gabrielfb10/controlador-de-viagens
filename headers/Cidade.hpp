//
// Created by gabig on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_CIDADE_HPP
#define CONTROLADOR_DE_VIAGENS_CIDADE_HPP

#include <string>

class Cidade {
private:
    std::string nome;
public:
    Cidade(std::string nome);

    std::string getNome();
};

#endif //CONTROLADOR_DE_VIAGENS_CIDADE_HPP
