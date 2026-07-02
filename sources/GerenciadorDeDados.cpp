#include "GerenciadorDeDados.hpp"

#include <sstream>
#include <unordered_map>

std::vector<Cidade*> GerenciadorDeDados::carregarCidades(std::string nomeArquivo) {
    std::vector<Cidade*> cidades;

    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir " << nomeArquivo << "\n";
        return cidades;
    }

    std::string linha;

    while (getline(arquivo, linha)) {
        if (!linha.empty() && linha.back() == '\r') linha.pop_back();
        if (linha.empty()) continue;
        Cidade* novaCidade = new Cidade(linha);
        cidades.push_back(novaCidade);
    }
    arquivo.close();
    return cidades;
}

std::vector<Passageiro*> GerenciadorDeDados::carregarPassageiros(std::string nomeArquivo, const std::vector<Cidade*>& cidades) {
    std::vector<Passageiro*> passageiros;


    unordered_map<std::string, Cidade*> mapaCidades;
    for (int i = 0; i < cidades.size();i++) {
        mapaCidades[cidades[i]->getNome()] = cidades[i];
    }

    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir " << nomeArquivo << "\n";
        return passageiros;
    }

    std::string linha;
    int maxId = 0;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);

        string idString;
        string nome;
        string local;

        getline(ss,idString,',');
        getline(ss,nome,',');
        getline(ss,local,',');
        if (!local.empty() && local.back() == '\r') local.pop_back();

        int id = std::stoi(idString);
        if (id > maxId) maxId = id;


        //Acessa o objeto da cidade e depois cria o objeto do passageiro.
        Cidade* localAtual = mapaCidades[local];
        if (localAtual) {
            Passageiro* novoPassageiro = new Passageiro(id, nome, localAtual);
            passageiros.push_back(novoPassageiro);
        }

    }
    arquivo.close();
    Passageiro::setContadorID(maxId + 1);
    return passageiros;
}

std::vector<Trajeto *> GerenciadorDeDados::carregarTrajetos(std::string nomeArquivo, std::vector<Cidade *>& cidades) {
    std::vector<Trajeto*> trajetos;


    unordered_map<std::string, Cidade*> mapaCidades;
    for (int i = 0; i < cidades.size();i++) {
        mapaCidades[cidades[i]->getNome()] = cidades[i];
    }

    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir " << nomeArquivo << "\n";
        return trajetos;
    }

    std::string linha;
    while (getline(arquivo,linha)) {

        stringstream ss(linha);

        string origem;
        string destino;
        string tipo;
        string distanciaString;

        getline(ss, origem, ',');
        getline(ss, destino, ',');
        getline(ss, tipo, ',');
        getline(ss, distanciaString, ',');
        if (!distanciaString.empty() && distanciaString.back() == '\r') distanciaString.pop_back();

        Cidade* localOrigem = mapaCidades[origem];
        Cidade* localDestino = mapaCidades[destino];

        int distancia = std::stoi(distanciaString);

        if (localOrigem && localDestino) {
            Trajeto* novoTrajeto = new Trajeto(localOrigem,localDestino, tipo[0], distancia);
            trajetos.push_back(novoTrajeto);
        }
    }
    arquivo.close();
    return trajetos;
}

std::vector<Transporte*> GerenciadorDeDados::carregarTransportes(std::string nomeArquivo, const std::vector<Cidade*>& cidades) {
    std::vector<Transporte*> transportes;

    unordered_map<std::string, Cidade*> mapaCidades;
    for (int i = 0; i < cidades.size(); i++) {
        mapaCidades[cidades[i]->getNome()] = cidades[i];
    }

    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir " << nomeArquivo << "\n";
        return transportes;
    }

    std::string linha;
    int maxId = 0;
    while (getline(arquivo, linha)) {
        if (!linha.empty() && linha.back() == '\r') linha.pop_back();
        if (linha.empty()) continue;

        stringstream ss(linha);

        string idString, nome, tipoStr, capacidadeStr, velocidadeStr, distDescansosStr, tempoDescansoStr, localAtualStr;

        getline(ss, idString, ',');
        getline(ss, nome, ',');
        getline(ss, tipoStr, ',');
        getline(ss, capacidadeStr, ',');
        getline(ss, velocidadeStr, ',');
        getline(ss, distDescansosStr, ',');
        getline(ss, tempoDescansoStr, ',');
        getline(ss, localAtualStr, ',');
        if (!localAtualStr.empty() && localAtualStr.back() == '\r') localAtualStr.pop_back();

        string distPercorridaStr, horasDescansadasStr;
        int dist_percorrida = 0;
        int horas_descansadas = 0;
        if (getline(ss, distPercorridaStr, ',')) {
            if (getline(ss, horasDescansadasStr, ',')) {
                if (!horasDescansadasStr.empty() && horasDescansadasStr.back() == '\r') horasDescansadasStr.pop_back();
                dist_percorrida = std::stoi(distPercorridaStr);
                horas_descansadas = std::stoi(horasDescansadasStr);
            }
        }

        int id = std::stoi(idString);
        if (id > maxId) maxId = id;
        char tipo = tipoStr[0];
        int capacidade = std::stoi(capacidadeStr);
        int velocidade = std::stoi(velocidadeStr);
        int distancia_entre_descansos = std::stoi(distDescansosStr);
        int tempo_de_descanso_atual = std::stoi(tempoDescansoStr);

        Cidade* localAtual = mapaCidades[localAtualStr];
        if (localAtual || localAtualStr.empty()) {
            Transporte* novoTransporte = new Transporte(id, nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso_atual, localAtual);
            novoTransporte->setDistanciaPercorrida(dist_percorrida);
            novoTransporte->setHorasDescansadas(horas_descansadas);
            transportes.push_back(novoTransporte);
        }
    }
    arquivo.close();
    Transporte::setContadorID(maxId + 1);
    return transportes;
}

std::vector<Viagem*> GerenciadorDeDados::carregarViagens(std::string nomeArquivo, const std::vector<Transporte*>& transportes, const std::vector<Passageiro*>& passageiros, const std::vector<Cidade*>& cidades) {
    std::vector<Viagem*> viagens;

    unordered_map<int, Transporte*> mapaTransportes;
    for (int i = 0; i < transportes.size(); i++) {
        mapaTransportes[transportes[i]->getId()] = transportes[i];
    }

    unordered_map<int, Passageiro*> mapaPassageiros;
    for (int i = 0; i < passageiros.size(); i++) {
        mapaPassageiros[passageiros[i]->getId()] = passageiros[i];
    }

    unordered_map<std::string, Cidade*> mapaCidades;
    for (int i = 0; i < cidades.size(); i++) {
        mapaCidades[cidades[i]->getNome()] = cidades[i];
    }

    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir " << nomeArquivo << "\n";
        return viagens;
    }

    std::string linha;
    int maxId = 0;
    struct ViagemTempData {
        Viagem* viagem;
        int proximaId;
    };
    std::vector<ViagemTempData> viagensTemp;
    unordered_map<int, Viagem*> mapaViagens;

    while (getline(arquivo, linha)) {
        if (!linha.empty() && linha.back() == '\r') linha.pop_back();
        if (linha.empty()) continue;

        stringstream ss(linha);

        string idStr, idTransporteStr, origemStr, destinoStr, idProximaStr, horasEmTransitoStr, emAndamentoStr, ocorreuStr;

        getline(ss, idStr, ',');
        getline(ss, idTransporteStr, ',');
        getline(ss, origemStr, ',');
        getline(ss, destinoStr, ',');
        getline(ss, idProximaStr, ',');
        getline(ss, horasEmTransitoStr, ',');
        getline(ss, emAndamentoStr, ',');
        getline(ss, ocorreuStr, ',');

        int id = std::stoi(idStr);
        if (id > maxId) maxId = id;
        int idTransporte = std::stoi(idTransporteStr);
        int idProxima = std::stoi(idProximaStr);
        int horasEmTransito = std::stoi(horasEmTransitoStr);
        bool emAndamento = (emAndamentoStr == "1" || emAndamentoStr == "true");
        bool ocorreu = (ocorreuStr == "1" || ocorreuStr == "true");

        Transporte* transporte = mapaTransportes[idTransporte];
        Cidade* origem = mapaCidades[origemStr];
        Cidade* destino = mapaCidades[destinoStr];

        std::vector<Passageiro*> passList;
        int distancia = 0;
        string nextStr;
        while (getline(ss, nextStr, ',')) {
            if (!nextStr.empty() && nextStr.back() == '\r') nextStr.pop_back();
            if (!nextStr.empty()) {
                if (nextStr[0] == 'D') {
                    distancia = std::stoi(nextStr.substr(1));
                } else {
                    int idPass = std::stoi(nextStr);
                    if (mapaPassageiros.count(idPass)) {
                        passList.push_back(mapaPassageiros[idPass]);
                    }
                }
            }
        }

        if (transporte && origem && destino) {
            Viagem* novaViagem = new Viagem(id, transporte, passList, origem, destino, nullptr, horasEmTransito, emAndamento, ocorreu, distancia);
            viagensTemp.push_back({novaViagem, idProxima});
            mapaViagens[id] = novaViagem;
            viagens.push_back(novaViagem);
        }
    }

    //Segunda passagem para linkar as próximas viagens
    for (int i = 0; i < viagensTemp.size(); i++) {
        if (viagensTemp[i].proximaId != -1 && mapaViagens.count(viagensTemp[i].proximaId)) {
            viagensTemp[i].viagem->setProxima(mapaViagens[viagensTemp[i].proximaId]);
        }
    }
    arquivo.close();
    Viagem::setContadorID(maxId + 1);
    return viagens;
}

void GerenciadorDeDados::salvarCidades(std::string nomeArquivo, const std::vector<Cidade*>& cidades) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir " << nomeArquivo << " para escrita.\n";
        return;
    }
    for (int i = 0; i < cidades.size(); i++) {
        arquivo << cidades[i]->getNome() << "\n";
    }
    arquivo.close();
}

void GerenciadorDeDados::salvarPassageiros(std::string nomeArquivo, const std::vector<Passageiro*>& passageiros) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir " << nomeArquivo << " para escrita.\n";
        return;
    }
    for (int i = 0; i < passageiros.size(); i++) {
        arquivo << passageiros[i]->getId() << ","
                << passageiros[i]->getNome() << ",";
        if (passageiros[i]->getLocalAtual() != nullptr) {
            arquivo << passageiros[i]->getLocalAtual()->getNome();
        }
        arquivo << "\n";
    }
    arquivo.close();
}

void GerenciadorDeDados::salvarTrajetos(std::string nomeArquivo, const std::vector<Trajeto*>& trajetos) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir " << nomeArquivo << " para escrita.\n";
        return;
    }
    for (int i = 0; i < trajetos.size(); i++) {
        arquivo << trajetos[i]->getOrigem()->getNome() << ","
                << trajetos[i]->getDestino()->getNome() << ","
                << trajetos[i]->getTipo() << ","
                << trajetos[i]->getDistancia() << "\n";
    }
    arquivo.close();
}

void GerenciadorDeDados::salvarTransportes(std::string nomeArquivo, const std::vector<Transporte*>& transportes) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir " << nomeArquivo << " para escrita.\n";
        return;
    }
    for (int i = 0; i < transportes.size(); i++) {
        arquivo << transportes[i]->getId() << ","
                << transportes[i]->getNome() << ","
                << transportes[i]->getTipo() << ","
                << transportes[i]->getCapacidade() << ","
                << transportes[i]->getVelocidade() << ","
                << transportes[i]->getDistanciaEnteDescansos() << ","
                << transportes[i]->getTempoDeDescansoAtual() << ",";
        if (transportes[i]->getLocalAtual() != nullptr) {
            arquivo << transportes[i]->getLocalAtual()->getNome();
        }
        arquivo << "," << transportes[i]->getDistanciaPercorrida() << ","
                << transportes[i]->getHorasDescansadas() << "\n";
    }
    arquivo.close();
}

void GerenciadorDeDados::salvarViagens(std::string nomeArquivo, const std::vector<Viagem*>& viagens) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir " << nomeArquivo << " para escrita.\n";
        return;
    }
    for (int i = 0; i < viagens.size(); i++) {
        arquivo << viagens[i]->getId() << ","
                << viagens[i]->getTransporte()->getId() << ","
                << viagens[i]->getOrigem()->getNome() << ","
                << viagens[i]->getDestino()->getNome() << ",";
        
        if (viagens[i]->getProxima() != nullptr) {
            arquivo << viagens[i]->getProxima()->getId() << ",";
        } else {
            arquivo << "-1,";
        }

        arquivo << viagens[i]->getHorasEmTransito() << ","
                << viagens[i]->isEmAndamento() << ","
                << viagens[i]->isOcorreu() << ","
                << "D" << viagens[i]->getDistancia();
        
        std::vector<Passageiro*> passList = viagens[i]->getPassageiros();
        if (!passList.empty()) {
            arquivo << ",";
            for (int j = 0; j < passList.size(); j++) {
                arquivo << passList[j]->getId();
                if (j < passList.size() - 1) {
                    arquivo << ",";
                }
            }
        }
        arquivo << "\n";
    }
    arquivo.close();
}
