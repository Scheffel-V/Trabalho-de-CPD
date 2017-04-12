#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio2.h>

struct user
{
    char nome[41];
    int tempo_jogado;
    char arma_preferida1[21];
    char arma_preferida2[21];
    char mapa_preferido1[41];
    char mapa_preferido2[41];
    int kills;
    int deaths;
    int total_score;
    int headshots;
    int matches_played;
    int matches_won;
    int shots_fired;
    int shots_hit;
};
typedef struct user user;

struct information // ao adicionar algo aqui, arrumar funções: ReadArqBinInfGerais,WriteArqBinInfGerais e PrintaInformation
{
      int num_de_user;
      int tempo_jogado;
      int media_tempo_jogado;
      int desvio_padrao_tempo_jogado;
      int kills;
      int media_kills;
      int desvio_padrao_kills;
      int deaths;
      int media_deaths;
      int desvio_padrao_deaths;
      int total_score;
      int media_total_score;
      int desvio_padrao_total_score;
      int headshots;
      int media_headshots;
      int desvio_padrao_headshots;
      int matches_played;
      int media_matches_played;
      int desvio_padrao_matches_played;
      int matches_won;
      int media_matches_won;
      int desvio_padrao_matches_won;
      int shots_fired;
      int media_shots_fired;
      int desvio_padrao_shots_fired;
      int shots_hit;
      int media_shots_hit;
      int desvio_padrao_shots_hit;
      float win_per_game;
      float KDA;
      float acertos_de_tiros;
      float kill_de_headshot;
      char primeiro_mapa[41];
      char segundo_mapa[41];
      char primeira_arma[21];
      char segunda_arma[21];
};
typedef struct information information;

struct lista_mapas // Lista para os mapas preferidos
{
    char mapa[41];
    int contador;
    struct lista_mapas *prox;
};
typedef struct lista_mapas lista_mapas;

struct lista_armas // Lista para as armas preferidas
{
    char arma[41];
    int contador;
    struct lista_armas *prox;
};
typedef struct lista_armas lista_armas;

struct trie // Arvore trie de busca
{
    struct trie *(alfabeto[95]);
    int end;
};
typedef struct trie trie;

trie* AddNodoTRIE()
{
    trie *novo;
    int j=0;
    novo = (trie*)malloc(sizeof(trie));
    novo->end=-1;
    while (j<95)
    {
        novo->alfabeto[j]=NULL;
        j++;
    }

    return novo;
}

// Função que adiciona um nodo na árvore.
void AdicionaNaTRIE(trie *arv, char palavra[], int endereco)
{
    trie *arv_aux = arv;
    char caractere;
    int caractere_int, i=0, j;

    while(palavra[i] != '\0')
    {
        caractere = palavra[i];
        caractere_int = (int)caractere;
        caractere_int = caractere_int - 32;
        if ( arv_aux->alfabeto[caractere_int] == NULL)
        {
            arv_aux->alfabeto[caractere_int] = AddNodoTRIE();
            j=0;
        }
        arv_aux->end = -1;
        arv_aux = arv_aux->alfabeto[caractere_int];
        i++;
    }
    arv_aux->end = endereco;
}

//Função que cria uma árvore.
trie* CriaTRIE()
{
    FILE *arqbin, *arq;
    char palavra[50];
    user* usuario;
    trie *arv;
    int end, i = 0, contador, j=0;

    usuario = (user*)malloc(sizeof(user));
    arv = (trie*)malloc(sizeof(trie));
    arv->end = -1;

    while (j<95)
    {
        arv->alfabeto[j]=NULL;
        j++;
    }

    arq = fopen("Plus de info de users.txt", "rb");
    fread(&contador, sizeof(int), 1, arq);
    fclose(arq);

    arqbin = fopen("arquivo.txt", "r");

    while(i < contador)
    {
        fseek(arqbin, 204*i, SEEK_SET);
        fread(usuario, sizeof(struct user), 1, arqbin);
        strcpy(palavra, usuario->nome);
        end = i * 204;
        AdicionaNaTRIE(arv, palavra, end);
        i++;
    }

    fclose(arqbin);

    return arv;
}

//Função que pesquisa um nome em uma árvore e devolve a posição da estrutura no arquivo. (Se não existir ele retorna -1)
int PesquisaNaTRIE(trie *arv, char palavra[50], char senha[])
{
    trie *arv_aux = arv;
    int letra, i=0;
    while(palavra[i] != '\0')
    {
        letra = (int)palavra[i] - 32;
        if(arv_aux->alfabeto[letra] == NULL)
            return -1;
        arv_aux = arv_aux->alfabeto[letra];
        i++;
    }
    if(arv_aux->end == -1)
        return -1;
    return arv_aux->end;
}

// Função que recebe um user e o criptografa. (modifica os valores das estruturas.)
void Criptografar(user *User)
{
    int i=0, j=0, numero=0;
    char senha[10]={'2','3','1','1','2','1','3','1','\0'};

    while(User->nome[i] != '\0')
    {
        if(j == 8)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->nome[i] = User->nome[i] + numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->arma_preferida1[i] != '\0')
    {
        if(j == 8)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->arma_preferida1[i] = User->arma_preferida1[i] + numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->arma_preferida2[i] != '\0')
    {
        if(j == 8)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->arma_preferida2[i] = User->arma_preferida2[i] + numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->mapa_preferido1[i] != '\0')
    {
        if(j == 8)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->mapa_preferido1[i] = User->mapa_preferido1[i] + numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->mapa_preferido2[i] != '\0')
    {
        if(j == 8)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->mapa_preferido2[i] = User->mapa_preferido2[i] + numero;
        i++;
        j++;
    }
}

// Função que recebe um nome e o criprografa. (modifica os valores da string).
void CriptografarPalavra(char palavra[], char senha[])
{
    int i=0, j=0, numero=0, tamanho;
    tamanho = strlen(senha);

    while(palavra[i] != '\0')
    {
        if(j == tamanho)
        {
            j=0;
        }
        numero = senha[j] - '0';
        palavra[i] = palavra[i] + numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
}

// Função que recebe um user e o descriptografa. (modifica os valores das estruturas para voltarem ao normal.)
void Descriptografar(user *User, char senha[])
{
    int i=0, j=0, numero=0, tamanho;
    tamanho = strlen(senha);

    while(User->nome[i] != '\0')
    {
        if(j == tamanho)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->nome[i] = User->nome[i] - numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->arma_preferida1[i] != '\0')
    {
        if(j == tamanho)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->arma_preferida1[i] = User->arma_preferida1[i] - numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->arma_preferida2[i] != '\0')
    {
        if(j == tamanho)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->arma_preferida2[i] = User->arma_preferida2[i] - numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->mapa_preferido1[i] != '\0')
    {
        if(j == tamanho)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->mapa_preferido1[i] = User->mapa_preferido1[i] - numero;
        i++;
        j++;
    }
    i = 0;
    j = 0;
    while(User->mapa_preferido2[i] != '\0')
    {
        if(j == tamanho)
        {
            j=0;
        }
        numero = senha[j] - '0';
        User->mapa_preferido2[i] = User->mapa_preferido2[i] - numero;
        i++;
        j++;
    }
}

// Função que recebe uma arma ou um mapa e o descriptografa.
void DescriptografarArmaOuMapa(char palavra[], char senha[])
{
    int tamanho, numero, i=0, j=0;

    tamanho = strlen(senha);

    i = 0;
    j = 0;
    while(palavra[i] != '\0')
    {
        if(j == tamanho)
        {
            j=0;
        }
        numero = senha[j] - '0';
        palavra[i] = palavra[i] - numero;
        i++;
        j++;
    }
}

// Função para printar a estrutura user
void PrintUser(user *new_user, char senha[] )
{
    Descriptografar(new_user, senha);
    printf("nome: ");
    puts(new_user->nome);
    printf("tempo_jogado: %d\narma_preferida1: ", new_user->tempo_jogado);
    puts(new_user->arma_preferida1);
    printf("arma_preferida2: ");
    puts(new_user->arma_preferida2);
    printf("mapa_preferido1: ");
    puts(new_user->mapa_preferido1);
    printf("mapa_preferido2: ");
    puts(new_user->mapa_preferido2);
    printf("kills: %d\n", new_user->kills);
    printf("deaths: %d\n", new_user->deaths);
    printf("total_score: %d\n", new_user->total_score);
    printf("headshots: %d\n", new_user->headshots);
    printf("matches_played: %d\n", new_user->matches_played);
    printf("matches_won: %d\n", new_user->matches_won);
    printf("shots_fired: %d\n", new_user->shots_fired);
    printf("shots_hit: %d\n", new_user->shots_hit);
}

// Função que lê o arquivo txt e escreve no arquivo binário com todas as estruturas já criptografadas.
void LerArquivoTxt(char senha[])
{
    FILE *arqtxt, *arq_main_bin;
    FILE* arq_geral_bin;
    char c, str[50], nome_txt[50], nome_binario[50];
    int campo=-1, i=0, local, num_de_user=0;
    user *new_user;

   /* printf("\nInforme o nome do arquivo de texto:");
    gets(nome_txt);
    printf("\nInforme o nome do arquivo binario:");
    gets(nome_binario); */


    arqtxt = fopen("cpd.txt", "r");
    arq_main_bin = fopen("arquivo.txt", "wb");

    if ( arqtxt == NULL)
    {
        printf("Erro no arquivo TXT.\n");
        return;
    }
    if ( arq_main_bin == NULL)
    {
        printf("Erro no arquivo BINARIO.\n");
        return;
    }

    new_user = (user*) malloc(sizeof(user));

    while( (c = fgetc(arqtxt)) != EOF )
    {
        if (c == '#')
        {
            if(campo != -1)
            {
                str[i] = '\0';
            }
            if (campo == 0) // está no nome
            {
                strcpy(new_user->nome, str);
                i = 0;
            }
            if (campo == 1) // está no tempo jogado
            {
                new_user->tempo_jogado = atoi(str);
                i = 0;
            }
            if (campo == 2) // está no arma1
            {
                strcpy(new_user->arma_preferida1, str);
                i = 0;
            }
            if (campo == 3) // está no arma2
            {
                strcpy(new_user->arma_preferida2, str);
                i = 0;
            }
            if (campo == 4) // está no mapa1
            {
                strcpy(new_user->mapa_preferido1, str);
                i = 0;
            }
            if (campo == 5) // está no mapa2
            {
                strcpy(new_user->mapa_preferido2, str);
                i = 0;
            }
            if (campo == 6) // está no kills
            {
                new_user->kills = atoi(str);
                i = 0;
            }
            if (campo == 7) // está no deaths
            {
                new_user->deaths = atoi(str);
                i = 0;
            }
            if (campo == 9) // está no total_score
            {
                new_user->total_score = atoi(str);
                i = 0;
            }
            if (campo == 8) // está no headshots
            {
                new_user->headshots = atoi(str);
                i = 0;
            }
            if (campo == 10) // está no matches_played
            {
                new_user->matches_played = atoi(str);
                i = 0;
            }
            if (campo == 11) // está no matches_won
            {
                new_user->matches_won = atoi(str);
                i = 0;
            }
            if (campo == 12) // está no shots_fired
            {
                new_user->shots_fired = atoi(str);
                i = 0;
            }
            if (campo == 13) // está no shots_hit
            {
                fflush(stdin);
                new_user->shots_hit = atoi(str);
                i = 0;
                campo = -2;
                textcolor(GREEN);
                printf("\n> Salvo na posicao %d o usuario:\n", ftell(arq_main_bin));
                textcolor(RED);
                //PrintUser(new_user, senha);
                Criptografar(new_user);
                fwrite(new_user, sizeof(struct user), 1, arq_main_bin);
                num_de_user++;
            }
            campo++;
        }
        else
        {
            if(campo > -1)
            {
                c = toupper(c);
                str[i] = c;
                i++;
            }
        }
    }
    fclose(arq_main_bin);

    arq_geral_bin = fopen("Plus de info de users.txt", "wb");
    rewind(arq_geral_bin);
    fwrite(&num_de_user, sizeof(int), 1, arq_geral_bin);
    textcolor(GREEN);
    printf("\n\nnumero de usuarios salvos: %d\n", num_de_user);
    fclose(arqtxt);
    fclose(arq_geral_bin);
}

// Função de menu geral
int Menu(int *controlador, char senha[])
{
    char menu;
    int *controlador2, controlador2_aux=1;

    controlador2 = &controlador2_aux;

    menu = getch();

    if(menu == 80)
    {
        system("cls");
        if((*controlador) != 6)
            (*controlador) = (*controlador) + 1;

        switch((*controlador))
        {
            case 1:
            {
                textbackground(WHITE);
                textcolor(RED);
                printf("[1] Montar o arquivo Binario.\n");
                textbackground(BLACK);
                printf("[2] Ordena arquivo Binario.\n");
                printf("[3] Informacoes gerais.\n");
                printf("[4] Adcionar User.\n");
                printf("[5] Pesquisar User.\n");
                printf("[6] Sair.\n");
                Menu(controlador, senha);
                break;
            }
            case 2:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Montar o arquivo Binario.\n");
                textbackground(WHITE);
                printf("[2] Ordena arquivo Binario.\n");
                textbackground(BLACK);
                printf("[3] Informacoes gerais.\n");
                printf("[4] Adcionar User.\n");
                printf("[5] Pesquisar User.\n");
                printf("[6] Sair.\n");
                Menu(controlador, senha);
                break;
            }
            case 3:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Montar o arquivo Binario.\n");
                printf("[2] Ordena arquivo Binario.\n");
                textbackground(WHITE);
                printf("[3] Informacoes gerais.\n");
                textbackground(BLACK);
                printf("[4] Adcionar User.\n");
                printf("[5] Pesquisar User.\n");
                printf("[6] Sair.\n");
                Menu(controlador, senha);
                break;
            }
            case 4:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Montar o arquivo Binario.\n");
                printf("[2] Ordena arquivo Binario.\n");
                printf("[3] Informacoes gerais.\n");
                textbackground(WHITE);
                printf("[4] Adcionar User.\n");
                textbackground(BLACK);
                printf("[5] Pesquisar User.\n");
                printf("[6] Sair.\n");
                Menu(controlador, senha);
                break;
            }
            case 5:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Montar o arquivo Binario.\n");
                printf("[2] Ordena arquivo Binario.\n");
                printf("[3] Informacoes gerais.\n");
                printf("[4] Adcionar User.\n");
                textbackground(WHITE);
                printf("[5] Pesquisar User.\n");
                textbackground(BLACK);
                printf("[6] Sair.\n");
                Menu(controlador, senha);
                break;
            }
            case 6:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Montar o arquivo Binario.\n");
                printf("[2] Ordena arquivo Binario.\n");
                printf("[3] Informacoes gerais.\n");
                printf("[4] Adcionar User.\n");
                printf("[5] Pesquisar User.\n");
                textbackground(WHITE);
                printf("[6] Sair.\n");
                textbackground(BLACK);
                Menu(controlador, senha);
                break;
            }
        }
    }
    else if(menu == 72)
           {
               system("cls");
               if((*controlador) != 1)
                  (*controlador) = (*controlador) - 1;

               switch((*controlador))
               {
                   case 1:
                   {
                        textbackground(WHITE);
                        textcolor(RED);
                        printf("[1] Montar o arquivo Binario.\n");
                        textbackground(BLACK);
                        printf("[2] Ordena arquivo Binario.\n");
                        printf("[3] Informacoes gerais.\n");
                        printf("[4] Adcionar User.\n");
                        printf("[5] Pesquisar User.\n");
                        printf("[6] Sair.\n");
                        Menu(controlador, senha);
                        break;
                    }
                    case 2:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Montar o arquivo Binario.\n");
                        textbackground(WHITE);
                        printf("[2] Ordena arquivo Binario.\n");
                        textbackground(BLACK);
                        printf("[3] Informacoes gerais.\n");
                        printf("[4] Adcionar User.\n");
                        printf("[5] Pesquisar User.\n");
                        printf("[6] Sair.\n");
                        Menu(controlador, senha);
                        break;
                    }
                    case 3:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Montar o arquivo Binario.\n");
                        printf("[2] Ordena arquivo Binario.\n");
                        textbackground(WHITE);
                        printf("[3] Informacoes gerais.\n");
                        textbackground(BLACK);
                        printf("[4] Adcionar User.\n");
                        printf("[5] Pesquisar User.\n");
                        printf("[6] Sair.\n");
                        Menu(controlador, senha);
                        break;
                    }
                    case 4:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Montar o arquivo Binario.\n");
                        printf("[2] Ordena arquivo Binario.\n");
                        printf("[3] Informacoes gerais.\n");
                        textbackground(WHITE);
                        printf("[4] Adcionar User.\n");
                        textbackground(BLACK);
                        printf("[5] Pesquisar User.\n");
                        printf("[6] Sair.\n");
                        Menu(controlador, senha);
                        break;
                    }
                    case 5:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Montar o arquivo Binario.\n");
                        printf("[2] Ordena arquivo Binario.\n");
                        printf("[3] Informacoes gerais.\n");
                        printf("[4] Adcionar User.\n");
                        textbackground(WHITE);
                        printf("[5] Pesquisar User.\n");
                        textbackground(BLACK);
                        printf("[6] Sair.\n");
                        Menu(controlador, senha);
                        break;
                    }
                    case 6:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Montar o arquivo Binario.\n");
                        printf("[2] Ordena arquivo Binario.\n");
                        printf("[3] Informacoes gerais.\n");
                        printf("[4] Adcionar User.\n");
                        printf("[5] Pesquisar User.\n");
                        textbackground(WHITE);
                        printf("[6] Sair.\n");
                        textbackground(BLACK);
                        Menu(controlador, senha);
                        break;
                    }
                }
           }
          else if(menu == 13)
               {
                   system("cls");
                   switch((*controlador))
                   {
                        case 1:
                        {
                            LerArquivoTxt(senha); // MONTAR O ARQUIVO BINARIO A PARTIR DO TXT
                            system("pause");
                            (*controlador) = 1;
                            return 0;
                        }
                        case 2:
                        {
                            textbackground(WHITE);
                            textcolor(RED);
                            printf("[1] Kills sobre Deaths.\n");
                            textbackground(BLACK);
                            printf("[2] Tempo Jogado.\n");
                            printf("[3] Score.\n");
                            printf("[4] Headshots.\n");
                            printf("[5] Vitorias.\n");
                            printf("[6] Voltar.\n");
                            MenuOrdena(controlador2, senha);
                            (*controlador)=1;
                            return 0;
                        }
                        case 3:
                        {
							CriaInformacoesGerais(senha);
							system("pause");
                            (*controlador)=1;
                            return 0;
                        }
                        case 4:
                        {
                            AdcionaUser(senha);
                            system("pause");
                            (*controlador)=1;
                            return 0;
                        }
                        case 5:
                        {
                            PesquisarUser(senha);
                            system("pause");
                            (*controlador)=1;
                            return 0;
                        }
                        case 6:
                        {
                            printf("\nSaindo do programa.\n");
                            system("pause");
                            return 1;
                        }
                    }
               }
               else
               {
                    Menu(controlador, senha);
               }
}

// Função de menu dos ordenamentos
void MenuOrdena(int *controlador, char senha[])
{
    char menu;

    menu = getch();
    char nome[41];
    int tempo_jogado;
    char arma_preferida1[21];
    char arma_preferida2[21];
    char mapa_preferido1[41];
    char mapa_preferido2[41];
    int kills;
    int deaths;
    int total_score;
    int headshots;
    int matches_played;
    int matches_won;
    int shots_fired;
    int shots_hit;
    if(menu == 80)
    {
        system("cls");
        if((*controlador) != 6)
            (*controlador) = (*controlador) + 1;

        switch((*controlador))
        {
            case 1:
            {
                textbackground(WHITE);
                textcolor(RED);
                printf("[1] Kills sobre Deaths.\n");
                textbackground(BLACK);
                printf("[2] Tempo Jogado.\n");
                printf("[3] Score.\n");
                printf("[4] Headshots.\n");
                printf("[5] Vitorias.\n");
                printf("[6] Voltar.\n");
                MenuOrdena(controlador, senha);
                break;
            }
            case 2:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Kills sobre Deaths.\n");
                textbackground(WHITE);
                printf("[2] Tempo jogado.\n");
                textbackground(BLACK);
                printf("[3] Score.\n");
                printf("[4] Headshots.\n");
                printf("[5] Vitorias.\n");
                printf("[6] Voltar.\n");
                MenuOrdena(controlador, senha);
                break;
            }
            case 3:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Kills sobre Deaths.\n");
                printf("[2] Tempo jogado.\n");
                textbackground(WHITE);
                printf("[3] Score.\n");
                textbackground(BLACK);
                printf("[4] Headshots.\n");
                printf("[5] Vitorias.\n");
                printf("[6] Voltar.\n");
                MenuOrdena(controlador, senha);
                break;
            }
            case 4:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Kills sobre Deaths.\n");
                printf("[2] Tempo jogado.\n");
                printf("[3] Score.\n");
                textbackground(WHITE);
                printf("[4] Headshots.\n");
                textbackground(BLACK);
                printf("[5] Vitorias.\n");
                printf("[6] Voltar.\n");
                MenuOrdena(controlador, senha);
                break;
            }
            case 5:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Kills sobre Deaths.\n");
                printf("[2] Tempo jogado.\n");
                printf("[3] Score.\n");
                printf("[4] Headshots.\n");
                textbackground(WHITE);
                printf("[5] Vitorias.\n");
                textbackground(BLACK);
                printf("[6] Voltar.\n");
                MenuOrdena(controlador, senha);
                break;
            }
            case 6:
            {
                textcolor(RED);
                textbackground(BLACK);
                printf("[1] Kills sobre Deaths.\n");
                printf("[2] Tempo jogado.\n");
                printf("[3] Score.\n");
                printf("[4] Headshots.\n");
                printf("[5] Vitorias.\n");
                textbackground(WHITE);
                printf("[6] Voltar.\n");
                textbackground(BLACK);
                MenuOrdena(controlador, senha);
                break;
            }
        }
    }
    else if(menu == 72)
           {
               system("cls");
               if((*controlador) != 1)
                  (*controlador) = (*controlador) - 1;

               switch((*controlador))
               {
                   case 1:
                   {
                        textbackground(WHITE);
                        textcolor(RED);
                        printf("[1] Kills sobre Deaths.\n");
                        textbackground(BLACK);
                        printf("[2] Tempo jogado.\n");
                        printf("[3] Score.\n");
                        printf("[4] Headshots.\n");
                        printf("[5] Vitorias.\n");
                        printf("[6] Voltar.\n");
                        MenuOrdena(controlador, senha);
                        break;
                    }
                    case 2:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Kills sobre Deaths.\n");
                        textbackground(WHITE);
                        printf("[2] Tempo jogado.\n");
                        textbackground(BLACK);
                        printf("[3] Score.\n");
                        printf("[4] Headshots.\n");
                        printf("[5] Vitorias.\n");
                        printf("[6] Voltar.\n");
                        MenuOrdena(controlador, senha);
                        break;
                    }
                    case 3:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Kills sobre Deaths.\n");
                        printf("[2] Tempo jogado.\n");
                        textbackground(WHITE);
                        printf("[3] Score.\n");
                        textbackground(BLACK);
                        printf("[4] Headshots.\n");
                        printf("[5] Vitorias.\n");
                        printf("[6] Voltar.\n");
                        MenuOrdena(controlador, senha);
                        break;
                    }
                    case 4:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Kills sobre Deaths.\n");
                        printf("[2] Tempo jogado.\n");
                        printf("[3] Score.\n");
                        textbackground(WHITE);
                        printf("[4] Headshots.\n");
                        textbackground(BLACK);
                        printf("[5] Vitorias.\n");
                        printf("[6] Voltar.\n");
                        MenuOrdena(controlador, senha);
                        break;
                    }
                    case 5:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Kills sobre Deaths.\n");
                        printf("[2] Tempo jogado.\n");
                        printf("[3] Score.\n");
                        printf("[4] Headshots.\n");
                        textbackground(WHITE);
                        printf("[5] Vitorias.\n");
                        textbackground(BLACK);
                        printf("[6] Voltar.\n");
                        MenuOrdena(controlador, senha);
                        break;
                    }
                    case 6:
                    {
                        textcolor(RED);
                        textbackground(BLACK);
                        printf("[1] Kills sobre Deaths.\n");
                        printf("[2] Tempo jogado.\n");
                        printf("[3] Score.\n");
                        printf("[4] Headshots.\n");
                        printf("[5] Vitorias.\n");
                        textbackground(WHITE);
                        printf("[6] Voltar.\n");
                        textbackground(BLACK);
                        MenuOrdena(controlador, senha);
                        break;
                    }
                }
           }
          else if(menu == 13)
               {
                   system("cls");
                   switch((*controlador))
                   {
                        case 1:
                        {
                            OrdenaPorKills(senha);
                            system("pause");
                            (*controlador) = 1;
                            break;
                        }
                        case 2:
                        {
                            OrdenaPorTempoJogado(senha);
                            system("pause");
                            (*controlador)=1;
                            break;
                        }
                        case 3:
                        {
							OrdenaPorScore(senha);
							system("pause");
                            (*controlador)=1;
                            break;
                        }
                        case 4:
                        {
                            OrdenaPorHeadshot(senha);
                            system("pause");
                            (*controlador)=1;
                            break;
                        }
                        case 5:
                        {
                            OrdenaPorWin(senha);
                            system("pause");
                            (*controlador)=1;
                            break;
                        }
                        case 6:
                        {
                            break;
                        }
                    }
               }
               else
               {
                    MenuOrdena(controlador, senha);
               }
}

//Função que calcula o desvio padrao
int DesvioPadrao(int media, int contador, int valor[9][150], int j)
{
    int  i,desvio ;
    unsigned int somatorio=0;

    for (i=contador+1; i>1; i--)
    {
        somatorio = somatorio + (unsigned int)((valor[j][i] - media) * (valor[j][i] - media));
    }
    desvio= sqrt((somatorio)/(contador-1));
    return desvio;
}

// Função que lê em um arquivo bin a estrutura information
information* ReadArqBinInfGerais(information* all)
{
     FILE* arq_geral_bin;

    arq_geral_bin = fopen("Plus de info de users.txt", "rb");
    fread(all, sizeof(struct information), 1, arq_geral_bin);
    fclose(arq_geral_bin);
    //PrintInformation(all);
    return all;
}

// Função para printar a estrutura information
void PrintInformation(information *i, char senha[])
{
    DescriptografarArmaOuMapa(i->primeira_arma, senha);
    printf("\ntotal de usuarios: %d\n\narma favorita dos usuarios:", i->num_de_user);
    puts(i->primeira_arma);
    printf("\nsegunda arma favorita dos usuarios:");
    DescriptografarArmaOuMapa(i->segunda_arma, senha);
    puts(i->segunda_arma);
    printf("\nmapa favorito dos usuarios:");
    DescriptografarArmaOuMapa(i->primeiro_mapa, senha);
    puts(i->primeiro_mapa);
    printf("\nsegundo mapa favorito dos usuarios:");
    DescriptografarArmaOuMapa(i->segundo_mapa, senha);
    puts(i->segundo_mapa);
    printf("\ntotal de tempo jogado: %d\tmedia: %d\tdesvio padrao: %d\n\n", i->tempo_jogado, i->media_tempo_jogado, i->desvio_padrao_tempo_jogado);
    printf("total de kills: %d\t\tmedia: %d\tdesvio padrao: %d\n\n", i->kills, i->media_kills, i->desvio_padrao_kills);
    printf("total de deaths: %d\t\tmedia: %d\tdesvio padrao: %d\n\n", i->deaths, i->media_deaths, i->desvio_padrao_deaths);
    printf("total de total score: %d\tmedia: %d\tdesvio padrao: %d\n\n", i->total_score, i->media_total_score, i->desvio_padrao_total_score);
    printf("total de headshots: %d\tmedia: %d\tdesvio padrao: %d\n\n", i->headshots, i->media_headshots, i->desvio_padrao_headshots);
    printf("total de matches played: %d\tmedia: %d\tdesvio padrao: %d\n\n", i->matches_played, i->media_matches_played, i->desvio_padrao_matches_played);
    printf("total de matches won: %d\tmedia: %d\tdesvio padrao: %d\n\n", i->matches_won, i->media_matches_won, i->desvio_padrao_matches_won);
    printf("total de shots fired: %d\tmedia: %d\tdesvio padrao: %d\n\n", i->shots_fired, i->media_shots_fired, i->desvio_padrao_shots_fired);
    printf("total de shots hit: %d\tmedia: %d\tdesvio padrao: %d\n\n", i->shots_hit, i->media_shots_hit, i->desvio_padrao_shots_hit);

    textcolor(GREEN);
    printf("ESTATISTICAS:\n");
    textcolor(YELLOW);
    printf("win/game= %f\n\n", i->win_per_game);
    printf("kills/deaths: %f\n\n", i->KDA);
    printf("tiros_certeiros/tiros: %f\n\n", i->acertos_de_tiros);
    printf("headshots/kills: %f\n\n", i->kill_de_headshot);
}

void OrdenaPorTempoJogado(char senha[])
{
    FILE *arq_main_bin, *arq_geral_bin;
    int valor[150], contador,atual, x, menor, indice, aux, i=0, j=0, temp;
    user *at, *men, *new_user;
    int top;

    at = (user*) malloc(sizeof(user));
    men = (user*) malloc(sizeof(user));


    arq_geral_bin = fopen("Plus de info de users.txt", "rb");
    fread(&contador, sizeof(int), 1, arq_geral_bin);
    fclose(arq_geral_bin);

    arq_main_bin = fopen("Arquivo.txt", "rb+");

    aux = contador;

    while(i < contador-1)
    {
        fseek(arq_main_bin, 204*i, SEEK_SET);
        fseek(arq_main_bin, 40 +  (sizeof(int)), SEEK_CUR);
        fread(&atual, sizeof(int), 1, arq_main_bin);
        j = i + 1;
        menor = 99999999999;

        while(j < aux)
        {
            fseek(arq_main_bin, 204*j, SEEK_SET);
            fseek(arq_main_bin, 40 +  (sizeof(int)), SEEK_CUR);
            fread(&temp, sizeof(int), 1, arq_main_bin);

            if (menor > temp)
            {
                menor = temp;
                indice = j;
            }
            j++;
        }

        if (menor < atual)
        {
            fseek(arq_main_bin, 204*i, SEEK_SET);
            fread(at, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fread(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*i, SEEK_SET);
            fwrite(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fwrite(at, sizeof(struct user), 1, arq_main_bin);
        }
        i++;
    }
    textcolor(YELLOW);
    printf("\tOs que possuem mais tempo jogado\n");
    new_user = (user*) malloc(sizeof(user));
    textcolor(RED);

    for(i=1;i<4;i++)
    {
        textcolor(GREEN);
        printf("\n______TOP %d______ \n", i);
        fseek(arq_main_bin, -204*i , SEEK_END);
        fread(new_user, sizeof(user),1,arq_main_bin);
        Descriptografar(new_user, senha);
        textcolor(RED);
        printf("nome: ");
        puts(new_user->nome);
        textcolor(YELLOW);
        printf("tempo_jogado: %d\n", new_user->tempo_jogado);
        textcolor(RED);
        printf("arma_preferida1: ");
        puts(new_user->arma_preferida1);
        printf("arma_preferida2: ");
        puts(new_user->arma_preferida2);
        printf("mapa_preferido1: ");
        puts(new_user->mapa_preferido1);
        printf("mapa_preferido2: ");
        puts(new_user->mapa_preferido2);
        printf("kills: %d\n", new_user->kills);
        printf("deaths: %d\n", new_user->deaths);
        printf("total_score: %d\n", new_user->total_score);
        printf("headshots: %d\n", new_user->headshots);
        printf("matches_played: %d\n", new_user->matches_played);
        printf("matches_won: %d\n", new_user->matches_won);
        printf("shots_fired: %d\n", new_user->shots_fired);
        printf("shots_hit: %d\n", new_user->shots_hit);
    }
    fclose(arq_main_bin);
}

// Função que ordena arquivo main binário conforme o KD Ratio dos usuários
void OrdenaPorKills(char senha[])
{
    FILE *arq_main_bin, *arq_geral_bin;
    int valor[150], contador, atual, atual_2, x, indice, aux, i=0, j=0, temp, temp_2;
    float kd_1, kd_2, menor;
    user *at, *men, *new_user;
    int top;

    at = (user*) malloc(sizeof(user));
    men = (user*) malloc(sizeof(user));


    arq_geral_bin = fopen("Plus de info de users.txt", "rb");
    fread(&contador, sizeof(int), 1, arq_geral_bin);
    fclose(arq_geral_bin);

    arq_main_bin = fopen("Arquivo.txt", "rb+");

    aux = contador;

    while(i < contador-1)
    {
        fseek(arq_main_bin, 204*i, SEEK_SET);
        fseek(arq_main_bin, 164+ 2* (sizeof(int)), SEEK_CUR);
        fread(&atual, sizeof(int), 1, arq_main_bin);
        fread(&atual_2, sizeof(int), 1, arq_main_bin);

        kd_1 = ((float)atual / (float)atual_2);

        j = i + 1;
        menor = 9999999;

        while(j < aux)
        {
            fseek(arq_main_bin, 204*j, SEEK_SET);
            fseek(arq_main_bin, 164+ 2* (sizeof(int)), SEEK_CUR);
            fread(&temp, sizeof(int), 1, arq_main_bin);
            fread(&temp_2, sizeof(int), 1, arq_main_bin);
            kd_2 = ((float)temp / (float)temp_2);

            if (menor > kd_2)
            {
                menor = kd_2;
                indice = j;
            }
            j++;
        }

        if (menor < kd_1)
        {
            fseek(arq_main_bin, 204*i, SEEK_SET);
            fread(at, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fread(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*i, SEEK_SET);
            fwrite(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fwrite(at, sizeof(struct user), 1, arq_main_bin);
        }
        i++;
    }
    textcolor(YELLOW);
    printf("\tOs melhores em kills\n");
    new_user = (user*) malloc(sizeof(user));
    textcolor(RED);

    for(i=1;i<4;i++)
    {
        textcolor(GREEN);
        printf("\n______TOP %d______ \n", i);
        fseek(arq_main_bin, -204*i , SEEK_END);
        fread(new_user, sizeof(user),1,arq_main_bin);

        Descriptografar(new_user, senha);
        textcolor(RED);
        printf("nome: ");
        puts(new_user->nome);
        printf("tempo_jogado: %d\narma_preferida1: ", new_user->tempo_jogado);
        puts(new_user->arma_preferida1);
        printf("arma_preferida2: ");
        puts(new_user->arma_preferida2);
        printf("mapa_preferido1: ");
        puts(new_user->mapa_preferido1);
        printf("mapa_preferido2: ");
        puts(new_user->mapa_preferido2);
        textcolor(YELLOW);
        printf("kills: %d\n", new_user->kills);
        printf("deaths: %d\n", new_user->deaths);
        textcolor(WHITE);
        printf("KD Ratio: %f\n", (((float)(new_user->kills))/((float)(new_user->deaths))));
        textcolor(RED);
        printf("total_score: %d\n", new_user->total_score);
        printf("headshots: %d\n", new_user->headshots);
        printf("matches_played: %d\n", new_user->matches_played);
        printf("matches_won: %d\n", new_user->matches_won);
        printf("shots_fired: %d\n", new_user->shots_fired);
        printf("shots_hit: %d\n", new_user->shots_hit);
    }
    fclose(arq_main_bin);
}

void OrdenaPorScore(char senha[])
{
    FILE *arq_main_bin, *arq_geral_bin;
    int valor[150], contador,atual, x, menor, indice, aux, i=0, j=0, temp;
    user *at, *men, *new_user;
    int top;

    at = (user*) malloc(sizeof(user));
    men = (user*) malloc(sizeof(user));


    arq_geral_bin = fopen("Plus de info de users.txt", "rb");
    fread(&contador, sizeof(int), 1, arq_geral_bin);
    fclose(arq_geral_bin);

    arq_main_bin = fopen("Arquivo.txt", "rb+");

    aux = contador;

    while(i < contador-1)
    {
        fseek(arq_main_bin, 204*i, SEEK_SET);
        fseek(arq_main_bin, 164+ 4* (sizeof(int)), SEEK_CUR);
        fread(&atual, sizeof(int), 1, arq_main_bin);
        j = i + 1;
        menor = 99999999999;

        while(j < aux)
        {
            fseek(arq_main_bin, 204*j, SEEK_SET);
            fseek(arq_main_bin, 164+ 4* (sizeof(int)), SEEK_CUR);
            fread(&temp, sizeof(int), 1, arq_main_bin);

            if (menor > temp)
            {
                menor = temp;
                indice = j;
            }
            j++;
        }

        if (menor < atual)
        {
            fseek(arq_main_bin, 204*i, SEEK_SET);
            fread(at, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fread(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*i, SEEK_SET);
            fwrite(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fwrite(at, sizeof(struct user), 1, arq_main_bin);
        }
        i++;
    }
    textcolor(YELLOW);
    printf("\tOs melhores scores\n");
    new_user = (user*) malloc(sizeof(user));
    textcolor(RED);

    for(i=1;i<4;i++)
    {
        textcolor(GREEN);
        printf("\n______TOP %d______ \n", i);
        fseek(arq_main_bin, -204*i , SEEK_END);
        fread(new_user, sizeof(user),1,arq_main_bin);

        Descriptografar(new_user, senha);
        textcolor(RED);
        printf("nome: ");
        puts(new_user->nome);
        printf("tempo_jogado: %d\narma_preferida1: ", new_user->tempo_jogado);
        puts(new_user->arma_preferida1);
        printf("arma_preferida2: ");
        puts(new_user->arma_preferida2);
        printf("mapa_preferido1: ");
        puts(new_user->mapa_preferido1);
        printf("mapa_preferido2: ");
        puts(new_user->mapa_preferido2);
        printf("kills: %d\n", new_user->kills);
        printf("deaths: %d\n", new_user->deaths);
        textcolor(YELLOW);
        printf("total_score: %d\n", new_user->total_score);
        textcolor(RED);
        printf("headshots: %d\n", new_user->headshots);
        printf("matches_played: %d\n", new_user->matches_played);
        printf("matches_won: %d\n", new_user->matches_won);
        printf("shots_fired: %d\n", new_user->shots_fired);
        printf("shots_hit: %d\n", new_user->shots_hit);
    }
    fclose(arq_main_bin);
}

void OrdenaPorHeadshot(char senha[])
{
    FILE *arq_main_bin, *arq_geral_bin;
    int valor[150], contador,atual, x, menor, indice, aux, i=0, j=0, temp;
    user *at, *men, *new_user;
    int top;

    at = (user*) malloc(sizeof(user));
    men = (user*) malloc(sizeof(user));


    arq_geral_bin = fopen("Plus de info de users.txt", "rb");
    fread(&contador, sizeof(int), 1, arq_geral_bin);
    fclose(arq_geral_bin);

    arq_main_bin = fopen("Arquivo.txt", "rb+");

    aux = contador;

    while(i < contador-1)
    {
        fseek(arq_main_bin, 204*i, SEEK_SET);
        fseek(arq_main_bin, 164+ 5* (sizeof(int)), SEEK_CUR);
        fread(&atual, sizeof(int), 1, arq_main_bin);
        j = i + 1;
        menor = 99999999999;

        while(j < aux)
        {
            fseek(arq_main_bin, 204*j, SEEK_SET);
            fseek(arq_main_bin, 164+ 5* (sizeof(int)), SEEK_CUR);
            fread(&temp, sizeof(int), 1, arq_main_bin);

            if (menor > temp)
            {
                menor = temp;
                indice = j;
            }
            j++;
        }

        if (menor < atual)
        {
            fseek(arq_main_bin, 204*i, SEEK_SET);
            fread(at, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fread(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*i, SEEK_SET);
            fwrite(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fwrite(at, sizeof(struct user), 1, arq_main_bin);
        }
        i++;
    }
    textcolor(YELLOW);
    printf("\tCom maior numero de headshots\n");
    new_user = (user*) malloc(sizeof(user));
    textcolor(RED);

    for(i=1;i<4;i++)
    {
        textcolor(GREEN);
        printf("\n______TOP %d______ \n", i);
        fseek(arq_main_bin, -204*i , SEEK_END);
        fread(new_user, sizeof(user),1,arq_main_bin);

        Descriptografar(new_user, senha);
        textcolor(RED);
        printf("nome: ");
        puts(new_user->nome);
        printf("tempo_jogado: %d\narma_preferida1: ", new_user->tempo_jogado);
        puts(new_user->arma_preferida1);
        printf("arma_preferida2: ");
        puts(new_user->arma_preferida2);
        printf("mapa_preferido1: ");
        puts(new_user->mapa_preferido1);
        printf("mapa_preferido2: ");
        puts(new_user->mapa_preferido2);
        printf("kills: %d\n", new_user->kills);
        printf("deaths: %d\n", new_user->deaths);
        printf("total_score: %d\n", new_user->total_score);
        textcolor(YELLOW);
        printf("headshots: %d\n", new_user->headshots);
        textcolor(RED);
        printf("matches_played: %d\n", new_user->matches_played);
        printf("matches_won: %d\n", new_user->matches_won);
        printf("shots_fired: %d\n", new_user->shots_fired);
        printf("shots_hit: %d\n", new_user->shots_hit);
    }
    fclose(arq_main_bin);
}

void OrdenaPorWin(char senha[])
{
    FILE *arq_main_bin, *arq_geral_bin;
    int valor[150], contador,atual, x, menor, indice, aux, i=0, j=0, temp;
    user *at, *men, *new_user;
    int top;

    at = (user*) malloc(sizeof(user));
    men = (user*) malloc(sizeof(user));


    arq_geral_bin = fopen("Plus de info de users.txt", "rb");
    fread(&contador, sizeof(int), 1, arq_geral_bin);
    fclose(arq_geral_bin);

    arq_main_bin = fopen("Arquivo.txt", "rb+");

    aux = contador;

    while(i < contador-1)
    {
        fseek(arq_main_bin, 204*i, SEEK_SET);
        fseek(arq_main_bin, 164+ 7* (sizeof(int)), SEEK_CUR);
        fread(&atual, sizeof(int), 1, arq_main_bin);
        j = i + 1;
        menor = 99999999999;

        while(j < aux)
        {
            fseek(arq_main_bin, 204*j, SEEK_SET);
            fseek(arq_main_bin, 164+ 7* (sizeof(int)), SEEK_CUR);
            fread(&temp, sizeof(int), 1, arq_main_bin);

            if (menor > temp)
            {
                menor = temp;
                indice = j;
            }
            j++;
        }

        if (menor < atual)
        {
            fseek(arq_main_bin, 204*i, SEEK_SET);
            fread(at, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fread(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*i, SEEK_SET);
            fwrite(men, sizeof(struct user), 1, arq_main_bin);

            fseek(arq_main_bin, 204*indice, SEEK_SET);
            fwrite(at, sizeof(struct user), 1, arq_main_bin);
        }
        i++;
    }
    textcolor(YELLOW);
    printf("\tCom maior numero de vitoria\n");
    new_user = (user*) malloc(sizeof(user));
    textcolor(RED);

    for(i=1;i<4;i++)
    {
        textcolor(GREEN);
        printf("\n______TOP %d______ \n", i);
        fseek(arq_main_bin, -204*i , SEEK_END);
        fread(new_user, sizeof(user),1,arq_main_bin);

        Descriptografar(new_user, senha);
        textcolor(RED);
        printf("nome: ");
        puts(new_user->nome);
        printf("tempo_jogado: %d\narma_preferida1: ", new_user->tempo_jogado);
        puts(new_user->arma_preferida1);
        printf("arma_preferida2: ");
        puts(new_user->arma_preferida2);
        printf("mapa_preferido1: ");
        puts(new_user->mapa_preferido1);
        printf("mapa_preferido2: ");
        puts(new_user->mapa_preferido2);
        printf("kills: %d\n", new_user->kills);
        printf("deaths: %d\n", new_user->deaths);
        printf("total_score: %d\n", new_user->total_score);
        printf("headshots: %d\n", new_user->headshots);
        printf("matches_played: %d\n", new_user->matches_played);
        textcolor(YELLOW);
        printf("matches_won: %d\n", new_user->matches_won);
        textcolor(RED);
        printf("shots_fired: %d\n", new_user->shots_fired);
        printf("shots_hit: %d\n", new_user->shots_hit);
    }
    fclose(arq_main_bin);
}

// Função que recebe a lista de armas e uma arma, adciona a nova arma na lista e devolve a lista.
lista_armas* AdcionarListaArmas(lista_armas *Lista_Armas, char arma[])
{
    lista_armas *Lista_Aux=Lista_Armas, *Lista_Aux2=Lista_Armas;
    int condicao1=0;

    if(Lista_Armas == NULL) // Se o primeiro elemento da lista for NULL, cria um novo elemento e adciona a arma.
    {
        Lista_Armas = (lista_armas*) malloc(sizeof(lista_armas));
        strcpy(Lista_Armas->arma, arma);
        Lista_Armas->contador = 1;
        Lista_Armas->prox = NULL;
    }
    else
    {
        while(Lista_Aux != NULL) // Se já existir elementos na lista, percorrer a lista.
        {
            if(strcmp(Lista_Aux->arma, arma) == 0)  // Se encontrar um elemento que é igual a arma recebida, incrementar o contador.
            {
                (Lista_Aux->contador) = ((Lista_Aux->contador) + 1);
                return Lista_Armas;                 // Logo em seguida, retornar o ponteiro incial da Lista.
            }
            Lista_Aux = Lista_Aux->prox;
        }

        Lista_Aux = (lista_armas*) malloc(sizeof(lista_armas)); // Percorreu a lista sem encontrar nenhum elemento igual a arma recebida.
        strcpy(Lista_Aux->arma, arma);                          // Logo, é necessario criar um novo elemento e encadea-lo ao final da lista.
        Lista_Aux->contador = 1;
        Lista_Aux->prox = NULL;
        while(Lista_Aux2->prox != NULL)
        {
            Lista_Aux2 = Lista_Aux2->prox;
        }
        Lista_Aux2->prox = Lista_Aux;

    }
    return Lista_Armas; // Retorna o ponteiro inicial da lista.
}

// Função que recebe a lista de mapas e um mapa, adciona o novo mapa na lista e devolve a lista.
lista_mapas* AdcionarListaMapas(lista_mapas *Lista_Mapas, char mapa[])
{
    lista_mapas *Lista_Aux=Lista_Mapas, *Lista_Aux2=Lista_Mapas;
    int condicao1=0;

    if(Lista_Mapas == NULL) // Se o primeiro elemento da lista for NULL, cria um novo elemento e adciona o mapa.
    {
        Lista_Mapas = (lista_mapas*) malloc(sizeof(lista_mapas));
        strcpy(Lista_Mapas->mapa, mapa);
        Lista_Mapas->contador = 1;
        Lista_Mapas->prox = NULL;
    }
    else
    {
        while(Lista_Aux != NULL)   // Se já existir elementos na lista, percorrer a lista.
        {
            if(strcmp(Lista_Aux->mapa, mapa) == 0)  // Se encontrar um elemento que é igual ao mapa recebido, incrementar o contador.
            {
                (Lista_Aux->contador) = ((Lista_Aux->contador) + 1);
                return Lista_Mapas;                 // Logo em seguida, retornar o ponteiro incial da Lista.
            }
            Lista_Aux = Lista_Aux->prox;
        }

        Lista_Aux = (lista_armas*) malloc(sizeof(lista_armas));  // Percorreu a lista sem encontrar nenhum elemento igual ao mapa recebido.
        strcpy(Lista_Aux->mapa, mapa);                           // Logo, é necessario criar um novo elemento e encadea-lo ao final da lista.
        Lista_Aux->contador = 1;
        Lista_Aux->prox = NULL;
        while(Lista_Aux2->prox != NULL)
        {
            Lista_Aux2 = Lista_Aux2->prox;
        }
        Lista_Aux2->prox = Lista_Aux;

    }
    return Lista_Mapas;  // Retorna o ponteiro inicial da lista.
}

// Função que cria as informações gerais
void CriaInformacoesGerais(char senha[])
{
    information* teste;
    FILE *arq_main_bin;
    FILE* arq_geral_bin;
    int valor[9][150], contador, aux,i=0,j,soma, media, desvio, maior1, maior2, k=0, w=0, kills, deaths, headshots, shots, shotright, jogou, ganhou;
    float s;
    char arma1[21], mapa1[41], arma2[21], mapa2[41];
    lista_armas *Lista_Armas=NULL;
    lista_mapas *Lista_Mapas=NULL;

    arq_geral_bin = fopen("Plus de info de users.txt", "rb");
    fread(&contador, sizeof(int), 1, arq_geral_bin);
    fclose(arq_geral_bin);
    arq_main_bin = fopen("Arquivo.txt", "rb");

    contador++;
    aux=contador;

    while (contador>1)
    {
        fseek(arq_main_bin, 204*(contador-2), SEEK_SET);
        fseek(arq_main_bin, 40+sizeof(int), SEEK_CUR);
        fread(&valor[0][contador], sizeof(int), 1, arq_main_bin);
        fread(&arma1, 21, 1, arq_main_bin);
        fread(&arma2, 21, 1, arq_main_bin);
        fread(&mapa1, 41, 1, arq_main_bin);
        fread(&mapa2, 41, 1, arq_main_bin);
        Lista_Armas = AdcionarListaArmas(Lista_Armas, arma1);
        Lista_Armas = AdcionarListaArmas(Lista_Armas, arma2);
        Lista_Mapas = AdcionarListaMapas(Lista_Mapas, mapa1);
        Lista_Mapas = AdcionarListaMapas(Lista_Mapas, mapa2);
        fseek(arq_main_bin, 204*(contador-2), SEEK_SET);
        fseek(arq_main_bin, 40+2*sizeof(int), SEEK_CUR);
        fseek(arq_main_bin, 124, SEEK_CUR);
        fread(&valor[1][contador], sizeof(int), 1, arq_main_bin);
        fread(&valor[2][contador], sizeof(int), 1, arq_main_bin);
        fread(&valor[3][contador], sizeof(int), 1, arq_main_bin);
        fread(&valor[4][contador], sizeof(int), 1, arq_main_bin);
        fread(&valor[5][contador], sizeof(int), 1, arq_main_bin);
        fread(&valor[6][contador], sizeof(int), 1, arq_main_bin);
        fread(&valor[7][contador], sizeof(int), 1, arq_main_bin);
        fread(&valor[8][contador], sizeof(int), 1, arq_main_bin);
        contador--;
    }
    fseek(arq_main_bin, 0, SEEK_END);
    fclose(arq_main_bin);

    //SOMATÓRIO, MÉDIAS E DESVIOS PADRÕES------------------------
    contador=aux-1;
    arq_geral_bin = fopen("Plus de info de users.txt", "wb");
    fwrite(&contador, sizeof(int), 1, arq_geral_bin);

    for(j=0; 9>j; j++)
    {
        soma=0;
        for(i=aux; i>1; i--)
        {
            soma=soma + valor[j][i];

        }
            fwrite(&soma, sizeof(int), 1, arq_geral_bin);
            media= soma/contador;
            fwrite(&media, sizeof(int), 1, arq_geral_bin);
            desvio=DesvioPadrao(media, contador, &valor, j);
            fwrite(&desvio, sizeof(int), 1, arq_geral_bin);
            if (j==1) kills=soma;
            if (j==2) deaths=soma;
            if (j==4) headshots=soma;
            if (j==5) jogou=soma;
            if (j==6) ganhou=soma;
            if (j==7) shots=soma;
            if (j==8) shotright=soma;

    }
    s = (float)ganhou / (float)jogou;
    fwrite(&s, sizeof(float), 1, arq_geral_bin);

    s=(float)kills/(float)deaths;
    fwrite(&s, sizeof(float), 1, arq_geral_bin);

    s=(float)shotright/(float)shots;
    fwrite(&s, sizeof(float), 1, arq_geral_bin);

    s=(float)headshots/(float)kills;
    fwrite(&s, sizeof(float), 1, arq_geral_bin);

    //mapa e arma preferido

    maior1=0;
    maior2=0;
    while(Lista_Armas != NULL)
    {
        if (Lista_Armas->contador > maior1)
        {
            maior2=maior1;
            maior1=Lista_Armas->contador;
            strcpy(arma2,arma1);
            strcpy(arma1,Lista_Armas->arma);
        }
        else
        {
            if(Lista_Armas->contador > maior2)
            {
                maior2=Lista_Armas->contador;
                strcpy(arma2,Lista_Armas->arma);
            }
        }
        Lista_Armas=Lista_Armas->prox;
    }

    maior1=0;
    maior2=0;
    while(Lista_Mapas != NULL)
    {
        if (Lista_Mapas->contador > maior1)
        {
            maior2=maior1;
            maior1=Lista_Mapas->contador;
            strcpy(mapa2,mapa1);
            strcpy(mapa1,Lista_Mapas->mapa);
        }
        else
        {
            if(Lista_Mapas->contador > maior2)
            {
                maior2=Lista_Mapas->contador;
                strcpy(mapa2,Lista_Mapas->mapa);
            }
        }
        Lista_Mapas=Lista_Mapas->prox;
    }
    fwrite(&mapa1, 41, 1, arq_geral_bin);
    fwrite(&mapa2, 41, 1, arq_geral_bin);
    fwrite(&arma1, 21, 1, arq_geral_bin);
    fwrite(&arma2, 21, 1, arq_geral_bin);

    fclose(arq_geral_bin);

    teste = (information*) malloc(sizeof(information));

    textcolor(GREEN);
    printf("\tINFORMACOES GERAIS  -  foi usado dados de todos os usuarios\n");
    textcolor(YELLOW);
    teste = ReadArqBinInfGerais(teste);
    PrintInformation(teste, senha);
}

// Função para adcionar um usuario novo ao arquivo binario (e ao txt).
void AdcionaUser(char senha[])
{
    FILE *arquivo, *arquivo_geral, *arquivo_txt;
    char nome[41], arma_preferida1[21], arma_preferida2[21], mapa_preferido1[41], mapa_preferido2[41];
    int kills,deaths,total_score,headshots,matches_played,matches_won,shots_fired,shots_hit,tempo_jogado, contador;
    user *novo_user;

    novo_user = (user*) malloc(sizeof(user));

    arquivo = fopen("arquivo.txt", "ab");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo binario.");
        return;
    }

    printf("\nInforme o nome do usuario:");
    gets(nome);
    printf("\nInforme o tempo de jogo do usuario em horas:");
    scanf("%d", &tempo_jogado);
    novo_user->tempo_jogado = tempo_jogado;
    fflush(stdin);
    printf("\nInforme a primeira arma preferida do usuario:");
    gets(arma_preferida1);
    printf("\nInforme a segunda arma preferida do usuario:");
    gets(arma_preferida2);
    printf("\nInforme o primeiro mapa preferido do usuario:");
    gets(mapa_preferido1);
    printf("\nInforme o segundo mapa preferido do usuario:");
    gets(mapa_preferido2);
    printf("\nInforme a quantidade de kills do usuario:");
    scanf("%d", &kills);
    novo_user->kills = kills;
    printf("\nInforme a quantidade de deaths do usuario:");
    scanf("%d", &deaths);
    novo_user->deaths = deaths;
    printf("\nInforme a quantidade de score do usuario:");
    scanf("%d", &total_score);
    novo_user->total_score = total_score;
    printf("\nInforme a quantidade de headshots do usuario:");
    scanf("%d", &headshots);
    novo_user->headshots = headshots;
    printf("\nInforme a quantidade de partidas do usuario:");
    scanf("%d", &matches_played);
    novo_user->matches_played = matches_played;
    printf("\nInforme a quantidade de vitorias usuario:");
    scanf("%d", &matches_won);
    novo_user->matches_won = matches_won;
    printf("\nInforme a quantidade de tiros realizados pelo usuario:");
    scanf("%d", &shots_fired);
    novo_user->shots_fired = shots_fired;
    printf("\nInforme a quantidade de tiros acertados pelo usuario:");
    scanf("%d", &shots_hit);
    novo_user->shots_hit = shots_hit;

    strcpy(novo_user->nome, nome);
    strcpy(novo_user->arma_preferida1, arma_preferida1);
    strcpy(novo_user->arma_preferida2, arma_preferida2);
    strcpy(novo_user->mapa_preferido1, mapa_preferido1);
    strcpy(novo_user->mapa_preferido2, mapa_preferido2);
    fwrite(novo_user, sizeof(user), 1, arquivo);
    fclose(arquivo);

    arquivo_txt = fopen("cpd.txt", "a");
    if(arquivo_txt == NULL)
    {
        printf("Erro ao abrir o arquivo txt.");
        return;
    }

    fprintf(arquivo_txt, "\n#%s#%d#%s#%s#%s#%s#%d#%d#%d#%d#%d#%d#%d#%d#", novo_user->nome, novo_user->tempo_jogado, novo_user->arma_preferida1,
            novo_user->arma_preferida2, novo_user->mapa_preferido1, novo_user->mapa_preferido2, novo_user->kills, novo_user->deaths,
            novo_user->total_score, novo_user->headshots, novo_user->matches_played, novo_user->matches_won, novo_user->shots_fired, novo_user->shots_hit);
    fclose(arquivo_txt);

    arquivo_geral = fopen("Plus de info de users.txt", "r+b");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo binario.");
        return;
    }

    fread(&contador, sizeof(int), 1, arquivo_geral);
    contador = contador + 1;
    rewind(arquivo_geral);
    fwrite(&contador, sizeof(int), 1, arquivo_geral);
    fclose(arquivo_geral);
    system("cls");
    LerArquivoTxt(senha);
    printf("\n");
    system("pause");
    system("cls");
    CriaInformacoesGerais(senha);
    printf("\n");
    system("pause");
    system("cls");
}

void Legenda()
{
    textcolor(WHITE);
    printf("LEGENDA:\tOBS: pode inverter a escala, como no caso das deaths\n");
    textcolor(RED);
    printf("________________");
    textcolor(WHITE);
    printf("|");
    textcolor(YELLOW);
    printf("_______________________________");
    textcolor(WHITE);
    printf("|");
    textcolor(GREEN);
    printf("_______________\n");


    textcolor(RED);
    printf("  RUIM    ");
    textcolor(YELLOW);
    printf("              MEDIO                 ");
    textcolor(GREEN);
    printf("     OTIMO\n");

    textcolor(RED);
    printf("abaixo da media");
    textcolor(YELLOW);
    printf("  entre media +/- desvio padrao");
    textcolor(GREEN);
    printf("    acima da media\n");

    textcolor(WHITE);
}

void PesquisarUser(char senha[])
{
    FILE *arq_main_bin;
    char nome[41];
    user* escolhido;
    information* dados;
    int posicao=0, i;
    float aux;
    trie *arv;

    Legenda();
    arv = CriaTRIE();

    printf("\n\nNome do usuario: ");
    gets(nome);
    CriptografarPalavra(nome, senha);

    i = 0;
    while(i < 41)
    {
        nome[i] = toupper(nome[i]);
        i++;
    }

    if(PesquisaNaTRIE(arv, nome, senha) == -1)
    {
        printf("O USUARIO NAO EXISTE!!!\n");
        return;
    }
    posicao = PesquisaNaTRIE(arv, nome, senha);

    escolhido = (user*) malloc(sizeof(user));
    dados = (information*) malloc(sizeof(information));

    arq_main_bin = fopen("Arquivo.txt", "rb");
    fseek(arq_main_bin, posicao, SEEK_SET);
    fread(escolhido, sizeof (struct user), 1, arq_main_bin);
    fclose(arq_main_bin);


    dados = ReadArqBinInfGerais(dados);

    Descriptografar(escolhido, senha);

    printf("\narma_preferida1: ");
    puts(escolhido->arma_preferida1);
    printf("arma_preferida2: ");
    puts(escolhido->arma_preferida2);
    printf("mapa_preferido1: ");
    puts(escolhido->mapa_preferido1);
    printf("mapa_preferido2: ");
    puts(escolhido->mapa_preferido2);

    if(escolhido->tempo_jogado > (dados->media_tempo_jogado + dados->desvio_padrao_tempo_jogado)) textcolor(GREEN);
    else
    {
        if(escolhido->tempo_jogado < (dados->media_tempo_jogado - dados->desvio_padrao_tempo_jogado)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("tempo_jogado: %d\n", escolhido->tempo_jogado);

    if(escolhido->kills > (dados->media_kills + dados->desvio_padrao_kills)) textcolor(GREEN);
    else
    {
        if(escolhido->kills < (dados->media_kills- dados->desvio_padrao_kills)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("kills: %d\n", escolhido->kills);

    if(escolhido->deaths < (dados->media_deaths + dados->desvio_padrao_deaths)) textcolor(GREEN);
    else
    {
        if(escolhido->deaths > (dados->media_deaths- dados->desvio_padrao_deaths)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("deaths: %d\n", escolhido->deaths);

    if (escolhido->total_score>(dados->media_total_score + dados->desvio_padrao_total_score)) textcolor(GREEN);
    else
    {
        if (escolhido->total_score<(dados->media_total_score- dados->desvio_padrao_total_score)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("total_score: %d\n", escolhido->total_score);

    if(escolhido->headshots > (dados->media_headshots + dados->desvio_padrao_headshots)) textcolor(GREEN);
    else
    {
        if(escolhido->headshots < (dados->media_headshots- dados->desvio_padrao_headshots)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("headshots: %d\n", escolhido->headshots);

    if(escolhido->matches_played > (dados->media_matches_played + dados->desvio_padrao_matches_played)) textcolor(GREEN);
    else
    {
        if(escolhido->matches_played < (dados->media_matches_played- dados->desvio_padrao_matches_played)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("matches_played: %d\n", escolhido->matches_played);

    if(escolhido->matches_won > (dados->media_matches_won + dados->desvio_padrao_matches_won)) textcolor(GREEN);
    else
    {
        if(escolhido->matches_won < (dados->media_matches_won- dados->desvio_padrao_matches_won)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("matches_won: %d\n", escolhido->matches_won);

    if(escolhido->shots_fired > (dados->media_shots_fired + dados->desvio_padrao_shots_fired)) textcolor(GREEN);
    else
    {
        if(escolhido->shots_fired < (dados->media_shots_fired- dados->desvio_padrao_shots_fired)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("shots_fired: %d\n", escolhido->shots_fired);

    if(escolhido->shots_hit > (dados->media_shots_hit + dados->desvio_padrao_shots_hit)) textcolor(GREEN);
    else
    {
        if(escolhido->shots_hit < (dados->media_shots_hit- dados->desvio_padrao_shots_hit)) textcolor(RED);
        else textcolor(YELLOW);
    }
    printf("shots_hit: %d\n", escolhido->shots_hit);

    //ESTATISTICAS-------------------------------------------------------------------------------

    aux = (float)(escolhido->matches_won) / (float)(escolhido->matches_played);
    if(aux>= dados->win_per_game) textcolor(GREEN);
    else  textcolor(RED);
    printf("win/game= %f\n", aux);

    aux = (float)(escolhido->kills) / (float)(escolhido->deaths);
    if(aux>= dados->KDA) textcolor(GREEN);
    else  textcolor(RED);
    printf("kills/deaths: %f\n", aux);

    aux = (float)(escolhido->shots_hit) / (float)(escolhido->shots_fired);
    if(aux>= dados->acertos_de_tiros) textcolor(GREEN);
    else  textcolor(RED);
    printf("tiros_certeiros/tiros: %f\n", aux);

    aux = (float)(escolhido->headshots) / (float)(escolhido->kills);
    if(aux >= dados->kill_de_headshot) textcolor(GREEN);
    else  textcolor(RED);
    printf("headshots/kills: %f\n\n\n\n", aux);


}

main()
{
    FILE *arqtxt, *arq_main_bin;
    int campo=-1, i=0, local, num_de_user=0, *controlador, controlador_aux=1, k=0, condicao1_senha=1, condicao2_senha=1, flag=0, controlador_menu=0;
    char str[50], c, nome_txt[40], nome_binario[40];
    user *new_user, *user_escolhido, *user_escolhido2;

    // senha não predefinida
     char senha[10];
    // senha predefinida
    //char senha[10]={'2','3','1','1','2','1','3','1','\0'};

// Para desabilitar a parte da senha, basta comentar todo esse DO e habilitar o char senha com a senha predefinida ali em cima.
    do
    {
        printf("Informe a senha numerica de no maximo 8 digitos para descriptografar:");
        gets(senha);
        k = strlen(senha);
        if(k > 8)
        {
            printf("\nSenha maior do que oito digitos.\n");
            condicao1_senha = 0;
        }
        else
        {
            condicao1_senha = 1;
        }
        k = k - 1;
        flag = 0;
        while(k != 0)
        {
            if(senha[k] != '0' && senha[k] != '1' && senha[k] != '2' && senha[k] != '3' && senha[k] != '4' && senha[k] != '5' && senha[k] != '6'
               && senha[k] != '7' && senha[k] != '8' && senha[k] != '9')
            {
                printf("\nSenha contem caracteres nao permitidos.\n");
                condicao2_senha = 0;
                flag++;
                break;
            }
            k--;
        }
        if(flag == 0)
        {
            condicao2_senha = 1;
        }
    }while((condicao1_senha == 0) || (condicao2_senha == 0));

    while(controlador_menu == 0)
    {
        system("cls");
        controlador = &controlador_aux;
        textcolor(RED);
        textbackground(WHITE);
        printf("[1] Montar o arquivo Binario.\n");
        textbackground(BLACK);
        printf("[2] Ordena arquivo Binario.\n");
        printf("[3] Informacoes gerais.\n");
        printf("[4] Adcionar User.\n");
        printf("[5] Pesquisar User.\n");
        printf("[6] Sair.\n");
        controlador_menu = Menu(controlador, senha);
    }
}
