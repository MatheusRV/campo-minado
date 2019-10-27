#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_bomba(char tabuleiro_auxiliar[9 + 2][9 + 2], int bombas)
{
    srand(time(NULL));
    //srand(1);
    int x_rand, y_rand;
    for (int i = 0; i < bombas; i++)
    {
        x_rand = 1 + (rand() % 9);
        y_rand = 1 + (rand() % 9);
        if (tabuleiro_auxiliar[x_rand][y_rand] != '*')
        {
            tabuleiro_auxiliar[x_rand][y_rand] = '*';
        }
        // trata as colisões de bombas
        else
        {
            gera_bomba(tabuleiro_auxiliar, 1);
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

void transporta(int x, int y, char tabuleiro[9 + 2][9 + 2], char tabuleiro_auxiliar[9 + 2][9 + 2])
{
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
        tabuleiro_auxiliar[x][y] = '+';
        tabuleiro[x][y] = '-';
    }
    else
    {
        tabuleiro[x][y] = tabuleiro_auxiliar[x][y];
    }
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
    transporta(x, y, tabuleiro, tabuleiro_auxiliar);
}

void inserir(int x, int y, int tipo)
{
    int retorno_verifica;
    do
    {
        if (tipo == 1)
        {
            printf("Insira a linha que deseja colocar a bandeira: ");
            scanf("%d", &x);
            printf("Insira a coluna que deseja colocar a bandeira: ");
            scanf("%d", &y);
        }
        else
        {
            printf("Insira a linha da jogada: ");
            scanf("%d", &x);
            printf("Insira a coluna da jogada: ");
            scanf("%d", &y);
        }
        if (x > 1 || x < 10 || y > 1 || y < 10)
        {
            retorno_verifica = 1;
            break;
        }
        printf("Jogada invalida\n");
    } while (retorno_verifica == 0);
}

void preenche_tabuleiro(char tabuleiro[9 + 2][9 + 2], char tabuleiro_auxiliar[9 + 2][9 + 2])
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            tabuleiro[i][j] = '#';
            tabuleiro_auxiliar[i][j] = '#';
        }
    }
    gera_bomba(tabuleiro_auxiliar, 10);
    adjacente(tabuleiro_auxiliar);
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
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

void jogo(int x_init, int y_init, int bombas)
{
    char tabuleiro[9 + 2][9 + 2], tabuleiro_auxiliar[9 + 2][9 + 2];
    int ganhou = 0;
    system("cls || clear");
    preenche_tabuleiro(tabuleiro, tabuleiro_auxiliar);
    int count = 0;
    while (ganhou != 1)
    {
        system("cls || clear");
        printf("----------------------------------------------\n");
        printf("\t\t CAMPO MINADO\n");
        printf("----------------------------------------------\n");
        printa_tabuleiro(tabuleiro);
        printf("\n");
        printa_tabuleiro(tabuleiro_auxiliar);
        int opcao, x, y;
        printf("Bandeira(-1) ou Abrir(1): ");
        scanf("%d", &opcao);
        if (opcao == -1)
        {
            printf("%d", x);
            inserir(x, y, 1);
            if (tabuleiro[x][y] == '-' || tabuleiro[x][y] == '1' || tabuleiro[x][y] == '2' || tabuleiro[x][y] == '4')
            {
                printf("Voce nao pode colocar uma bandeira na posicao ja aberta\n");
            }
            else
            {
                tabuleiro[x][y] = 'B';
            }
        }
        else
        {
            inserir(x, y, 0);
            if (tabuleiro[x][y] == 'B')
            {
                printf("Voce nao pode abrir uma bandeira\n");
                system("pause");
            }
            else if (tabuleiro_auxiliar[x][y] == '*')
            {
                printf("Voce perdeu\n");
                system("pause");
                exit(1);
            }
            else
            {
                expandir(x, y, tabuleiro, tabuleiro_auxiliar);
            }
        }
    }
}

int menu_config()
{
    int menu_opcao, config_x = 9, config_y = 9, config_bombas = 10;
    system("cls || clear");
    printf("O que deseja:\nDefinir o numero de linhas - digite 1\nDefinir o numero de colunas - digite 2\nDefinir o numero de bombas - digite 3\nVoltar ao menu inicial - digite 4\n");
    scanf("%d", &menu_opcao);
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
        menu();
        break;
    default:
        printf("Por favor digite uma opcao valida!\n");
        break;
    }
}

int menu()
{
    int menu_opcao;
    //system("cls || clear");
    printf("----------------------------------------------\n");
    printf("\t\t CAMPO MINADO\n");
    printf("----------------------------------------------\n");
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

    int controle;
    controle = menu();
    if (controle == 1)
    {
        jogo(9, 9, 10);
    }
    else
    {
        printf("Falha catastrofica!\n");
        exit(1);
    }

    return 0;
}