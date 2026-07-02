#include <iostream>
#include <algorithm>
#include "Viagem.hpp"

int Viagem::contadorID = 1;

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;

//Inicialização padrão
    this->proxima = nullptr;
    this->horasEmTransito = 0;
    this->emAndamento = false;
    this->ocorreu = false;

    //Atribuição de um ID único e atualização do contador
    this->id = contadorID;
    contadorID++;
}

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia, Viagem* proxima) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->proxima = proxima;
    this->distancia = distancia;

    //Inicialização padrão
    this->horasEmTransito = 0;
    this->emAndamento = false;
    this->ocorreu = false;

    //Atribuição de um ID único e atualização do contador
    this->id = contadorID;
    contadorID++;
}

//Construtor para criar objetos a partir do arquivo txt
Viagem::Viagem(int idExistente, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, Viagem* proxima, int horasEmTransito, bool emAndamento, bool ocorreu, int distancia) {
    this->id = idExistente;
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->proxima = proxima;


    this->horasEmTransito = horasEmTransito;
    this->emAndamento = emAndamento;
    this->ocorreu = ocorreu;
    this->distancia = distancia;

}

void Viagem::iniciarViagem() {

    this->emAndamento = true;
    this->transporte->setLocalAtual(nullptr);
    for (int i = 0; i < this->passageiros.size(); i++) {
        this->passageiros[i]->setLocalAtual(nullptr);
    }

    std::cout << "\nViagem " << this->id << " iniciada!\n";
    std::cout << " - Veiculo na estrada.\n";
    std::cout << " - Saindo de: " << this->origem->getNome() << "\n";
    std::cout << " - Rumo a: " << this->destino->getNome() << "\n";

}

void Viagem::avancarHoras() {
    if (this->transporte->getDistanciaEnteDescansos() > 0 && this->transporte->getDistanciaPercorrida() >= this->transporte->getDistanciaEnteDescansos()) {
        this->transporte->adicionarHoraDescanso();
        this->horasEmTransito += 1;
        
        std::cout << " [Viagem " << this->id << "] " << this->transporte->getNome() << " esta descansando. (" 
                  << this->transporte->getHorasDescansadas() << "/" << this->transporte->getTempoDeDescansoAtual() << " horas de descanso concluidas)\n";
        
        if (this->transporte->getHorasDescansadas() >= this->transporte->getTempoDeDescansoAtual()) {
            std::cout << " [Viagem " << this->id << "] " << this->transporte->getNome() << " terminou o descanso apos percorrer " << this->transporte->getDistanciaPercorrida() << " km e estara pronto para continuar!\n";
            this->transporte->resetarDescanso();
        }
    } else {
        this->horasEmTransito += 1;
        int distSendoPercorrida = std::min(this->distancia, this->transporte->getVelocidade());
        this->distancia -= distSendoPercorrida;
        this->transporte->adicionarDistancia(distSendoPercorrida);
        
        std::cout << " [Viagem " << this->id << "] " << this->transporte->getNome() << " viajou " << distSendoPercorrida << " km (Faltam " << this->distancia << " km).\n";
        
        if (this->distancia > 0 && this->transporte->getDistanciaEnteDescansos() > 0 && this->transporte->getDistanciaPercorrida() >= this->transporte->getDistanciaEnteDescansos()) {
            std::cout << " [Viagem " << this->id << "] " << this->transporte->getNome() << " atingiu o limite de " << this->transporte->getDistanciaPercorrida() << " km percorridos e estacionou para descansar!\n";
        }
        
        if (this->distancia <= 0) {
            this->setEmAndamento(false);
            this->setOcorreu(true);
            this->transporte->setLocalAtual(this->destino);
            for (int i = 0; i < this->passageiros.size(); i++) {
                this->passageiros[i]->setLocalAtual(this->destino);
            }
            std::cout << " [Viagem " << this->id << "] Viagem finalizada! Chegou ao destino: " << this->destino->getNome() << ".\n";
            if (this->proxima != nullptr) {
                this->proxima->iniciarViagem();
            }
        }
    }
}

void Viagem::relatarEstado() {
    std::cout << "\n--- STATUS DA VIAGEM " << this->id << " ---\n";
    std::cout << "Origem: " << this->origem->getNome() << " | Destino: " << this->destino->getNome() << "\n";

    if (this->emAndamento) {
        std::cout << "Estado: Em andamento (" << this->horasEmTransito << " horas de viagem decorridas)\n";
        std::cout << "Transporte: " << this->transporte->getNome() << "\n";
        std::cout << "Passageiros (" << this->passageiros.size() << "):\n";
        for (int i = 0; i < this->passageiros.size(); i++) {
            std::cout << "  - " << this->passageiros[i]->getNome() << " (ID: " << this->passageiros[i]->getId() << ")\n";
        }
    } else if (this->ocorreu){
        std::cout << "Estado: Finalizada.\n";
    } else {
        std::cout << "Estado: Aguardando inicio.\n";
    }
}

void Viagem::setProxima(Viagem *proxima) {
    this->proxima = proxima;
}

Transporte* Viagem::getTransporte() {
    return this->transporte;
}

std::vector<Passageiro*> Viagem::getPassageiros() {
    return this->passageiros;
}

Cidade* Viagem::getOrigem() {
    return this->origem;
}

Cidade* Viagem::getDestino() {
    return this->destino;
}

Viagem* Viagem::getProxima() {
    return this->proxima;
}

int Viagem::getHorasEmTransito() {
    return this->horasEmTransito;
}

int Viagem::getDistancia() {
    return this->distancia;
}


void Viagem::setContadorID(int novoValor) {
    contadorID = novoValor;
}

void Viagem::setEmAndamento(bool estado) {
    this->emAndamento = estado;
}

void Viagem::setOcorreu(bool estado) {
    this->ocorreu = estado;
}


bool Viagem::isEmAndamento() {
    return emAndamento;
}

bool Viagem::isOcorreu() {
    return ocorreu;
}

int Viagem::getId() const {
    return id;
}

//IMPLEMENTAR FUNÇÃO QUE INICIALIZA OS ARQUIVOS