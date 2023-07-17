#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>

//faz o calculo da distancia de cada ponto em relação ao ponto 3 "cheagada"
void calc(int *mapa, int *val)
{

    int mapacopy[16][16];
    int valores[16][16];
    int x = 1;

    for(int x = 0; x <16; x++)
    {
        for(int y = 0; y <16; y++)
        {
            mapacopy[x][y] = *mapa;
            *mapa++;
        }
    }
    for(int x = 0; x <16; x++)
    {
        for(int y = 0; y <16; y++)
        {
            valores[x][y] = *val;
            *val++;
        }
    }

    for(int x = 0; x <16; x++)
    {
        for(int y = 0; y <16; y++)
        {
            if(mapacopy[x][y] == 3)
            {
                valores[x][y] = 255;
            }
        }
    }
    for(int i = 0 ; i <256; i++)
    {
        for(int x = 0; x <16; x++)
        {
            for(int y = 0; y <16; y++)
            {
                if(valores[x][y] >= 0)
                {
                    if(valores[x][y] > valores[x + 1][y] && mapacopy[x + 1][y] != 1)
                    {
                        valores[x + 1][y] = valores[x][y] -1;
                    }
                    if(valores[x][y] > valores[x - 1][y] && mapacopy[x - 1][y] != 1)
                    {
                        valores[x - 1][y] = valores[x][y] -1;
                    }
                    if(valores[x][y] > valores[x][y + 1] && mapacopy[x][y + 1] != 1)
                    {
                        valores[x][y + 1] = valores[x][y] -1;
                    }
                    if(valores[x][y] > valores[x][y - 1] && mapacopy[x][y - 1] != 1)
                    {
                        valores[x][y - 1] = valores[x][y] -1;
                    }
                }
            }
        }
    }

    for(int x = 16; x >0; x--)
        for(int y = 16; y >0; y--)
        {
            *val = valores[x-1][y];
            *val--;
        }
}

void setconsolecolor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor +
                            (bgColor * 16)));
}
// calcula o numero de passagens disponiveis na atual possiçao do 2 "player"
int intercecao (int *mapa)
{

    int intercecao = 0;
    int mapacopy[16][16];



    for(int x = 0; x <16; x++)
        for(int y = 0; y <16; y++)
        {
            mapacopy[x][y] = *mapa;
            *mapa++;
        }
    for(int x = 0; x <16; x++)
        for(int y = 0; y <16; y++)
            if(mapacopy[x][y] == 2)
            {
                if(mapacopy[x+1][y] != 1)intercecao ++;
                if(mapacopy[x][y+1] != 1)intercecao ++;
                if(mapacopy[x-1][y] != 1)intercecao ++;
                if(mapacopy[x][y-1] != 1)intercecao ++;
            }
    return intercecao;
}
// atualiza os valores de "visao" oq almenta o conhecimento do "player" sobre o mapa do labirinto
void ver( int *mapa, int *visao)
{

    int mapacopy[16][16];
    int visaocopy[16][16];
    int x = 1;

    for(int x = 0; x <16; x++)
    {
        for(int y = 0; y <16; y++)
        {
            mapacopy[x][y] = *mapa;
            *mapa++;
        }
    }
    for(int x = 0; x <16; x++)
    {
        for(int y = 0; y <16; y++)
        {
            visaocopy[x][y] = *visao;
            *visao++;
        }
    }
    for(int x = 0; x <16; x++)
    {
        for(int y = 0; y <16; y++)
        {
            if(mapacopy[x][y] == 2)
            {
                visaocopy[x-1][y] = mapacopy[x-1][y];
                visaocopy[x][y-1] = mapacopy[x][y-1];
                visaocopy[x+1][y] = mapacopy[x+1][y];
                visaocopy[x][y+1] = mapacopy[x][y+1];
                visaocopy[x][y] = mapacopy[x][y];
            }
        }
    }
    for(int x = 16; x >0; x--)
        for(int y = 16; y >0; y--)
        {
            *visao = visaocopy[x-1][y];
            *visao--;
        }
}
//calcula a melhor movimentação do "player" e execulta ela no mapa
int mover(int *mapa, int *val, int last)
{

    int mapacopy[16][16];
    int valores[16][16];

    for(int x = 0; x <16; x++)
        for(int y = 0; y <16; y++)
        {
            mapacopy[x][y] = *mapa;
            *mapa++;
        }
    for(int x = 0; x <16; x++)
        for(int y = 0; y <16; y++)
        {
            valores[x][y] = *val;
            *val++;
        }
    for(int x = 0; x <16; x++)
        for(int y = 0; y <16; y++)
            if(mapacopy[x][y] == 2)
            {
                printf("opcoes : %d \n", intercecao(&mapacopy[0][0]));
                printf("escolhida : ");

                if(valores[x][y] < valores[x-1][y] && (last != 3 || intercecao(&mapacopy[0][0]) == 1))
                {
                    mapacopy[x][y] = 5;
                    mapacopy[x-1][y] = 4;
                    last = 1;
                    printf("cima\n");
                }
                else if(valores[x][y] < valores[x][y-1] && (last != 4 || intercecao(&mapacopy[0][0]) == 1))
                {
                    mapacopy[x][y] = 5;
                    mapacopy[x][y-1] = 4;
                    last = 2;
                    printf("esquerda\n");
                }
                else if(valores[x][y] < valores[x+1][y] && (last != 1 || intercecao(&mapacopy[0][0]) == 1))
                {
                    mapacopy[x][y] = 5;
                    mapacopy[x+1][y] = 4;
                    last = 3;
                    printf("baixo\n");
                }
                else if(valores[x][y] < valores[x][y+1] && (last != 2 || intercecao(&mapacopy[0][0]) == 1))
                {
                    mapacopy[x][y] = 5;
                    mapacopy[x][y+1] = 4;
                    last = 4;
                    printf("direita\n");
                }
                else
                {

                    if(valores[x][y] < valores[x-1][y])
                    {
                        mapacopy[x][y] = 5;
                        mapacopy[x-1][y] = 4;
                        last = 1;
                        printf("cima\n");
                    }
                    else if(valores[x][y] < valores[x][y-1])
                    {
                        mapacopy[x][y] = 5;
                        mapacopy[x][y-1] = 4;
                        last = 2;
                        printf("esquerda\n");
                    }
                    else if(valores[x][y] < valores[x+1][y])
                    {
                        mapacopy[x][y] = 5;
                        mapacopy[x+1][y] = 4;
                        last = 3;
                        printf("baixo\n");
                    }
                    else if(valores[x][y] < valores[x][y+1])
                    {
                        mapacopy[x][y] = 5;
                        mapacopy[x][y+1] = 4;
                        last = 4;
                        printf("direita\n");
                    }
                }
            }

    for(int x = 0; x <16; x++)
        for(int y = 0; y <16; y++)
            if(mapacopy[x][y] == 4)
                mapacopy[x][y] = 2;

    for(int x = 16; x >0; x--)
        for(int y = 16; y >0; y--)
        {
            *mapa = mapacopy[x-1][y];
            *mapa--;
        }

    return last;
}
//usa uma serie de "printf" para dar uma ideia geral de como o labirindo é e como esta sendo visto pelo player
void render(int *mapa)
{

    for(int x = 0; x <16; x++)
    {
        for(int y = 0; y <16; y++)
        {
            if(*mapa == 0)
            {
                setconsolecolor(0,0);
                printf("  ");
            }
            else if(*mapa == 1)
            {
                setconsolecolor(0,4);
                printf("  ");
            }
            else if(*mapa == 2)
            {
                setconsolecolor(0,12);
                printf("  ");
            }
            else if(*mapa == 3)
            {
                setconsolecolor(0,10);
                printf("  ");
            }
            else
            {
                setconsolecolor(12,0);
                printf(",,");
            }
            *mapa ++;
        }
        setconsolecolor(15,0);
        printf("\n");
    }
}

main(void)
{

    int mapa[16][16]
    {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,2,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
        1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,
        1,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,
        1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,
        1,0,1,0,0,1,1,1,1,1,0,0,0,0,0,1,
        1,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,
        1,0,0,0,0,0,0,1,0,0,0,0,1,1,0,1,
        1,1,1,1,1,1,0,1,1,1,1,0,1,0,0,1,
        1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,
        1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1,
        1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,1,
        1,0,1,1,0,1,1,1,1,1,1,0,1,0,0,1,
        1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,1,
        1,0,0,0,1,0,0,0,1,0,1,0,1,0,3,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    int valores[16][16] = {0};
    int last = 0;
    int run;
    int time = 0;

    int visao[16][16] = {0};
    for(int x = 0; x <16; x++)
        for(int y = 0; y <16; y++)
        {
            if(mapa[x][y] == 3)
                visao[x][y] = 3;

            if(x == 0 || y == 0 || x ==15 || y ==15)
                visao[x][y] = 1;

        }

    render(&mapa[0][0]);
    render(&visao[0][0]);

    // Ciclo de repetição do jogo
    while(true)
    {

        ver(&mapa[0][0],&visao[0][0]);

        for(int x = 0; x <16; x++)
            for(int y = 0; y <16; y++)
                valores[x][y] = 0;

        calc(&visao[0][0],&valores[0][0]);

        last = mover(&mapa[0][0],&valores[0][0], last);

        render(&visao[0][0]);

        printf("\n");
        printf("step = %d\n", time);

        run = 1;
        for(int x = 0; x <16; x++)
            for(int y = 0; y <16; y++)
                if(mapa[x][y] == 3) run = 0;

        if(run)break;
        time ++;

    }
    printf("*****Finished*****");
}
