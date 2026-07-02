#include "ControladorDeTransito.hpp"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
// Estrutura apenas para auxiliar no problema de busca do melhor trajeto
struct NoBusca {
    int custoMinimo;
    Trajeto* trajetoChegada;
    bool visitado;

    NoBusca() {
        this->custoMinimo = 999999999;
        this->trajetoChegada = nullptr;
        this->visitado = false;
    }
};

std::vector<Trajeto*> ControladorDeTransito::melhorTrajeto(Cidade* origem, Cidade* destino, char tipoTransporte) {

    //Cria um hash_map para armazenar as informações do algoritmo de Dijkstra
    std::unordered_map<Cidade*, NoBusca> mapaCidades;
    for (int i = 0; i < cidades.size(); i++) {
        mapaCidades[cidades[i]] = NoBusca();
    }

    //Define a distancia da origem
    mapaCidades[origem].custoMinimo = 0;
    
    //Cria uma fila de prioridade para auxiliar no problema de busca
    typedef std::pair<int, Cidade*> Estado; 
    std::priority_queue<Estado, std::vector<Estado>, std::greater<Estado>> fila;

    fila.push({0, origem});

    //Loop que realiza a busca
    while (!fila.empty()) {
        
        // Extrai a cidade mais próxima do topo da fila
        int distAtual = fila.top().first;
        Cidade* cidadeAtual = fila.top().second;
        fila.pop();

        //Ignora cidades visitadas
        if (mapaCidades[cidadeAtual].visitado) {
            continue; 
        }

        //Marca a cidade como visitada
        mapaCidades[cidadeAtual].visitado = true;

        //Em caso de ser o destino, finaliza a busca
        if (cidadeAtual == destino) {
            break;
        }

        //Busca dos vizinhos, ou seja, cidades que recebem trajeto desse local
        for (Trajeto* t : this->trajetos) {
            
            //Validação para confirmar que o trajeto parte da cidade que está sendo analisada e possui o tipo compatível
            if (t->getOrigem() == cidadeAtual && t->getTipo() == tipoTransporte) {
                Cidade* vizinho = t->getDestino();
                int pesoDoTrajeto = t->getDistancia();

                //Checa se a cidade vizinha não foi visitada e se foi achado um caminho menor que o já registrado para ela
                if (!mapaCidades[vizinho].visitado && 
                    mapaCidades[cidadeAtual].custoMinimo + pesoDoTrajeto < mapaCidades[vizinho].custoMinimo) {

                    //Atualiza as informações da cidade vizinha
                    mapaCidades[vizinho].custoMinimo = mapaCidades[cidadeAtual].custoMinimo + pesoDoTrajeto;
                    mapaCidades[vizinho].trajetoChegada = t;
                    
                    //Adiciona a cidade vizinha a fila de prioridade
                    fila.push({mapaCidades[vizinho].custoMinimo, vizinho});
                }
            }
        }
    }

    //Vetor que vai armazenas os trajetos para chegar até o destino
    std::vector<Trajeto*> caminhoFinal;

    //Checa se o destino não tem um trajeto de chegada e se não é a origem
    if (mapaCidades[destino].trajetoChegada == nullptr && origem != destino) {
        std::cout << "ERRO: Nao existe rota possivel entre as cidades informadas.\n";
        return caminhoFinal;
    }

    Cidade* passoAtual = destino;

    // Vamos voltar as migalhas até bater na origem
    while (passoAtual != origem) {
        // Pega o trajeto que conectou até o passoAtual
        Trajeto* rodoviaUsada = mapaCidades[passoAtual].trajetoChegada;

        // Guarda na resposta
        caminhoFinal.push_back(rodoviaUsada);

        // O próximo passo para trás é a origem dessa rodovia!
        passoAtual = rodoviaUsada->getOrigem();
    }

    // O caminho foi construído do Destino para a Origem, então invertemos:
    std::reverse(caminhoFinal.begin(), caminhoFinal.end());

    // Exemplo de impressão do log para o usuário:
    std::cout << "ROTA ENCONTRADA! Custo total: " << mapaCidades[destino].custoMinimo << "\n";
    std::cout << "Trajetos a percorrer:\n";
    for (Trajeto* t : caminhoFinal) {
        std::cout << " - De " << t->getOrigem()->getNome() << " para " << t->getDestino()->getNome() << " (Distancia: " << t->getDistancia() << ")\n";
    }

    return caminhoFinal;
}

void ControladorDeTransito::cadastrarCidade(std::string nome) {
    //Evita cidades duplicatas
    for (int i = 0; i < cidades.size(); i++) {
        if (cidades[i]->getNome() == nome) {
            std::cout << "ERRO: A cidade '" << nome << "' ja esta cadastrada no sistema!\n";
            return;
        }
    }

    //Cria a cidade e adiciona a lista de cidades
    Cidade* novaCidade = new Cidade(nome);
    this->cidades.push_back(novaCidade);
    std::cout << "Cidade '" << nome << "' cadastrada com sucesso!\n";
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
    Cidade* cidadeOrigem = nullptr;
    Cidade* cidadeDestino = nullptr;

    int verificador = 0;

    //Checa se as cidades existem
    for (int i = 0; i < cidades.size(); i++) {
        //Cria objeto com a cidade de origem
        if (cidades[i]->getNome() == nomeOrigem) {
            cidadeOrigem = cidades[i];
            verificador += 1;
        }
        //Cria objeto com a cidade de destino
        if (cidades[i]->getNome() == nomeDestino) {
            cidadeDestino = cidades[i];
            verificador += 1;
        }
    }

    //Através do verificador, checa se existe uma cidade de origem e de destino
    if (verificador != 2) {
        std::cout << "ERRO: Cidade de origem ou destino nao encontrada no sistema!\n";
        return;
    }

    //Cria objeto do novo trajeto e adiciona a lista de trajetos
    Trajeto* novoTrajeto = new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia);
    trajetos.push_back(novoTrajeto);
    std::cout << "Trajeto de " << nomeOrigem << " para " << nomeDestino << " cadastrado com sucesso!\n";
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual) {

    //Checa se a cidade existe, acessa o objeto da cidade e depois cria o objeto do transporte.
    Cidade* local = nullptr;
    for (int i = 0; i < cidades.size(); i++) {
        if (cidades[i]->getNome() == localAtual) {
            local = cidades[i];
            Transporte* novoTransporte = new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local);
            transportes.push_back(novoTransporte);
            std::cout << "Transporte '" << nome << "' (ID: " << novoTransporte->getId() << ") cadastrado com sucesso!\n";
            return;
        }
    }
    std::cout << "ERRO: A cidade '" << localAtual << "' não existe!\n";
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {

    //Checa se a cidade existe, acessa o objeto da cidade e depois cria o objeto do passageiro.
    Cidade* local = nullptr;
    for (int i = 0; i < cidades.size(); i++) {
        if (cidades[i]->getNome() == localAtual) {
            local = cidades[i];
            Passageiro* novoPassageiro = new Passageiro(nome, local);
            passageiros.push_back(novoPassageiro);
            std::cout << "Passageiro '" << nome << "' (ID: " << novoPassageiro->getId() << ") cadastrado com sucesso!\n";
            return;
        }
    }
    std::cout << "ERRO: A cidade '" << localAtual << "' não existe!\n";
}

void ControladorDeTransito::iniciarViagem(int idTransporte, std::vector<int> idsPassageiros, std::string nomeOrigem, std::string nomeDestino) {

    //Checa se o transporte existe e acessa o objeto
    Transporte* transporte = nullptr;
    for (int i = 0; i < transportes.size(); i++) {
        if (transportes[i]->getId() == idTransporte) {
            transporte = transportes[i];
            break;
        }
    }

    //Checa se o transporte foi encontrado
    if (!transporte) {
        std::cout << "ERRO: O transporte com ID '" << idTransporte << "' nao existe!\n";
        return;

    }

    //Checa se todos os passageiros da viagem estão cadastrados no sistema e armazena os objetos em uma nova lista
    std::vector<Passageiro*> passageirosViagem;
    for (int i = 0; i < idsPassageiros.size(); i++) {
        for (int j = 0; j < passageiros.size(); j++) {
            if (passageiros[j]->getId() == idsPassageiros[i]) {
                passageirosViagem.push_back(passageiros[j]);
                break;
            }
        }
    }

    //Checa se todos os passageiros foram encontrados
    if (idsPassageiros.size() != passageirosViagem.size()) {
        std::cout << "ERRO: Um ou mais passageiros informados nao foram encontrados no sistema!\n";
        return;
    }

    Cidade* cidadeOrigem = nullptr;
    Cidade* cidadeDestino = nullptr;

    int verificador = 0;

    //Checa se as cidades existem
    for (int i = 0; i < cidades.size(); i++) {
        //Cria objeto com a cidade de origem
        if (cidades[i]->getNome() == nomeOrigem) {
            cidadeOrigem = cidades[i];
            verificador += 1;
        }
        //Cria objeto com a cidade de destino
        if (cidades[i]->getNome() == nomeDestino) {
            cidadeDestino = cidades[i];
            verificador += 1;
        }
    }

    //Através do verificador, checa se existe uma cidade de origem e de destino
    if (verificador != 2) {
        std::cout << "ERRO: Cidade de origem ou destino nao encontrada no sistema!\n";
        return;
    }

    //Checa a localização do transporte e capacidade antes de criar a viagem
    if (transporte->getLocalAtual() != cidadeOrigem) {
        std::cout << "ERRO: O transporte '" << transporte->getNome() << "' nao esta na cidade de origem (" << cidadeOrigem->getNome() << "). A viagem nao foi criada.\n";
        return;
    }

    if (transporte->getCapacidade() < passageirosViagem.size()) {
        std::cout << "ERRO: Capacidade insuficiente do transporte para o numero de passageiros. A viagem nao foi criada.\n";
        return;
    }

    //Checa se todos os passageiros estao na cidade de origem
    for (int i = 0; i < passageirosViagem.size(); i++) {
        if (passageirosViagem[i]->getLocalAtual() != cidadeOrigem) {
            std::cout << "ERRO: O passageiro '" << passageirosViagem[i]->getNome() << "' (ID: " << passageirosViagem[i]->getId() << ") nao esta na cidade de origem (" << cidadeOrigem->getNome() << "). A viagem nao foi criada.\n";
            return;
        }
    }

    //Chama a função que busca o melhor trajeto compatível com o tipo de transporte
    std::vector<Trajeto*> trajeto = melhorTrajeto(cidadeOrigem, cidadeDestino, transporte->getTipo());

    //Checa se algum trajeto foi encontrado
    if (trajeto.empty()) {
        return;
    }

    //Vetor para armazenar cada viagem que o trajeto irá fazer
    std::vector<Viagem*> viagensTrajeto;
    Viagem* viagemAnterior = nullptr;

    //Laço para criar todas as viagens do trajeto
    for (int i = 0; i < trajeto.size(); i++) {

        Cidade* origemTrecho = trajeto[i]->getOrigem();
        Cidade* destinoTrecho = trajeto[i]->getDestino();
        int distancia = trajeto[i]->getDistancia();

        Viagem* novaViagem = new Viagem(transporte, passageirosViagem, origemTrecho, destinoTrecho, distancia, nullptr);

        viagensTrajeto.push_back(novaViagem);

        if (viagemAnterior != nullptr) {
            viagemAnterior->setProxima(novaViagem);
        }

        viagemAnterior = novaViagem;
    }

    //Laço para inserir cada viagem criada na lista de todas as viagens
    for (int i = 0; i < viagensTrajeto.size(); i++) {
        viagens.push_back(viagensTrajeto[i]);
    }

    viagensTrajeto.front()->iniciarViagem();
}

void ControladorDeTransito::avancarHoras(int horas) {
    std::cout << "\n===================================================\n";
    std::cout << "               AVANCANDO O TEMPO (" << horas << "h)              \n";
    std::cout << "===================================================\n";
    for (int h = 1; h <= horas; h++) {
        std::cout << "\n--- HORA " << h << " ---\n";
        bool teveAcao = false;
        
        // Salva o estado de quem estava rodando no INICIO da hora.
        // Isso impede que viagens iniciadas no meio desta hora viajem imediatamente.
        std::vector<bool> rodandoNoInicioDaHora(viagens.size());
        for (int i = 0; i < viagens.size(); i++) {
            rodandoNoInicioDaHora[i] = viagens[i]->isEmAndamento();
        }

        // Itera para frente, assim os logs aparecem em ordem crescente (do ID menor pro maior)
        for (int i = 0; i < viagens.size(); i++) {
            if (rodandoNoInicioDaHora[i]) {
                viagens[i]->avancarHoras();
                teveAcao = true;
            }
        }
        
        if (!teveAcao) {
            std::cout << " Nenhuma viagem em andamento no momento.\n";
            break; 
        }
    }
    std::cout << "===================================================\n";
}

void ControladorDeTransito::relatarEstado() {
    std::cout << "\n===================================================\n";
    std::cout << "            RELATORIO DE ESTADO DO TRANSITO        \n";
    std::cout << "===================================================\n";

    // Contadores para o resumo final
    int concluidas = 0;
    int rodando = 0;
    int aguardando = 0;

    //Checa se há viagens cadastradas
    if (viagens.empty()) {
        std::cout << "Nenhuma viagem cadastrada no sistema no momento.\n";
        std::cout << "===================================================\n";
        return;
    }

    std::cout << "--- STATUS DETALHADO DOS TRECHOS ---\n";

    //Percorre o vetor listando o status de cada viagem
    for (int i = 0; i < viagens.size(); i++) {
        viagens[i]->relatarEstado();
        if (viagens[i]->isEmAndamento()) {
            rodando++;
        } else if (viagens[i]->isOcorreu()) {
            concluidas++;
        } else {
            aguardando++;
        }
    }

    std::cout << "\n--- RESUMO DO SISTEMA ---\n";
    std::cout << "Total de trechos monitorados : " << this->viagens.size() << "\n";
    std::cout << "Trechos ja finalizados       : " << concluidas << "\n";
    std::cout << "Trechos na estrada agora     : " << rodando << "\n";
    std::cout << "Trechos aguardando partida   : " << aguardando << "\n";

    std::cout << "===================================================\n\n";
}



