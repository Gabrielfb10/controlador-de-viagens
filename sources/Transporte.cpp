#include "Transporte.hpp"

int Transporte::contadorID = 1;

Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso_atual, Cidade *localAtual) {
    this->id = contadorID;
    contadorID++;
    this->nome = nome;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->velocidade = velocidade;
    this->distancia_entre_descansos = distancia_entre_descansos;
    this->tempo_de_descanso_atual = tempo_de_descanso_atual;
    this->localAtual = localAtual;
    this->distancia_percorrida = 0;
    this->horas_descansadas = 0;
}

Transporte::Transporte(int idExistente, std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso_atual, Cidade *localAtual) {
    this->id = idExistente;
    this->nome = nome;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->velocidade = velocidade;
    this->distancia_entre_descansos = distancia_entre_descansos;
    this->tempo_de_descanso_atual = tempo_de_descanso_atual;
    this->localAtual = localAtual;
    this->distancia_percorrida = 0;
    this->horas_descansadas = 0;
}

int Transporte::getId() const {
    return this->id;
}

void Transporte::setContadorID(int novoValor) {
    contadorID = novoValor;
}

std::string  Transporte::getNome() {
    return this->nome;
}

char Transporte::getTipo() {
    return this->tipo;
}

int Transporte::getCapacidade() {
    return this->capacidade;
}


int Transporte::getVelocidade() {
    return this->velocidade;
}

int Transporte::getDistanciaEnteDescansos() {
   return this->distancia_entre_descansos;
}

int Transporte::getTempoDeDescansoAtual() {
    return this->tempo_de_descanso_atual;
}

Cidade* Transporte::getLocalAtual() {
    return this->localAtual;
}

void Transporte::setLocalAtual(Cidade* local) {
    this->localAtual = local;
}

int Transporte::getDistanciaPercorrida() {
    return this->distancia_percorrida;
}

void Transporte::setDistanciaPercorrida(int dist) {
    this->distancia_percorrida = dist;
}

void Transporte::adicionarDistancia(int dist) {
    this->distancia_percorrida += dist;
}

int Transporte::getHorasDescansadas() {
    return this->horas_descansadas;
}

void Transporte::setHorasDescansadas(int horas) {
    this->horas_descansadas = horas;
}

void Transporte::adicionarHoraDescanso() {
    this->horas_descansadas++;
}

void Transporte::resetarDescanso() {
    this->distancia_percorrida = 0;
    this->horas_descansadas = 0;
}
