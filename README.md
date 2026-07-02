# Controlador de Viagens

Projeto em C++ para controle e gerenciamento de viagens.

## Como Executar

### Pré-requisitos
- Baixar a pasta do projeto e extrair a pasta do arquivo zip.
- Um compilador C++ (`g++` / MinGW no Windows ou GCC no Linux/Mac).
- (Opcional) utilitário `make`.

### Opção 1: Usando `make` (Recomendado)

Abra o terminal na pasta raiz do projeto e digite:

```bash
# Para compilar e rodar automaticamente
make run
```

*(No Windows com MinGW, o comando pode ser `mingw32-make run` dependendo de como foi instalado).*

Para apagar os arquivos compilados, você pode rodar `make clean`.

### Opção 2: Compilação via linha de comando manual

Se você não tiver o `make` instalado, não tem problema. Abra o terminal na pasta principal do projeto (onde ficam as pastas `data`, `sources` e `headers`) e rode o comando:

**1. Compilar o projeto:**
```bash
g++ -I headers -Wall -Wextra -std=c++17 sources/*.cpp -o controlador_viagens
```

**2. Executar o projeto:**

No **Windows**:
```cmd
controlador_viagens.exe
```
*(Se estiver usando PowerShell, use `.\controlador_viagens.exe`)*

No **Linux / macOS**:
```bash
./controlador_viagens
```

> **⚠️ Atenção:** É obrigatório que o terminal esteja na mesma pasta que contém a pasta `data` na hora de executar. O código utiliza caminhos relativos (como `data/arquivo.txt`) e precisa dessa estrutura para funcionar corretamente.

---

## Estrutura de Dados (Pasta `data/`)

O projeto utiliza arquivos de texto simples (`.txt`) armazenados na pasta `data/` para carregar e salvar o estado do sistema. 

Os nomes dos arquivos devem ser **exatamente** os listados abaixo para que o projeto consiga carregá-los. Os dados dentro de cada arquivo são separados por vírgula (formato CSV simplificado).

### Formatos Esperados:

**1. `cidade.txt`**
Cada linha representa uma cidade. Apenas o nome da cidade.
- **Formato:** `NomeDaCidade`
- **Exemplo:**
  ```text
  Sao Paulo
  Rio de Janeiro
  ```

**2. `passageiro.txt`**
- **Formato:** `ID,Nome,CidadeAtual`
- **Exemplo:**
  ```text
  1,Joao Silva,Sao Paulo
  2,Maria Souza,Rio de Janeiro
  ```

**3. `trajeto.txt`**
O "Tipo" refere-se ao tipo de trajeto (ex: 'A' para Aquático, 'T' para Terrestre, etc).
- **Formato:** `CidadeOrigem,CidadeDestino,Tipo,Distancia`
- **Exemplo:**
  ```text
  Sao Paulo,Rio de Janeiro,T,400
  ```

**4. `transporte.txt`**
- **Formato:** `ID,Nome,Tipo,Capacidade,Velocidade,DistanciaEntreDescansos,TempoDeDescansoAtual,LocalAtual`
- **Exemplo:**
  ```text
  1,Onibus Expresso,T,40,80,200,0,Sao Paulo
  ```

**5. `viagem.txt`**
O campo `IDProximaViagem` deve ser `-1` caso não exista uma viagem subsequente. Os booleanos (`EmAndamento`, `Ocorreu`) são salvos como `0` (Falso) ou `1` (Verdadeiro). Os IDs dos passageiros a bordo vão no final da linha, separados por vírgula.
- **Formato:** `ID,IDTransporte,Origem,Destino,IDProximaViagem,HorasEmTransito,EmAndamento,Ocorreu,IDPassageiro1,IDPassageiro2,...`
- **Exemplo:** (Viagem 1, com o transporte 1, de SP para RJ, com os passageiros de ID 1 e 2)
  ```text
  1,1,Sao Paulo,Rio de Janeiro,-1,5,0,0,1,2
  ```
