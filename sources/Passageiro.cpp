#include "Passageiro.hpp"

int Passageiro::contadorID = 1;

Passageiro::Passageiro(std::string nome, Cidade *localAtual) {
    this->id = contadorID;
    contadorID++;
    this->nome = nome;
    this->localAtual = localAtual;
}

Passageiro::Passageiro(int idExistente, std::string nome, Cidade *localAtual) {
    this->id = idExistente;
    this->nome = nome;
    this->localAtual = localAtual;
}

int Passageiro::getId() const {
    return this->id;
}

void Passageiro::setContadorID(int novoValor) {
    contadorID = novoValor;
}

std::string Passageiro::getNome() {
    return this->nome;
}

Cidade *Passageiro::getLocalAtual() {
    return this->localAtual;
}

void Passageiro::setLocalAtual(Cidade* local) {
    this->localAtual = local;
}