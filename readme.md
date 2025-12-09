# Projeto TAD SUS-V2

Autores:
- Arthur de Castro Dias
- Gabriel Carraro Salzedas
- Kauã Benjamin Trombim Silva

### Descrição:
Este projeto implementa um sistema de gerenciamento de pacientes em um hospital utilizando árvores para armazenamento e gestão dos dados. Os tipos abstratos de dados usados foram:
- `Árvore AVL`: Usada como cadastro dos usuários, possui uma boa condição de busca e remoção;
- `Heap de prioridade`: Usada como fila, mas que aceita diferentes níveis de prioridade. Sempre remove o mais urgente;
- `Pilha`: Usada como histórico, uma forma de gerir os ultimos dados inseridos facilmente;
- `Tad Paciente`: Tipo abstrato de dado que será usado em todo o projeto.

### Estrutura:
- `main.c`: interface de usuário em linha de comando e fluxo principal do programa.
- `makefile`: alvo para compilar o projeto (pode exigir `make` no Windows; veja instruções abaixo).
- `TADs/codes`: pasta que abriga a implementação de cada TAD
- `TADs/headers`: pasta que abriga os cabeçalhos e as funções públicas dos TADs

### Dados persistentes:
- A lista de pacientes é salva em `lista.json`.
- A fila de triagem é salva em `triagem.txt`.

### Como compilar e executar (Windows PowerShell):
1. Se você tem `make` instalado, na pasta do projeto execute:

```powershell
make rrun
```
O comando acima facilita a execução, mas é possível executar manualmente

```powershell
make all
make run
```

2. Se `make` não estiver disponível (Windows padrão), compile manualmente com `gcc`:

```powershell
# 1. Compilando os TADS
gcc -c ./TADs/codes/paciente.c -o paciente.o -std=c99 -Wall
gcc -c ./TADs/codes/avl.c -o avl.o -std=c99 -Wall
gcc -c ./TADs/codes/heap.c -o heap.o -std=c99 -Wall
gcc -c ./TADs/codes/historico.c -o historico.o -std=c99 -Wall

# 2. Compilando a main
gcc -c main.c -o main.o -std=c99 -Wall

# 3. Linkando os arquivos
gcc main.o paciente.o avl.o heap.o historico.o -o main -std=c99 -Wall

# 4. Executar (Linux/Mac)
./main
# Ou no Windows:
# main.exe
```


3. Execute o programa:

```powershell
.\main.exe
```

(Nota: Se quiser somente executar, sem detalhes técnicos, copie a linha abaixo e execute!)

```powershell
gcc main.c ./TADs/codes/paciente.c ./TADs/codes/avl.c ./TADs/codes/heap.c ./TADs/codes/historico.c -o main -std=c99 -Wall
```

### Observações e limitações:
- `historico` aceita até 10 procedimentos por paciente.
- IDs de pacientes são gerados sequencialmente pela função `avl_gerar_id`, de modo que um id já existente mas apagado não será repetido (possível overflow de int a depender da quantidade de pacientes cadastrados).
- `nome` do paciente pode abrigar no máximo 99 caracteres.
