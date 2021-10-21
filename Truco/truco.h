#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tristto.h"
#define quatro 0
#define cinco 1
#define seis 2
#define sete 3
#define dama 4
#define valete 5
#define rei 6
#define as 7
#define dois 8
#define tres 9
#define ouro 0
#define espada 1
#define copas 2
#define paus 3
#define blefe 5
#define vida1 15000
#define vida2 20000

//estrutura da carta
typedef struct carta
{
    int naipe;
    int valor;
}carta;

//lista de cartas
typedef struct ListaCarta
{
    struct carta Cart;
    struct ListaCarta *proxima;
}ListaCarta;

//estrutura da pontuação
typedef struct placar
{
    int computador;
    int jogador;
    ///se o jogador ou o pc podem pedir truco
    int truco[2];
    ///usado nas mãos de onze
    int vez[3];
    ///é quanto vale a rodada, é o "vale"
    int pontuacao;
}placar;

int menu();
int normal();
int blind();
void delay(unsigned int mseconds);
ListaCarta *tirarcarta(ListaCarta **carta, int posicao);
int prejogo(ListaCarta **baralho,ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,placar *placar_jogo, int *turno);
int vez1(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez2(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez11(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez12(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez21(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez22(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez31(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez32(ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,int *truco);
int vez4(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira, placar *placar_partida, int *truco);
int lertecla();
int comparar_cartas(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira);
int sorteia_mao(ListaCarta **baralho, ListaCarta **mao_aleatoria, ListaCarta *computador);
int colocarCarta(ListaCarta ** carta , int valor , int naipe);
int tamanho(ListaCarta *carta);
int mostracarta(ListaCarta *carta , int posicao , int *valor , int *naipe);
int tirar3cartasale(ListaCarta **carta1, ListaCarta **carta2);
int iniciarmaos(ListaCarta **baralho , ListaCarta **jogador , ListaCarta **computador , ListaCarta **vira);
int voltarmaos(ListaCarta **baralho , ListaCarta **jogador , ListaCarta **computador , ListaCarta **vira);
int exibirmao(ListaCarta **jogador,int y, int x);
int exibirmao2(ListaCarta **jogador, int y, int x);
int rodada(placar *placar_partida, ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira);
int reiniciarmao(ListaCarta **cartas);
int PC_pensa(ListaCarta **computador, ListaCarta *vira);
int possibilidades(ListaCarta *carta, ListaCarta *vira);


