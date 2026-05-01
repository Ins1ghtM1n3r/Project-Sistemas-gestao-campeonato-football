#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_EQUIPES 20
#define MAX_JOGADORES 30
#define MAX_CAMPEONATOS 10
#define MAX_PARTIDAS 100
#define MAX_GOLEADORES 10

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
    int empates;
    int derrotas;
    int gols_marcados;
    int gols_sofridos;
} Equipe;

typedef struct {
    char nome[50];
    int ano;
    char equipes[MAX_EQUIPES][50];
    int num_equipes;
} Campeonato;

typedef struct {
    char equipe1[50];
    char equipe2[50];
    int gols_equipe1;
    int gols_equipe2;
    char campeonato[50];
    char data[20];
    char goleadores1[MAX_GOLEADORES][50];
    char goleadores2[MAX_GOLEADORES][50];
    int tempos_gols1[MAX_GOLEADORES];
    int tempos_gols2[MAX_GOLEADORES];
    int num_goleadores1;
    int num_goleadores2;
} Partida;

Equipe equipes[MAX_EQUIPES];
Campeonato campeonatos[MAX_CAMPEONATOS];
Partida partidas[MAX_PARTIDAS];
int num_equipes = 0;
int num_campeonatos = 0;
int num_partidas = 0;

void salvar_dados() {
    system("cls");
    FILE *file = fopen("dados.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "%d\n", num_equipes);
    for (int i = 0; i < num_equipes; i++) {
        fprintf(file, "%s\n%s\n%d\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", equipes[i].nome, equipes[i].cidade, equipes[i].ano_fundacao, equipes[i].treinador, equipes[i].num_jogadores, equipes[i].pontos, equipes[i].vitorias, equipes[i].empates, equipes[i].derrotas, equipes[i].gols_marcados, equipes[i].gols_sofridos);
        for (int j = 0; j < equipes[i].num_jogadores; j++) {
            fprintf(file, "%s\n%d\n%d\n%s\n%d\n", equipes[i].jogadores[j].nome, equipes[i].jogadores[j].idade, equipes[i].jogadores[j].numero_camisa, equipes[i].jogadores[j].posicao, equipes[i].jogadores[j].gols);
        }
    }

    fprintf(file, "%d\n", num_campeonatos);
    for (int i = 0; i < num_campeonatos; i++) {
        fprintf(file, "%s\n", campeonatos[i].nome);
        fprintf(file, "%d\n", campeonatos[i].ano);
        fprintf(file, "%d\n", campeonatos[i].num_equipes);
        for (int j = 0; j < campeonatos[i].num_equipes; j++) {
            fprintf(file, "%s\n", campeonatos[i].equipes[j]);
        }
    }

    fprintf(file, "%d\n", num_partidas);
    for (int i = 0; i < num_partidas; i++) {
        fprintf(file, "%s\n%s\n%s\n%d\n%d\n%s\n%d\n", partidas[i].campeonato, partidas[i].equipe1, partidas[i].equipe2, partidas[i].gols_equipe1, partidas[i].gols_equipe2, partidas[i].data, partidas[i].num_goleadores1);
        for (int j = 0; j < partidas[i].num_goleadores1; j++) {
            fprintf(file, "%s\n", partidas[i].goleadores1[j]);
        }
        fprintf(file, "%d\n", partidas[i].num_goleadores2);
        for (int j = 0; j < partidas[i].num_goleadores2; j++) {
            fprintf(file, "%s\n", partidas[i].goleadores2[j]);
        }
    }

    fclose(file);
}

void carregar_dados() {
    system("cls");
    FILE *file = fopen("dados.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    fscanf(file, "%d\n", &num_equipes);
    for (int i = 0; i < num_equipes; i++) {
        fscanf(file, "%[^\n]\n%[^\n]\n%d\n%[^\n]\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", equipes[i].nome, equipes[i].cidade, &equipes[i].ano_fundacao, equipes[i].treinador, &equipes[i].num_jogadores, &equipes[i].pontos, &equipes[i].vitorias, &equipes[i].empates, &equipes[i].derrotas, &equipes[i].gols_marcados, &equipes[i].gols_sofridos);
        for (int j = 0; j < equipes[i].num_jogadores; j++) {
            fscanf(file, "%[^\n]\n%d\n%d\n%[^\n]\n%d\n", equipes[i].jogadores[j].nome, &equipes[i].jogadores[j].idade, &equipes[i].jogadores[j].numero_camisa, equipes[i].jogadores[j].posicao, &equipes[i].jogadores[j].gols);
        }
    }

    fscanf(file, "%d\n", &num_campeonatos);
    for (int i = 0; i < num_campeonatos; i++) {
        fscanf(file, "%[^\n]\n", campeonatos[i].nome);
        fscanf(file, "%d\n", &campeonatos[i].ano);
        fscanf(file, "%d\n", &campeonatos[i].num_equipes);
        for (int j = 0; j < campeonatos[i].num_equipes; j++) {
            fscanf(file, "%[^\n]\n", campeonatos[i].equipes[j]);
        }
    }

    fscanf(file, "%d\n", &num_partidas);
    for (int i = 0; i < num_partidas; i++) {
        fscanf(file, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n%[^\n]\n%d\n", partidas[i].campeonato, partidas[i].equipe1, partidas[i].equipe2, &partidas[i].gols_equipe1, &partidas[i].gols_equipe2, partidas[i].data, &partidas[i].num_goleadores1);
        for (int j = 0; j < partidas[i].num_goleadores1; j++) {
            fscanf(file, "%[^\n]\n", partidas[i].goleadores1[j]);
        }
        fscanf(file, "%d\n", &partidas[i].num_goleadores2);
        for (int j = 0; j < partidas[i].num_goleadores2; j++) {
            fscanf(file, "%[^\n]\n", partidas[i].goleadores2[j]);
        }
    }

    fclose(file);
}

void cadastrar_equipe() {
    system("cls");
    if (num_equipes >= MAX_EQUIPES) {
        printf("Número máximo de equipes atingido.\n");
        return;
    }
    printf("Nome da equipe: ");
    fflush(stdin);
    scanf(" %[^\n]", equipes[num_equipes].nome);
    printf("Cidade: ");
    fflush(stdin);
    scanf(" %[^\n]", equipes[num_equipes].cidade);
    printf("Ano de fundação: ");
    fflush(stdin);
    scanf("%d", &equipes[num_equipes].ano_fundacao);
    printf("Nome do treinador: ");
    fflush(stdin);
    scanf(" %[^\n]", equipes[num_equipes].treinador);
    equipes[num_equipes].num_jogadores = 0;
    equipes[num_equipes].pontos = 0;
    equipes[num_equipes].vitorias = 0;
    equipes[num_equipes].empates = 0;
    equipes[num_equipes].derrotas = 0;
    equipes[num_equipes].gols_marcados = 0;
    equipes[num_equipes].gols_sofridos = 0;
    num_equipes++;
    salvar_dados();
}

void cadastrar_jogador() {
    system("cls");
    char nome_equipe[50];
    printf("Nome da equipe: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_equipe);
    for (int i = 0; i < num_equipes; i++) {
        if (strcmp(equipes[i].nome, nome_equipe) == 0) {
            if (equipes[i].num_jogadores >= MAX_JOGADORES) {
                printf("Número máximo de jogadores atingido.\n");
                return;
            }
            Jogador *jogador = &equipes[i].jogadores[equipes[i].num_jogadores];
            printf("Nome do jogador: ");
            fflush(stdin);
            scanf(" %[^\n]", jogador->nome);
            printf("Idade: ");
            fflush(stdin);
            scanf("%d", &jogador->idade);
            if (jogador->idade < 16 || jogador->idade > 40) {
                printf("Idade inválida. Deve ser entre 16 e 40 anos.\n");
                return;
            }
            printf("Número da camisa: ");
            fflush(stdin);
            scanf("%d", &jogador->numero_camisa);
            printf("Posição: ");
            fflush(stdin);
            scanf(" %[^\n]", jogador->posicao);
            jogador->gols = 0;
            equipes[i].num_jogadores++;
            salvar_dados();
            return;
        }
    }
    printf("Equipe não encontrada.\n");
}

void cadastrar_campeonato() {
    // system("cls"); // Removido para compatibilidade com diferentes sistemas operacionais
    if (num_campeonatos >= MAX_CAMPEONATOS) {
        printf("Número máximo de campeonatos atingido.\n");
        return;
    }
    printf("Nome do campeonato: ");
    fflush(stdin);
    scanf(" %[^\n]", campeonatos[num_campeonatos].nome);
    printf("Ano de realização: ");
    fflush(stdin);
    scanf("%d", &campeonatos[num_campeonatos].ano);

    campeonatos[num_campeonatos].num_equipes = 0;

    // Inscrever equipes já cadastradas
    char opcao;
    do {
        if (campeonatos[num_campeonatos].num_equipes >= MAX_EQUIPES) {
            printf("Número máximo de equipes atingido para este campeonato.\n");
            break;
        }
        printf("Deseja inscrever uma equipe já cadastrada? (s/n): ");
        fflush(stdin);
        scanf(" %c", &opcao);
        if (opcao == 's' || opcao == 'S') {
            char nome_equipe[50];
            printf("Nome da equipe: ");
            fflush(stdin);
            scanf(" %[^\n]", nome_equipe);

            int equipe_encontrada = 0;
            for (int i = 0; i < num_equipes; i++) {
                if (strcmp(equipes[i].nome, nome_equipe) == 0) {
                    strcpy(campeonatos[num_campeonatos].equipes[campeonatos[num_campeonatos].num_equipes], nome_equipe);
                    campeonatos[num_campeonatos].num_equipes++;
                    equipe_encontrada = 1;
                    break;
                }
            }
            if (!equipe_encontrada) {
                printf("Equipe não encontrada.\n");
            }
        }
    } while (opcao == 's' || opcao == 'S');

    num_campeonatos++;
    salvar_dados();
}

int equipe_esta_no_campeonato(char *nome_campeonato, char *nome_equipe) {
    for (int i = 0; i < num_campeonatos; i++) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            for (int j = 0; j < campeonatos[i].num_equipes; j++) {
                if (strcmp(campeonatos[i].equipes[j], nome_equipe) == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void registrar_partida() {
     system("cls"); 
    if (num_partidas >= MAX_PARTIDAS) {
        printf("Número máximo de partidas atingido.\n");
        return;
    }
    printf("Nome do campeonato: ");
    fflush(stdin);
    scanf(" %[^\n]", partidas[num_partidas].campeonato);

    printf("Equipe 1: ");
    fflush(stdin);
    scanf(" %[^\n]", partidas[num_partidas].equipe1);
    if (!equipe_esta_no_campeonato(partidas[num_partidas].campeonato, partidas[num_partidas].equipe1)) {
        printf("Equipe 1 não está cadastrada no campeonato '%s'.\n", partidas[num_partidas].campeonato);
        return;
    }

    printf("Equipe 2: ");
    fflush(stdin);
    scanf(" %[^\n]", partidas[num_partidas].equipe2);
    if (!equipe_esta_no_campeonato(partidas[num_partidas].campeonato, partidas[num_partidas].equipe2)) {
        printf("Equipe 2 não está cadastrada no campeonato '%s'.\n", partidas[num_partidas].campeonato);
        return;
    }

    printf("Gols da equipe 1: ");
    fflush(stdin);
    scanf("%d", &partidas[num_partidas].gols_equipe1);
    printf("Gols da equipe 2: ");
    fflush(stdin);
    scanf("%d", &partidas[num_partidas].gols_equipe2);
    printf("Data da partida: ");
    fflush(stdin);
    scanf(" %[^\n]", partidas[num_partidas].data);

    // Registrar goleadores da equipe 1
    printf("Número de goleadores da equipe 1: ");
    fflush(stdin);
    scanf("%d", &partidas[num_partidas].num_goleadores1);
    for (int i = 0; i < partidas[num_partidas].num_goleadores1; i++) {
        printf("Nome do goleador %d da equipe 1: ", i + 1);
        fflush(stdin);
        scanf(" %[^\n]", partidas[num_partidas].goleadores1[i]);
        printf("Tempo do gol do goleador %d da equipe 1 (em minutos): ", i + 1);
        fflush(stdin);
        scanf("%d", &partidas[num_partidas].tempos_gols1[i]);
        // Atualizar gols do jogador
        for (int j = 0; j < num_equipes; j++) {
            if (strcmp(equipes[j].nome, partidas[num_partidas].equipe1) == 0) {
                for (int k = 0; k < equipes[j].num_jogadores; k++) {
                    if (strcmp(equipes[j].jogadores[k].nome, partidas[num_partidas].goleadores1[i]) == 0) {
                        equipes[j].jogadores[k].gols++;
                    }
                }
            }
        }
    }

    // Registrar goleadores da equipe 2
    printf("Número de goleadores da equipe 2: ");
    fflush(stdin);
    scanf("%d", &partidas[num_partidas].num_goleadores2);
    for (int i = 0; i < partidas[num_partidas].num_goleadores2; i++) {
        printf("Nome do goleador %d da equipe 2: ", i + 1);
        fflush(stdin);
        scanf(" %[^\n]", partidas[num_partidas].goleadores2[i]);
        printf("Tempo do gol do goleador %d da equipe 2 (em minutos): ", i + 1);
        fflush(stdin);
        scanf("%d", &partidas[num_partidas].tempos_gols2[i]);
        // Atualizar gols do jogador
        for (int j = 0; j < num_equipes; j++) {
            if (strcmp(equipes[j].nome, partidas[num_partidas].equipe2) == 0) {
                for (int k = 0; k < equipes[j].num_jogadores; k++) {
                    if (strcmp(equipes[j].jogadores[k].nome, partidas[num_partidas].goleadores2[i]) == 0) {
                        equipes[j].jogadores[k].gols++;
                    }
                }
            }
        }
    }

    // Atualizar estatísticas das equipes
    for (int i = 0; i < num_equipes; i++) {
        if (strcmp(equipes[i].nome, partidas[num_partidas].equipe1) == 0) {
            equipes[i].gols_marcados += partidas[num_partidas].gols_equipe1;
            equipes[i].gols_sofridos += partidas[num_partidas].gols_equipe2;
            if (partidas[num_partidas].gols_equipe1 > partidas[num_partidas].gols_equipe2) {
                equipes[i].vitorias++;
                equipes[i].pontos += 3;
            } else if (partidas[num_partidas].gols_equipe1 == partidas[num_partidas].gols_equipe2) {
                equipes[i].empates++;
                equipes[i].pontos += 1;
            } else {
                equipes[i].derrotas++;
            }
        }
        if (strcmp(equipes[i].nome, partidas[num_partidas].equipe2) == 0) {
            equipes[i].gols_marcados += partidas[num_partidas].gols_equipe2;
            equipes[i].gols_sofridos += partidas[num_partidas].gols_equipe1;
            if (partidas[num_partidas].gols_equipe2 > partidas[num_partidas].gols_equipe1) {
                equipes[i].vitorias++;
                equipes[i].pontos += 3;
            } else if (partidas[num_partidas].gols_equipe2 == partidas[num_partidas].gols_equipe1) {
                equipes[i].empates++;
                equipes[i].pontos += 1;
            } else {
                equipes[i].derrotas++;
            }
        }
    }

    num_partidas++;
    salvar_dados();
}
void listar_partidas() {
     system("cls"); 
    for (int i = 0; i < num_partidas; i++) {
        printf("--------------------------------------------------\n");
        printf("| Campeonato: %s\n", partidas[i].campeonato);
        printf("| Equipe 1: %s\n", partidas[i].equipe1);
        printf("| Equipe 2: %s\n", partidas[i].equipe2);
        printf("| Placar: %d - %d\n", partidas[i].gols_equipe1, partidas[i].gols_equipe2);
        printf("| Data: %s\n", partidas[i].data);
        printf("| Goleadores da equipe 1:\n");
        for (int j = 0; j < partidas[i].num_goleadores1; j++) {
            printf("|   %s (Tempo: %d minutos)\n", partidas[i].goleadores1[j], partidas[i].tempos_gols1[j]);
        }
        printf("| Goleadores da equipe 2:\n");
        for (int j = 0; j < partidas[i].num_goleadores2; j++) {
            printf("|   %s (Tempo: %d minutos)\n", partidas[i].goleadores2[j], partidas[i].tempos_gols2[j]);
        }
        printf("--------------------------------------------------\n");
    }
}

void tabela_classificativa() {
    // Ordenar equipes por pontos
    for (int i = 0; i < num_equipes - 1; i++) {
        for (int j = i + 1; j < num_equipes; j++) {
            if (equipes[j].pontos > equipes[i].pontos) {
                Equipe temp = equipes[i];
                equipes[i] = equipes[j];
                equipes[j] = temp;
            }
        }
    }

    // Exibir tabela classificativa
    printf("Tabela Classificativa:\n");
    printf("%-10s %-20s %-10s %-10s %-10s %-10s %-15s %-15s\n", "Posição", "Equipe", "Pontos", "Vitórias", "Empates", "Derrotas", "Gols Marcados", "Gols Sofridos");
    for (int i = 0; i < num_equipes; i++) {
        printf("%-10d %-20s %-10d %-10d %-10d %-10d %-15d %-15d\n", i + 1, equipes[i].nome, equipes[i].pontos, equipes[i].vitorias, equipes[i].empates, equipes[i].derrotas, equipes[i].gols_marcados, equipes[i].gols_sofridos);
    }
}

void pesquisar_equipe() {
    system("cls");
    char nome_equipe[50];
    printf("Nome da equipe: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_equipe);
    for (int i = 0; i < num_equipes; i++) {
        if (strcmp(equipes[i].nome, nome_equipe) == 0) {
            printf("Equipe encontrada:\n");
            printf("Nome: %s\n", equipes[i].nome);
            printf("Cidade: %s\n", equipes[i].cidade);
                     printf("Ano de fundação: %d\n", equipes[i].ano_fundacao);
            printf("Treinador: %s\n", equipes[i].treinador);
            return;
        }
    }
    printf("Equipe não encontrada.\n");
}

void pesquisar_jogador() {
    system("cls");
    char nome_jogador[50];
    printf("Nome do jogador: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_jogador);
    for (int i = 0; i < num_equipes; i++) {
        for (int j = 0; j < equipes[i].num_jogadores; j++) {
            if (strcmp(equipes[i].jogadores[j].nome, nome_jogador) == 0) {
                printf("Jogador encontrado:\n");
                printf("Nome: %s\n", equipes[i].jogadores[j].nome);
                printf("Idade: %d\n", equipes[i].jogadores[j].idade);
                printf("Número da camisa: %d\n", equipes[i].jogadores[j].numero_camisa);
                printf("Posição: %s\n", equipes[i].jogadores[j].posicao);
                printf("Equipe: %s\n", equipes[i].nome);
                return;
            }
        }
    }
    printf("Jogador não encontrado.\n");
}

void pesquisar_campeonato() {
    system("cls");
    char nome_campeonato[50];
    printf("Nome do campeonato: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_campeonato);
    for (int i = 0; i < num_campeonatos; i++) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            printf("Campeonato encontrado:\n");
            printf("Nome: %s\n", campeonatos[i].nome);
            printf("Ano: %d\n", campeonatos[i].ano);
            return;
        }
    }
    printf("Campeonato não encontrado.\n");
}

void editar_equipe() {
    system("cls");
    char nome_equipe[50];
    printf("Nome da equipe a editar: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_equipe);
    for (int i = 0; i < num_equipes; i++) {
        if (strcmp(equipes[i].nome, nome_equipe) == 0) {
            printf("Editar equipe:\n");
            printf("Novo nome: ");
            fflush(stdin);
            scanf(" %[^\n]", equipes[i].nome);
            printf("Nova cidade: ");
            fflush(stdin);
            scanf(" %[^\n]", equipes[i].cidade);
            printf("Novo ano de fundação: ");
            fflush(stdin);
            scanf("%d", &equipes[i].ano_fundacao);
            printf("Novo nome do treinador: ");
            fflush(stdin);
            scanf(" %[^\n]", equipes[i].treinador);
            salvar_dados();
            return;
        }
    }
    printf("Equipe não encontrada.\n");
}

void editar_jogador() {
    system("cls");
    char nome_jogador[50];
    printf("Nome do jogador a editar: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_jogador);
    for (int i = 0; i < num_equipes; i++) {
        for (int j = 0; j < equipes[i].num_jogadores; j++) {
            if (strcmp(equipes[i].jogadores[j].nome, nome_jogador) == 0) {
                printf("Editar jogador:\n");
                printf("Novo nome: ");
                fflush(stdin);
                scanf(" %[^\n]", equipes[i].jogadores[j].nome);
                printf("Nova idade: ");
                fflush(stdin);
                scanf("%d", &equipes[i].jogadores[j].idade);
                printf("Novo número da camisa: ");
                fflush(stdin);
                scanf("%d", &equipes[i].jogadores[j].numero_camisa);
                printf("Nova posição: ");
                fflush(stdin);
                scanf(" %[^\n]", equipes[i].jogadores[j].posicao);
                salvar_dados();
                return;
            }
        }
    }
    printf("Jogador não encontrado.\n");
}

void editar_campeonato() {
     system("cls");
     char nome_campeonato[50]; 
    printf("Nome do campeonato a editar: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_campeonato);

    for (int i = 0; i < num_campeonatos; i++) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            printf("Editar campeonato:\n");
            printf("Novo nome: ");
            fflush(stdin);
            scanf(" %[^\n]", campeonatos[i].nome);
            printf("Novo ano de realização: ");
            fflush(stdin);
            scanf("%d", &campeonatos[i].ano);

            // Editar equipes inscritas no campeonato
            char opcao;
            do {
                printf("Deseja adicionar, remover ou editar uma equipe? (a/r/e/n para nenhuma): ");
                fflush(stdin);
                scanf(" %c", &opcao);
                if (opcao == 'a' || opcao == 'A') {
                    if (campeonatos[i].num_equipes >= MAX_EQUIPES) {
                        printf("Número máximo de equipes atingido para este campeonato.\n");
                        continue;
                    }
                    char nome_equipe[50];
                    printf("Nome da equipe a adicionar: ");
                    fflush(stdin);
                    scanf(" %[^\n]", nome_equipe);

                    int equipe_encontrada = 0;
                    for (int j = 0; j < num_equipes; j++) {
                        if (strcmp(equipes[j].nome, nome_equipe) == 0) {
                            strcpy(campeonatos[i].equipes[campeonatos[i].num_equipes], nome_equipe);
                            campeonatos[i].num_equipes++;
                            equipe_encontrada = 1;
                            break;
                        }
                    }
                    if (!equipe_encontrada) {
                        printf("Equipe não encontrada.\n");
                    }
                } else if (opcao == 'r' || opcao == 'R') {
                    char nome_equipe[50];
                    printf("Nome da equipe a remover: ");
                    fflush(stdin);
                    scanf(" %[^\n]", nome_equipe);

                    int equipe_encontrada = 0;
                    for (int j = 0; j < campeonatos[i].num_equipes; j++) {
                        if (strcmp(campeonatos[i].equipes[j], nome_equipe) == 0) {
                            for (int k = j; k < campeonatos[i].num_equipes - 1; k++) {
                                strcpy(campeonatos[i].equipes[k], campeonatos[i].equipes[k + 1]);
                            }
                            campeonatos[i].num_equipes--;
                            equipe_encontrada = 1;
                            break;
                        }
                    }
                    if (!equipe_encontrada) {
                        printf("Equipe não encontrada no campeonato.\n");
                    }
                } else if (opcao == 'e' || opcao == 'E') {
                    char nome_equipe[50];
                    printf("Nome da equipe a editar: ");
                    fflush(stdin);
                    scanf(" %[^\n]", nome_equipe);

                    int equipe_encontrada = 0;
                    for (int j = 0; j < campeonatos[i].num_equipes; j++) {
                        if (strcmp(campeonatos[i].equipes[j], nome_equipe) == 0) {
                            printf("Novo nome da equipe: ");
                            fflush(stdin);
                            scanf(" %[^\n]", campeonatos[i].equipes[j]);
                            equipe_encontrada = 1;
                            break;
                        }
                    }
                    if (!equipe_encontrada) {
                        printf("Equipe não encontrada no campeonato.\n");
                    }
                }
            } while (opcao != 'n' && opcao != 'N');

            salvar_dados();
            return;
        }
    }
    printf("Campeonato não encontrado.\n");
}

void mostrar_estatisticas() {
    // system("cls"); // Removido para compatibilidade com diferentes sistemas operacionais
    for (int i = 0; i < num_campeonatos; i++) {
        printf("Campeonato: %s\n", campeonatos[i].nome);
        printf("Ano: %d\n", campeonatos[i].ano);
        printf("Equipes participantes:\n");
        for (int j = 0; j < campeonatos[i].num_equipes; j++) {
            printf("  %s\n", campeonatos[i].equipes[j]);
        }
        printf("-------------------------\n");
    }
}
void listar_equipes_campeonato() {
     system("cls"); 
    char nome_campeonato[50];
    printf("Nome do campeonato: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_campeonato);

    int encontrou = 0;
    for (int i = 0; i < num_campeonatos; i++) {
        if (strcmp(campeonatos[i].nome, nome_campeonato) == 0) {
            printf("Campeonato: %s\n", campeonatos[i].nome);
            printf("Ano: %d\n", campeonatos[i].ano);
            printf("Equipes participantes:\n");
            for (int j = 0; j < campeonatos[i].num_equipes; j++) {
                printf("  %s\n", campeonatos[i].equipes[j]);
            }
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("Campeonato '%s' não encontrado.\n", nome_campeonato);
    }
}


void listar_jogos_equipe() {
    system("cls");
    char nome_equipe[50];
    printf("Nome da equipe: ");
    fflush(stdin);
    scanf(" %[^\n]", nome_equipe);
    for (int i = 0; i < num_partidas; i++) {
        if (strcmp(partidas[i].equipe1, nome_equipe) == 0 || strcmp(partidas[i].equipe2, nome_equipe) == 0) {
            printf("Campeonato: %s\n", partidas[i].campeonato);
            printf("Partida: %s vs %s\n", partidas[i].equipe1, partidas[i].equipe2);
            printf("Placar: %d - %d\n", partidas[i].gols_equipe1, partidas[i].gols_equipe2);
            printf("Data: %s\n", partidas[i].data);
        }
    }
}

int main() {
    setlocale(LC_ALL,"portuguese");
    system("cls");
    carregar_dados();
    int opcao;
    do {
        printf("Menu Principal:\n");
        printf("1. Cadastrar Equipe\n");
        printf("2. Cadastrar Jogador\n");
        printf("3. Cadastrar Campeonato\n");
        printf("4. Registrar Partida\n");    
        printf("5. Tabela Classificativa\n");
        printf("6. Pesquisar Equipe\n");
        printf("7. Pesquisar Jogador\n");
        printf("8. Pesquisar Campeonato\n");
        printf("9. Editar Equipe\n");
        printf("10. Editar Jogador\n");
        printf("11. Editar Campeonato\n");
        printf("12. Mostrar Estatísticas\n");
        printf("13. Listar partidas\n");
        printf("14. Listar Jogos de uma Equipe\n");
        printf("15. Listar equipes de um campeonato\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrar_equipe();
                break;
            case 2:
                cadastrar_jogador();
                break;
            case 3:
                cadastrar_campeonato();
                break;
            case 4:
                registrar_partida();
                break;
            
            case 5:
                tabela_classificativa();
                break;
            case 6:
                pesquisar_equipe();
                break;
            case 7:
                pesquisar_jogador();
                break;
            case 8:
                pesquisar_campeonato();
                break;
            case 9:
                editar_equipe();
                break;
            case 10:
                editar_jogador();
                break;
            case 11:
                editar_campeonato();
                break;
            case 12:
                mostrar_estatisticas();
                break;
            case 13:
                listar_partidas();
                break;
            case 14:
                listar_jogos_equipe();
                break;
            case 15:
                listar_equipes_campeonato();
                break;
            case 0:
                printf("Saindo...\n");
                salvar_dados();
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
    return 0;
}