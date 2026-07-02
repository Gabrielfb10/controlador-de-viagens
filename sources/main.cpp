#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "../headers/ControladorDeTransito.hpp"
#include "../headers/GerenciadorDeDados.hpp"

using namespace std;

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void exibirMenu() {
    cout << "\n=========================================\n";
    cout << "          CONTROLADOR DE VIAGENS         \n";
    cout << "=========================================\n";
    cout << "1. Cadastrar Cidade\n";
    cout << "2. Cadastrar Trajeto\n";
    cout << "3. Cadastrar Transporte\n";
    cout << "4. Cadastrar Passageiro\n";
    cout << "5. Iniciar Viagem\n";
    cout << "6. Avancar Horas\n";
    cout << "7. Relatar Estado do Transito\n";
    cout << "8. Salvar Dados\n";
    cout << "0. Sair\n";
    cout << "=========================================\n";
    cout << "Escolha uma opcao: ";
}

void carregarDadosIniciais(ControladorDeTransito& controlador, const string& prefixo) {
    auto cidades = GerenciadorDeDados::carregarCidades(prefixo + "cidade.txt");
    controlador.setCidades(cidades);
    
    auto passageiros = GerenciadorDeDados::carregarPassageiros(prefixo + "passageiro.txt", cidades);
    controlador.setPassageiros(passageiros);
    
    auto trajetos = GerenciadorDeDados::carregarTrajetos(prefixo + "trajeto.txt", cidades);
    controlador.setTrajetos(trajetos);
    
    auto transportes = GerenciadorDeDados::carregarTransportes(prefixo + "transporte.txt", cidades);
    controlador.setTransportes(transportes);
    
    auto viagens = GerenciadorDeDados::carregarViagens(prefixo + "viagem.txt", transportes, passageiros, cidades);
    controlador.setViagens(viagens);
}

int main() {
    ControladorDeTransito controlador;
    int opcao = -1;

    string prefixo = "data/";
    
    // Carregamento automatico no inicio
    carregarDadosIniciais(controlador, prefixo);
    cout << "Dados carregados automaticamente ao iniciar o sistema!\n";

    while (opcao != 0) {
        exibirMenu();
        if (!(cin >> opcao)) {
            limparBuffer();
            cout << "Entrada invalida. Tente novamente.\n";
            opcao = -1;
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1: {
                string nomeCidade;
                cout << "Digite o nome da cidade: ";
                getline(cin, nomeCidade);
                controlador.cadastrarCidade(nomeCidade);
                break;
            }
            case 2: {
                string origem, destino;
                char tipo;
                int distancia;
                cout << "--- Cidades disponiveis ---\n";
                for (auto c : controlador.getCidades()) {
                    cout << " - " << c->getNome() << "\n";
                }
                cout << "---------------------------\n";
                cout << "Nome da cidade de origem: ";
                getline(cin, origem);
                cout << "Nome da cidade de destino: ";
                getline(cin, destino);
                cout << "Tipo do trajeto (letra): ";
                cin >> tipo;
                cout << "Distancia (km): ";
                cin >> distancia;
                limparBuffer();
                controlador.cadastrarTrajeto(origem, destino, tipo, distancia);
                break;
            }
            case 3: {
                string nome, localAtual;
                char tipo;
                int capacidade, velocidade, distDescanso, tempoDescanso;
                cout << "Nome do transporte: ";
                getline(cin, nome);
                cout << "Tipo (A ou T): ";
                cin >> tipo;
                cout << "Capacidade (passageiros): ";
                cin >> capacidade;
                cout << "Velocidade (km/h): ";
                cin >> velocidade;
                cout << "Distancia entre descansos (km): ";
                cin >> distDescanso;
                cout << "Tempo de descanso (horas): ";
                cin >> tempoDescanso;
                limparBuffer();
                cout << "--- Cidades disponiveis ---\n";
                for (auto c : controlador.getCidades()) {
                    cout << " - " << c->getNome() << "\n";
                }
                cout << "---------------------------\n";
                cout << "Local atual (nome da cidade): ";
                getline(cin, localAtual);
                controlador.cadastrarTransporte(nome, tipo, capacidade, velocidade, distDescanso, tempoDescanso, localAtual);
                break;
            }
            case 4: {
                string nome, localAtual;
                cout << "Nome do passageiro: ";
                getline(cin, nome);
                cout << "--- Cidades disponiveis ---\n";
                for (auto c : controlador.getCidades()) {
                    cout << " - " << c->getNome() << "\n";
                }
                cout << "---------------------------\n";
                cout << "Local atual (nome da cidade): ";
                getline(cin, localAtual);
                controlador.cadastrarPassageiro(nome, localAtual);
                break;
            }
            case 5: {
                int idTransporte;
                int numPassageiros;
                vector<int> idsPassageiros;
                string origem, destino;
                cout << "--- Transportes disponiveis ---\n";
                for (auto t : controlador.getTransportes()) {
                    cout << " - ID: " << t->getId() << " | Nome: " << t->getNome();
                    if (t->getLocalAtual() != nullptr) {
                        cout << " | Local Atual: " << t->getLocalAtual()->getNome() << "\n";
                    } else {
                        cout << " | Local Atual: Em transito\n";
                    }
                }
                cout << "-------------------------------\n";
                cout << "ID do transporte: ";
                cin >> idTransporte;
                cout << "Quantidade de passageiros: ";
                cin >> numPassageiros;
                for (int i = 0; i < numPassageiros; i++) {
                    int id;
                    cout << "ID do passageiro " << (i + 1) << ": ";
                    cin >> id;
                    idsPassageiros.push_back(id);
                }
                limparBuffer();
                cout << "--- Cidades disponiveis ---\n";
                for (auto c : controlador.getCidades()) {
                    cout << " - " << c->getNome() << "\n";
                }
                cout << "---------------------------\n";
                cout << "Cidade de origem: ";
                getline(cin, origem);
                cout << "Cidade de destino: ";
                getline(cin, destino);
                controlador.iniciarViagem(idTransporte, idsPassageiros, origem, destino);
                break;
            }
            case 6: {
                int horas;
                cout << "Horas para avancar (h): ";
                cin >> horas;
                limparBuffer();
                controlador.avancarHoras(horas);
                break;
            }
            case 7: {
                controlador.relatarEstado();
                break;
            }
            case 8: {
                GerenciadorDeDados::salvarCidades(prefixo + "cidade.txt", controlador.getCidades());
                GerenciadorDeDados::salvarPassageiros(prefixo + "passageiro.txt", controlador.getPassageiros());
                GerenciadorDeDados::salvarTrajetos(prefixo + "trajeto.txt", controlador.getTrajetos());
                GerenciadorDeDados::salvarTransportes(prefixo + "transporte.txt", controlador.getTransportes());
                GerenciadorDeDados::salvarViagens(prefixo + "viagem.txt", controlador.getViagens());
                cout << "Dados salvos com sucesso na pasta '" << prefixo << "'!\n";
                break;
            }
            case 0:
                cout << "As informacoes nao salvas serao perdidas. Saindo do sistema...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    }

    return 0;
}
