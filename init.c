#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_EQUIPAS 20
#define MAX_JOGADORES 30
#define MAX_CAMPEONATOS 10
#define MAX_PARTIDAS 100

typedef struct {
    char nome[50];
    int idade;
    int numero_camisa;
    char posicao[20];
    int gols;
} Jogador;

typedef struct {
    char nome[50];
    char cidade[50];
    int ano_fundacao;
    char treinador[50];
    Jogador jogadores[MAX_JOGADORES];
    int num_jogadores;
    int pontos;
    int vitorias;
    int gols;
} Equipa;

typedef struct {
    char nome[50];
    int ano;
    Equipa* equipas[MAX_EQUIPAS];
    int num_equipas;
    Equipa* campeao;
    Equipa* vice_campeao;
    Equipa* terceiro_colocado;
} Campeonato;

typedef struct {
    Equipa* equipa1;
    Equipa* equipa2;
    int gols_equipa1;
    int gols_equipa2;
    char data[20];
    char marcadores[100]; 
} Partida;

Equipa equipas[MAX_EQUIPAS];
Campeonato campeonatos[MAX_CAMPEONATOS];
Partida partidas[MAX_PARTIDAS];
int num_equipas = 0;
int num_campeonatos = 0;
int num_partidas = 0;

void salvarDados() {
    FILE *file = fopen("dados.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }
    fwrite(&num_equipas, sizeof(int), 1, file);
    fwrite(equipas, sizeof(Equipa), num_equipas, file);
    fwrite(&num_campeonatos, sizeof(int), 1, file);
    fwrite(campeonatos, sizeof(Campeonato), num_campeonatos, file);
    fwrite(&num_partidas, sizeof(int), 1, file);
    fwrite(partidas, sizeof(Partida), num_partidas, file);
    fclose(file);
}

void carregarDados() {
    FILE *file = fopen("dados.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para carregar os dados.\n");
        return;
    }
    fread(&num_equipas, sizeof(int), 1, file);
    fread(equipas, sizeof(Equipa), num_equipas, file);
    fread(&num_campeonatos, sizeof(int), 1, file);
    fread(campeonatos, sizeof(Campeonato), num_campeonatos, file);
    fread(&num_partidas, sizeof(int), 1, file);
    fread(partidas, sizeof(Partida), num_partidas, file);
    fclose(file);
}

void cadastrarEquipa() {
    if (num_equipas >= MAX_EQUIPAS) {
        printf("Número máximo de equipas atingido.\n");
        return;
    }
    Equipa e;
    printf("Nome da equipa: ");
    scanf("%[\n]s", e.nome);
    fflush(stdin);
    printf("Cidade: ");
    scanf("%[\n]s", e.cidade);
    fflush(stdin);
    printf("Ano de fundação: ");
    scanf("%d", &e.ano_fundacao);
    fflush(stdin);
    printf("Nome do treinador: ");
    scanf("%[\n]s", e.treinador);
    fflush(stdin);
    e.num_jogadores = 0;
    e.pontos = 0;
    e.vitorias = 0;
    e.gols = 0;
    equipas[num_equipas++] = e;
    salvarDados();
    printf("Equipa cadastrada com sucesso!\n");
}

void cadastrarJogador() {
    if (num_equipas == 0) {
        printf("Nenhuma equipa cadastrada.\n");
        return;
    }
    
    char nome_equipa[100];
    printf("Nome da equipa: ");
    scanf("%s", nome_equipa);
    
    int equipa_index = -1;
    for (int i = 0; i < num_equipas; ++i) {
        if (strcmp(equipas[i].nome, nome_equipa) == 0) {
            equipa_index = i;
            break;
        }
    }
    
    if (equipa_index == -1) {
        printf("Equipa inválida.\n");
        return;
    }
    
    Equipa* e = &equipas[equipa_index];
    if (e->num_jogadores >= MAX_JOGADORES) {
        printf("Número máximo de jogadores atingido.\n");
        return;
    }
    
    Jogador j;
    printf("Nome do jogador: ");
    scanf("%s", j.nome);
    printf("Idade: ");
    scanf("%d", &j.idade);
    if (j.idade < 16 || j.idade > 40) {
        printf("Idade inválida.\n");
        return;
    }
    printf("Número da camisa: ");
    scanf("%d", &j.numero_camisa);
    printf("Posição: ");
    scanf("%s", j.posicao);
    j.gols = 0;
    
    e->jogadores[e->num_jogadores++] = j;
    salvarDados();
    printf("Jogador cadastrado com sucesso!\n");
}

void cadastrarCampeonato() {
    if (num_campeonatos >= MAX_CAMPEONATOS) {
        printf("Número máximo de campeonatos atingido.\n");
        return;
    }
    Campeonato c;
    printf("Nome do campeonato: ");
    scanf("%[\n]s", c.nome);
    fflush(stdin);
    printf("Ano de realização: ");
    scanf("%d", &c.ano);
    fflush(stdin);
    c.num_equipas = 0;
    c.campeao = NULL;
    c.vice_campeao = NULL;
    c.terceiro_colocado = NULL;
    campeonatos[num_campeonatos++] = c;
    salvarDados();
    printf("Campeonato cadastrado com sucesso!\n");
}

void registrarPartida() {
    if (num_campeonatos == 0) {
        printf("Nenhum campeonato cadastrado.\n");
        return;
    }
    
    char nome_campeonato[100];
    printf("Nome do campeonato: ");
    scanf("%s", nome_campeonato);
    
    int campeonato_index = -1;
    for (int i = 0; i < num_campeonatos; ++i) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            campeonato_index = i;
            break;
        }
    }
    
    if (campeonato_index == -1) {
        printf("Campeonato inválido.\n");
        return;
    }
    
    if (num_partidas >= MAX_PARTIDAS) {
        printf("Número máximo de partidas atingido.\n");
        return;
    }
    
    Partida p;
    char nome_equipa1[100], nome_equipa2[100];
    
    printf("Nome da primeira equipa: ");
    scanf("%s", nome_equipa1);
    printf("Nome da segunda equipa: ");
    scanf("%s", nome_equipa2);
    
    int equipa1_index = -1, equipa2_index = -1;
    for (int i = 0; i < num_equipas; ++i) {
        if (strcmp(equipas[i].nome, nome_equipa1) == 0) {
            equipa1_index = i;
        }
        if (strcmp(equipas[i].nome, nome_equipa2) == 0) {
            equipa2_index = i;
        }
    }
    
    if (equipa1_index == -1 || equipa2_index == -1) {
        printf("Equipa inválida.\n");
        return;
    }
    
    p.equipa1 = &equipas[equipa1_index];
    p.equipa2 = &equipas[equipa2_index];
    printf("Data da partida (dd/mm/aaaa): ");
    scanf("%s", p.data);
    printf("Gols da primeira equipa: ");
    scanf("%d", &p.gols_equipa1);
    printf("Gols da segunda equipa: ");
    scanf("%d", &p.gols_equipa2);
    
    // Registrar gols dos jogadores
    for (int i = 0; i < p.gols_equipa1; i++) {
        char nome_jogador[50];
        printf("Nome do jogador da equipa 1 que marcou o gol %d: ", i + 1);
        scanf("%s", nome_jogador);
        for (int j = 0; j < p.equipa1->num_jogadores; j++) {
            if (strcmp(p.equipa1->jogadores[j].nome, nome_jogador) == 0) {
                p.equipa1->jogadores[j].gols++;
                break;
            }
        }
    }

    for (int i = 0; i < p.gols_equipa2; i++) {
        char nome_jogador[50];
        printf("Nome do jogador da equipa 2 que marcou o gol %d: ", i + 1);
        scanf("%s", nome_jogador);
        for (int j = 0; j < p.equipa2->num_jogadores; j++) {
            if (strcmp(p.equipa2->jogadores[j].nome, nome_jogador) == 0) {
                p.equipa2->jogadores[j].gols++;
                break;
            }
        }
    }
    
    partidas[num_partidas++] = p;
    
    // Atualizar estatísticas das equipas
    p.equipa1->gols += p.gols_equipa1;
    p.equipa2->gols += p.gols_equipa2;
    if (p.gols_equipa1 > p.gols_equipa2) {
        p.equipa1->vitorias++;
        p.equipa1->pontos += 3;
    } else if (p.gols_equipa2 > p.gols_equipa1) {
        p.equipa2->vitorias++;
        p.equipa2->pontos += 3;
    } else {
        p.equipa1->pontos++;
        p.equipa2->pontos++;
    }

    salvarDados();
    printf("Partida registrada com sucesso!\n");
}

void editarEquipa() {
    system("cls");
    if (num_equipas == 0) {
        printf("Nenhuma equipa cadastrada.\n");
        return;
    }
    
    char nome_equipa[100];
    printf("Nome da equipa: ");
    scanf("%s", nome_equipa);
    
    int equipa_index = -1;
    for (int i = 0; i < num_equipas; ++i) {
        if (strcmp(equipas[i].nome, nome_equipa) == 0) {
            equipa_index = i;
            break;
        }
    }
    
    if (equipa_index == -1) {
        printf("Equipa inválida.\n");
        return;
    }
    
    Equipa* e = &equipas[equipa_index];
    printf("Novo nome da equipa: ");
    scanf("%s", e->nome);
    printf("Nova cidade: ");
    scanf("%s", e->cidade);
    printf("Novo ano de fundação: ");
    scanf("%d", &e->ano_fundacao);
    printf("Novo nome do treinador: ");
    scanf("%s", e->treinador);
    salvarDados();
    printf("Equipa editada com sucesso!\n");
}

void editarJogador() {
    system("cls");
    if (num_equipas == 0) {
        printf("Nenhuma equipa cadastrada.\n");
        return;
    }
    int equipa_index;
    printf("Selecione a equipa do jogador (0 a %d): ", num_equipas - 1);
    scanf("%d", &equipa_index);
    fflush(stdin);
    if (equipa_index < 0 || equipa_index >= num_equipas) {
        printf("Equipa inválida.\n");
        return;
    }
    Equipa* e = &equipas[equipa_index];
    if (e->num_jogadores == 0) {
        printf("Nenhum jogador cadastrado nesta equipa.\n");
        return;
    }
    int jogador_index;
    printf("Selecione o jogador para editar (0 a %d): ", e->num_jogadores - 1);
    scanf("%d", &jogador_index);
    fflush(stdin);
    if (jogador_index < 0 || jogador_index >= e->num_jogadores) {
        printf("Jogador inválido.\n");
        return;
    }
    Jogador* j = &e->jogadores[jogador_index];
    printf("Novo nome do jogador: ");
    scanf("%[\n]s", j->nome);
    fflush(stdin);
    printf("Nova idade: ");
    scanf("%d", &j->idade);
    fflush(stdin);
    printf("Novo número da camisa: ");
    scanf("%d", &j->numero_camisa);
    fflush(stdin);
    printf("Nova posição: ");
    scanf("%[\n]s", j->posicao);
    fflush(stdin);
    salvarDados();
    printf("Jogador editado com sucesso!\n");
}

void exibirTabelaClassificacao(Campeonato* c) {
    system("cls");
    printf("\nTabela de Classificação do Campeonato %s (%d)\n", c->nome, c->ano);
    printf("------------------------------------------------------------\n");
    printf("| %-20s | %-10s | %-10s | %-10s |\n", "Equipa", "Pontos", "Vitórias", "Gols");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < c->num_equipas; i++) {
        Equipa* e = c->equipas[i];
        printf("| %-20s | %-10d | %-10d | %-10d |\n", e->nome, e->pontos, e->vitorias, e->gols);
    }
    printf("------------------------------------------------------------\n");
}

void pesquisarEquipa() {
    system("cls");
    char nome[50];
    printf("Digite o nome da equipa: ");
    scanf("%[\n]s", nome);
    fflush(stdin);
    for (int i = 0; i < num_equipas; i++) {
        if (strcmp(equipas[i].nome, nome) == 0) {
            printf("Equipa encontrada: %s, Cidade: %s, Ano de Fundação: %d, Treinador: %s\n",
                   equipas[i].nome, equipas[i].cidade, equipas[i].ano_fundacao, equipas[i].treinador);
            return;
        }
    }
    printf("Equipa não encontrada.\n");
}

void pesquisarJogador() {
    system("cls");
    char nome[50];
    printf("Digite o nome do jogador: ");
    scanf("%[\n]s", nome);
    fflush(stdin);
    for (int i = 0; i < num_equipas; i++) {
        for (int j = 0; j < equipas[i].num_jogadores; j++) {
            if (strcmp(equipas[i].jogadores[j].nome, nome) == 0) {
                printf("Jogador encontrado: %s, Idade: %d, Número da Camisa: %d, Posição: %s, Gols: %d\n",
                       equipas[i].jogadores[j].nome, equipas[i].jogadores[j].idade, equipas[i].jogadores[j].numero_camisa,
                       equipas[i].jogadores[j].posicao, equipas[i].jogadores[j].gols);
                return;
            }
        }
    }
    printf("Jogador não encontrado.\n");
}

void mostrarEstatisticas(Campeonato* c) {
    system("cls");
    printf("\nEstatísticas das Equipas no Campeonato %s (%d)\n", c->nome, c->ano);
    printf("------------------------------------------------------------\n");
    printf("| %-20s | %-10s | %-10s | %-10s |\n", "Equipa", "Pontos", "Vitórias", "Gols");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < c->num_equipas; i++) {
        Equipa* e = c->equipas[i];
        printf("| %-20s | %-10d | %-10d | %-10d |\n", e->nome, e->pontos, e->vitorias, e->gols);
    }
    printf("------------------------------------------------------------\n");
}

void listarEquipasCampeonato(Campeonato* c) {
    system("cls");
    printf("\nEquipas do Campeonato %s (%d)\n", c->nome, c->ano);
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < c->num_equipas; i++) {
        Equipa* e = c->equipas[i];
        printf("Equipa: %s, Cidade: %s, Ano de Fundação: %d, Treinador: %s\n",
               e->nome, e->cidade, e->ano_fundacao, e->treinador);
    }
    printf("------------------------------------------------------------\n");
}

void listarJogadoresEquipa(Equipa* e) {
    system("cls");
    printf("\nJogadores da Equipa %s\n", e->nome);
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < e->num_jogadores; i++) {
        Jogador* j = &e->jogadores[i];
        printf("Nome: %s, Idade: %d, Número da Camisa: %d, Posição: %s, Gols: %d\n",
               j->nome, j->idade, j->numero_camisa, j->posicao, j->gols);
    }
    printf("------------------------------------------------------------\n");
}

void listarJogosEquipa(Equipa* e) {
    system("cls");
    printf("\nJogos da Equipa %s\n", e->nome);
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < num_partidas; i++) {
        Partida* p = &partidas[i];
        if (p->equipa1 == e || p->equipa2 == e) {
            printf("Data: %s, Equipa 1: %s, Equipa 2: %s, Placar: %d - %d, Marcadores: %s\n",
                   p->data, p->equipa1->nome, p->equipa2->nome, p->gols_equipa1, p->gols_equipa2, p->marcadores);
        }
    }
    printf("------------------------------------------------------------\n");
}

void listarJogosCampeonato(Campeonato* c) {
    system("cls");
    printf("\nJogos do Campeonato %s (%d)\n", c->nome, c->ano);
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < num_partidas; i++) {
        Partida* p = &partidas[i];
        for (int j = 0; j < c->num_equipas; j++) {
            if (p->equipa1 == c->equipas[j] || p->equipa2 == c->equipas[j]) {
                printf("Data: %s, Equipa 1: %s, Equipa 2: %s, Placar: %d - %d, Marcadores: %s\n",
                       p->data, p->equipa1->nome, p->equipa2->nome, p->gols_equipa1, p->gols_equipa2, p->marcadores);
                break;
            }
        }
    }
    printf("------------------------------------------------------------\n");
}

int main() {
    setlocale(LC_ALL,"portuguese");
    system("cls");
    carregarDados();
    int opcao;
    do {
        printf("\nSISTEMA DE GESTÃO DA FEDERAÇÃO ANGOLANA DE FUTEBOL\n");
        printf("1. Cadastrar Equipa\n");
        printf("2. Cadastrar Jogador\n");
        printf("3. Cadastrar Campeonato\n");
        printf("4. Registrar Partida\n");
        printf("5. Editar Equipa\n");
        printf("6. Editar Jogador\n");
        printf("7. Exibir Tabela de Classificação\n");
        printf("8. Pesquisar Equipa\n");
        printf("9. Pesquisar Jogador\n");
        printf("10. Mostrar Estatísticas\n");
        printf("11. Listar Equipas de um Campeonato\n");
        printf("12. Listar Jogadores de uma Equipa\n");
        printf("13. Listar Jogos de uma Equipa\n");
        printf("14. Listar Jogos de um Campeonato\n");
        printf("15. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        fflush(stdin);
        switch (opcao) {
            case 1:
                cadastrarEquipa();
                break;
            case 2:
                cadastrarJogador();
                break;
            case 3:
                cadastrarCampeonato();
                break;
            case 4:
                registrarPartida();
                break;
            case 5:
                editarEquipa();
                break;
            case 6:
                editarJogador();
                break;
            case 7: {
    char nome_campeonato[100];
    printf("Nome do campeonato: ");
    scanf("%s", nome_campeonato);
    
    int campeonato_index = -1;
    for (int i = 0; i < num_campeonatos; ++i) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            campeonato_index = i;
            break;
        }
    }
    
    if (campeonato_index == -1) {
        printf("Campeonato inválido.\n");
        break;
    }
    exibirTabelaClassificacao(&campeonatos[campeonato_index]);
                break;
            }


                
            case 8:
                pesquisarEquipa();
                break;
            case 9:
                pesquisarJogador();
                break;
            case 10: {
                {
    char nome_campeonato[100];
    printf("Nome do campeonato: ");
    scanf("%s", nome_campeonato);
    
    int campeonato_index = -1;
    for (int i = 0; i < num_campeonatos; ++i) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            campeonato_index = i;
            break;
        }
    }
    
    if (campeonato_index == -1) {
        printf("Campeonato inválido.\n");
        break;
    }
    mostrarEstatisticas(&campeonatos[campeonato_index]);
                break;
            }
}

                
            case 11: {
                {
    char nome_campeonato[100];
    printf("Nome do campeonato: ");
    scanf("%s", nome_campeonato);
    
    int campeonato_index = -1;
    for (int i = 0; i < num_campeonatos; ++i) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            campeonato_index = i;
            break;
        }
    }
    
    if (campeonato_index == -1) {
        printf("Campeonato inválido.\n");
        break;
    }
    
    listarEquipasCampeonato(&campeonatos[campeonato_index]);
    break;
    listarEquipasCampeonato(&campeonatos[campeonato_index]);
                break;
            }
}

                
            case 12: {
    char nome_equipa[100];
    printf("Nome da equipa: ");
    scanf("%s", nome_equipa);
    
    int equipa_index = -1;
    for (int i = 0; i < num_equipas; ++i) {
        if (strcmp(equipas[i].nome, nome_equipa) == 0) {
            equipa_index = i;
            break;
        }
    }
    
    if (equipa_index == -1) {
        printf("Equipa inválida.\n");
        break;
    }
    
    listarJogadoresEquipa(&equipas[equipa_index]);
    break;
}

            case 13: {
    char nome_equipa[100];
    printf("Nome da equipa: ");
    scanf("%s", nome_equipa);
    
    int equipa_index = -1;
    for (int i = 0; i < num_equipas; ++i) {
        if (strcmp(equipas[i].nome, nome_equipa) == 0) {
            equipa_index = i;
            break;
        }
    }
    
    if (equipa_index == -1) {
        printf("Equipa inválida.\n");
        break;
    }
    
    listarJogosEquipa(&equipas[equipa_index]);
    break;
}

            case 14: {
    char nome_campeonato[100];
    printf("Nome do campeonato: ");
    scanf("%s", nome_campeonato);
    
    int campeonato_index = -1;
    for (int i = 0; i < num_campeonatos; ++i) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            campeonato_index = i;
            break;
        }
    }
    
    if (campeonato_index == -1) {
        printf("Campeonato inválido.\n");
        break;
    }
    
                listarJogosCampeonato(&campeonatos[campeonato_index]);
                break;
            
}

            case 15:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 15);
    salvarDados();
    return 0;
}