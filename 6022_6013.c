//Breno Thiago Mororó Afonso - 6013 Lucas Messias Magno - 6022
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x, y;

void gera_bomba(int x, int y, char tabuleiro_auxiliar[9 + 2][9 + 2], int bombas)
{
    int x_rand, y_rand, controle;
    for (int i = 0; i < bombas; i++)
    {
        controle = 0;
        x_rand = 1 + (rand() % 9);
        y_rand = 1 + (rand() % 9);
        // trata as colisões de bombas
        if (tabuleiro_auxiliar[x_rand][y_rand] == '*')
        {
            gera_bomba(x, y, tabuleiro_auxiliar, 1);
            controle = 1;
        }
        // nao gerar bomba na posição inicial e na adjacencia 8
        if (((x - 1) == x_rand && (y - 1) == y_rand) || ((x - 1) == x_rand && y == y_rand) || ((x - 1) == x_rand && (y + 1) == y_rand) || (x == x_rand && (y - 1) == y_rand) || (x == x_rand && y == y_rand) || (x == x_rand && (y + 1) == y_rand) || ((x + 1) == x_rand && (y - 1) == y_rand) || ((x + 1) == x_rand && y == y_rand) || ((x + 1) == x_rand && (y + 1) == y_rand))
        {
            gera_bomba(x, y, tabuleiro_auxiliar, 1);
            controle = 1;
        }
        if (tabuleiro_auxiliar[x_rand][y_rand] == '0' && controle == 0)
        {
            tabuleiro_auxiliar[x_rand][y_rand] = '*';
        }
    }
}

void adjacente(char tabuleiro_auxiliar[9 + 2][9 + 2])
{
    char count;
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            count = '0';
            if (tabuleiro_auxiliar[i][j] != '*')
            {
                //if (isdigit())
                if (tabuleiro_auxiliar[i - 1][j - 1] == '*')
                {
                    count++;
                }
                if (tabuleiro_auxiliar[i - 1][j] == '*')
                {
                    count++;
                }
                if (tabuleiro_auxiliar[i - 1][j + 1] == '*')
                {
                    count++;
                }
                if (tabuleiro_auxiliar[i][j - 1] == '*')
                {
                    count++;
                }
                if (tabuleiro_auxiliar[i][j + 1] == '*')
                {
                    count++;
                }
                if (tabuleiro_auxiliar[i + 1][j - 1] == '*')
                {
                    count++;
                }
                if (tabuleiro_auxiliar[i + 1][j] == '*')
                {
                    count++;
                }
                if (tabuleiro_auxiliar[i + 1][j + 1] == '*')
                {
                    count++;
                }
                tabuleiro_auxiliar[i][j] = count;
            }
        }
    }
}

void transporta_valor(int x, int y, char tabuleiro[9 + 2][9 + 2], char tabuleiro_auxiliar[9 + 2][9 + 2])
{
    if (isdigit(tabuleiro[x][y]) && tabuleiro[x][y] != 0)
    {
        return;
    }
    if (tabuleiro_auxiliar[x - 1][y] != '*')
    {
        tabuleiro[x - 1][y] = tabuleiro_auxiliar[x - 1][y];
    }
    if (tabuleiro_auxiliar[x][y - 1] != '*')
    {
        tabuleiro[x][y - 1] = tabuleiro_auxiliar[x][y - 1];
    }
    if (tabuleiro_auxiliar[x][y + 1] != '*')
    {
        tabuleiro[x][y + 1] = tabuleiro_auxiliar[x][y + 1];
    }
    if (tabuleiro_auxiliar[x + 1][y] != '*')
    {
        tabuleiro[x + 1][y] = tabuleiro_auxiliar[x + 1][y];
    }
    if (tabuleiro_auxiliar[x - 1][y - 1] != '0' && tabuleiro_auxiliar[x - 1][y - 1] != '*')
    {
        tabuleiro[x - 1][y - 1] = tabuleiro_auxiliar[x - 1][y - 1];
    }
    if (tabuleiro_auxiliar[x - 1][y + 1] != '0' && tabuleiro_auxiliar[x - 1][y + 1] != '*')
    {
        tabuleiro[x - 1][y + 1] = tabuleiro_auxiliar[x - 1][y + 1];
    }
    if (tabuleiro_auxiliar[x + 1][y - 1] != '0' && tabuleiro_auxiliar[x + 1][y - 1] != '*')
    {
        tabuleiro[x + 1][y - 1] = tabuleiro_auxiliar[x + 1][y - 1];
    }
    if (tabuleiro_auxiliar[x + 1][y + 1] != '0' && tabuleiro_auxiliar[x + 1][y + 1] != '*')
    {
        tabuleiro[x + 1][y + 1] = tabuleiro_auxiliar[x + 1][y + 1];
    }
}

void expandir(int x, int y, char tabuleiro[9 + 2][9 + 2], char tabuleiro_auxiliar[9 + 2][9 + 2])
{
    if (tabuleiro_auxiliar[x][y] == '0')
    {
        tabuleiro_auxiliar[x][y] = '-';
        tabuleiro[x][y] = '-';
    }
    else
    {
        tabuleiro[x][y] = tabuleiro_auxiliar[x][y];
    }
    transporta_valor(x, y, tabuleiro, tabuleiro_auxiliar);
    if (tabuleiro_auxiliar[x - 1][y] == '0')
    {
        expandir(x - 1, y, tabuleiro, tabuleiro_auxiliar);
    }
    if (tabuleiro_auxiliar[x][y - 1] == '0')
    {
        expandir(x, y - 1, tabuleiro, tabuleiro_auxiliar);
    }
    if (tabuleiro_auxiliar[x][y + 1] == '0')
    {
        expandir(x, y + 1, tabuleiro, tabuleiro_auxiliar);
    }
    if (tabuleiro_auxiliar[x + 1][y] == '0')
    {
        expandir(x + 1, y, tabuleiro, tabuleiro_auxiliar);
    }
}

void printa_tabuleiro(char tabuleiro[9 + 2][9 + 2])
{
    printf("\t");
    for (int y = 0; y < 11; y++)
    {
        if (y != 0 && y != 10)
        {
            printf("%d ", y);
        }
        else
        {
            printf("  ");
        }
    }
    printf("\n\n");
    for (int x = 0; x < 11; x++)
    {
        if (x != 0 && x != 10)
        {
            printf("%d ", x);
        }
        else
        {
            printf("  ");
        }
        printf("\t");
        for (int y = 0; y < 11; y++)
        {
            printf("%c ", tabuleiro[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

void instancia_tabuleiro(char tabuleiro[9 + 2][9 + 2], char tabuleiro_auxiliar[9 + 2][9 + 2])
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            // Instancia um Tabuleiro Vazio
            tabuleiro[i][j] = '#';
            tabuleiro_auxiliar[i][j] = '0';

            // Adiciona Bordas ao Tabuleiro
            if (i == 0)
            {
                tabuleiro[0][j] = '@';
                tabuleiro_auxiliar[0][j] = '@';
            }
            if (i == 10)
            {
                tabuleiro[10][j] = '@';
                tabuleiro_auxiliar[10][j] = '@';
            }
            if (j == 0)
            {
                tabuleiro[i][0] = '@';
                tabuleiro_auxiliar[i][0] = '@';
            }
            if (j == 10)
            {
                tabuleiro[i][10] = '@';
                tabuleiro_auxiliar[i][10] = '@';
            }
        }
    }
}

int verificacao_ganhou(char tabuleiro[9 + 2][9 + 2], char tabuleiro_auxiliar[9 + 2][9 + 2])
{
    int count = 0;
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            if (tabuleiro[i][j] == '#' || (tabuleiro_auxiliar[i][j] == '*' && tabuleiro[i][j] == 'B'))
            {
                count++;
            }
        }
    }
    if (count == 10)
    {
        return 1; // Ganhou
    }
    return 0; // Ainda não ganhou
}

int acao()
{
    int x_aux, y_aux;
    int controle = 0;
    int opcao;
    printf("Bandeira(2) ou Abrir(1): ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        do
        {
            printf("Insira a linha da jogada: ");
            scanf("%d", &x_aux);
            printf("Insira a coluna da jogada: ");
            scanf("%d", &y_aux);
            if (x_aux > 0 || x_aux < 11 || y_aux > 0 || y_aux < 11)
            {
                controle = 1;
                x = x_aux;
                y = y_aux;
                break;
            }
            printf("Jogada invalida\n");
        } while (controle == 0);
        return 1;
        break;

    case 2:
        do
        {
            printf("Insira a linha para inserir a bandeira: ");
            scanf("%d", &x_aux);
            printf("Insira a coluna para inserir a bandeira: ");
            scanf("%d", &y_aux);
            if (x_aux > 0 || x_aux < 11 || y_aux > 0 || y_aux < 11)
            {
                controle = 1;
                x = x_aux;
                y = y_aux;
                break;
            }
            printf("Jogada invalida\n");
        } while (controle == 0);
        return 2;
        break;

    default:
        printf("Opcao Invalida\n");
        acao();
        break;
    }
}

int menu_config()
{
    int menu_opcao, config_x = 9, config_y = 9, config_bombas = 10;
    //system("cls || clear");
    printf("O que deseja:\nDefinir o numero de linhas - digite 1\nDefinir o numero de colunas - digite 2\nDefinir o numero de bombas - digite 3\nVoltar ao menu inicial - digite 4\n");
    scanf("%d", &menu_opcao);
    printf("Var Menu Opcao: %d", menu_opcao);
    switch (menu_opcao)
    {
    case 1:
        printf("Digite o numero de linhas\n");
        scanf("%d", &config_x);
        menu_config();
        break;
    case 2:
        printf("Digite o numero de colunas\n");
        scanf("%d", &config_y);
        menu_config();
        break;
    case 3:
        printf("Digite o numero de bombas\n");
        scanf("%d", &config_bombas);
        menu_config();
        break;
    case 4:
        menu_opcao = menu();
        break;
    default:
        printf("Por favor digite uma opcao valida!\n");
        break;
    }
}

int menu()
{
    int menu_opcao;
    system("cls || clear");
    printf("\tCAMPO MINADO\n");
    printf("\nMENU\nO que deseja:\nNovo Jogo - digite 1\nConfiguracao - digite 2\nSair - digite 3\n");
    scanf("%d", &menu_opcao);
    switch (menu_opcao)
    {
    case 1:
        return 1;
        break;
    case 2:
        menu_config();
        break;
    case 3:
        printf("Fechando\n");
        exit(1);
        break;
    default:
        printf("Por favor digite uma opcao valida!\n");
        break;
    }
    return 0;
}

int main()
{
    system("cls || clear");
    srand(time(NULL));
    int opcao_menu, acao_retorno, controle, boleano = 1, count = 0, count_bandeiras;

    char tabuleiro[9 + 2][9 + 2], tabuleiro_auxiliar[9 + 2][9 + 2];

    opcao_menu = menu();
    switch (opcao_menu)
    {
    case 1: // Começar o jogo
        system("cls || clear");
        instancia_tabuleiro(tabuleiro, tabuleiro_auxiliar);
        while (boleano == 1)
        {
            printf("------- CAMPO MINADO -------\n");
            printa_tabuleiro(tabuleiro);
            //printa_tabuleiro(tabuleiro_auxiliar);
            controle = 0;
            acao_retorno = acao();

            if (acao_retorno == 1)
            {
                if (tabuleiro[x][y] == '-' || isdigit(tabuleiro[x][y]))
                {
                    printf("Voce nao pode abrir uma posição ja aberta\n");
                    acao_retorno = acao();
                    controle = 1;
                }
                if (tabuleiro[x][y] == 'B')
                {
                    printf("Voce nao pode abrir uma bandeira\n");
                    acao_retorno = acao();
                    controle = 1;
                }
                if (count == 0 && controle == 0)
                {
                    gera_bomba(x, y, tabuleiro_auxiliar, 10);
                    adjacente(tabuleiro_auxiliar);
                    expandir(x, y, tabuleiro, tabuleiro_auxiliar);
                }
                else if (count >= 1 && controle == 0)
                {
                    count = 0;
                    expandir(x, y, tabuleiro, tabuleiro_auxiliar);
                    controle = verificacao_ganhou(tabuleiro, tabuleiro_auxiliar);
                    if (controle == 1)
                    {
                        system("cls || clear");
                        printa_tabuleiro(tabuleiro);
                        printf("Voce ganhou!\n");
                        boleano = 0;
                    }
                }
                if (tabuleiro_auxiliar[x][y] == '*')
                {
                    system("cls || clear");
                    printf("Voce perdeu!\n");
                    printa_tabuleiro(tabuleiro_auxiliar);
                    controle = 1;
                    boleano = 0;
                }
            }
            else if (acao_retorno == 2)
            {
                if (tabuleiro[x][y] == 'B')
                {
                    printf("Voce nao pode colocar uma bandeira em outra bandeira\n");
                    acao_retorno = acao();
                    controle = 1;
                }
                if (tabuleiro[x][y] == '-')
                {
                    printf("Voce nao pode colocar uma bandeira em uma posicao bandeira\n");
                    acao_retorno = acao();
                    controle = 1;
                }
                if (controle == 0)
                {
                    tabuleiro[x][y] = 'B';
                    count_bandeiras++;
                }
            }
            count++;
            printf("Jogada Numero: %d\n", (count+1));
            printf("Numero de Bandeiras: %d/10\n", count_bandeiras);
        }
        break;

    default:
        printf("Falha catastrofica, começe o jogo novamente!\n");
        exit(1);
        break;
    }
    return 0;
}