#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "truco.h"
#include "Tristto.h"

int menu()
{
	int seta = 36, teclado = 0;	
	while (1)
	{
		limpa_tela(PRETO);
		tprintf(50, 34, BRANCO, PRETO, "Escolha uma das opcoes");
		tprintf(50, 36, BRANCO, PRETO, "Truco Normal");
		tprintf(50, 38, BRANCO, PRETO, "Truco as Escuras");
		tprintf(50, 40, BRANCO, PRETO, "Sair");
		tprintf(70, seta, BRANCO, PRETO, "<--------");
		tprintf(30, seta, BRANCO, PRETO, "-------->");
		atualizaTela();
		teclado = tgetch();
		switch (teclado)
		{
		case CIMA:
			if (seta == 36) seta = 40;
			else seta = seta - 2;
			break;
		case BAIXO:
			if (seta == 40) seta = 36;
			else seta = seta + 2;
			break;
		case ENTER:
			if (seta == 36) normal();
			if (seta == 38) blind();
			if (seta == 40) exit(0);
			break;
		}
	}
	return 0;
}

int normal()
{
	limpa_tela(PRETO);
	atualizaTela();
    int vez1_1 = 1;
    int vez1_2 = 1;
    int vez1_3 = 1;
    ///variável que diz se o computador vai pedir truco, correr ou aceitar
    int truco = 0;
    int turno = rand() % 2;
    int pre_jogo = 1;
    ListaCarta *baralho = NULL;
	ListaCarta *jogador = NULL;
	ListaCarta *computador = NULL;
	ListaCarta *vira = NULL;
    placar placar_jogo;
    placar placar_partida;
    placar_jogo.jogador = 0;
    placar_jogo.computador = 0;
    placar_partida.jogador = 0;
    placar_partida.computador = 0;
    while(1)
    {
        ///inicia tudo antes de começar a partida
        if(pre_jogo == 1)
        {
            limpa_tela(PRETO);
            pre_jogo = prejogo(&baralho, &jogador, &computador, &vira, &placar_partida,&placar_jogo, &truco);
            limpa_tela(PRETO);
			atualizaTela();
        }
        else
        {
            ///mão de onze
            if(placar_jogo.jogador == 11 || placar_jogo.computador == 11)
            {
                ///mão de ferro
                if(placar_jogo.jogador == 11 && placar_jogo.computador == 11)
                {
                    if(turno == 1)
                        turno = vez31(&jogador, &computador, &vira, &placar_partida,&truco);
                    else
                        turno = vez32(&jogador, &computador, &vira, &placar_partida,&truco);
                }
                else
                {
                    ///se o jogador está com 11
                    if(placar_jogo.jogador == 11)
                    {
                        if(turno == 1)
                            turno = vez11(&jogador, &computador, &vira, &placar_partida,&truco);
                        else
                            turno = vez12(&jogador, &computador, &vira, &placar_partida,&truco);
                    }
                    ///se o computador está com 11
                    if(placar_jogo.computador == 11)
                    {
                        if(turno == 1)
                            turno = vez22(&jogador, &computador, &vira, &placar_partida,&truco);
                        else
                            turno = vez21(&jogador, &computador, &vira, &placar_partida,&truco);
                    }
                }
				atualizaTela();
            }
            ///se não é mão de onze
            else
            {
                ///vez do jogador
                if (turno == 1)
                {
                    turno = vez1(&jogador, &computador, &vira, &placar_partida,&truco);
                }
                ///vez do computador
                else
                {
                    turno = vez2(&jogador, &computador, &vira, &placar_partida,&truco);
                }
            }
            ///se o jogador ganhou, soma a pontuação da partida
            if(placar_partida.jogador > 1)
            {
                placar_jogo.jogador = placar_jogo.jogador + placar_partida.pontuacao;
                pre_jogo = 1;
            }
            ///se o computador ganhou, soma a pontuação da partida
            if(placar_partida.computador > 1)
            {
                placar_jogo.computador = placar_jogo.computador + placar_partida.pontuacao;
                pre_jogo = 1;
            }
            ///se o jogador ganhou
            if(placar_jogo.jogador >= 12)
            {
                limpa_tela(PRETO);
                tprintf(54,29,BRANCO,PRETO,"YOU WON");
				atualizaTela();
                lertecla();
				menu();
                return 0;
            }
            ///se o computador ganhou
            if(placar_jogo.computador >= 12)
            {
                limpa_tela(PRETO);
                tprintf(54,29,BRANCO,PRETO,"YOU LOSE");
				atualizaTela();
                lertecla();
				menu();
                return 0;
            }
        }
    }
}

///vez do jogador
int vez1(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{
    int teclado = 0,turno = 1,acao = 1;
    int empaxou = 0;
    ///a carta a colocar na mesa
    int escarta = 0;
    int posx = 10,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);

    ///fica no while enquanto nenhuma "acao" for tomada
    while(acao == 1)
    {
        tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
        exibirmao(vira,11,8);
        tprintf(10,8,BRANCO,PRETO,"VIRA:");
        tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
        if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
        exibirmao(jogador,10,14);
		atualizaTela();

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

        ///para cima
        if(teclado == 1)
        {
            if(posx>12) posx = posx - 2;
            else posx = 12 + (cartas*2);
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        ///para baixo
        if(teclado == 2)
        {
            if(posx<12 + (cartas*2)) posx = posx + 2;
            else posx = 12;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }

        ///apertou ENTER
        if(teclado == 5)
        {
            switch(posx)
            {
            ///pediu truco
            case 12:
                if(placar_partida->truco[0] == 1)
                {
                    ///computador aceitou o truco
                    if(*truco > 0)
                    {
                        *truco --;
                        placar_partida->truco[1] = 1;
                        placar_partida->truco[0] = 0;
                        if(placar_partida->pontuacao == 1) placar_partida->pontuacao = 3;
                        else placar_partida->pontuacao = placar_partida->pontuacao + 3;
                        limpa_tela(PRETO);
						atualizaTela();
                    }
                    ///computador correu
                    else
                    {
                        tprintf(10,14+(cartas*2),BRANCO,PRETO,"COMPUTADOR CORREU.....");
                        tprintf(10,16+(cartas*2),BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
						atualizaTela();
                        lertecla();
						atualizaTela();
                        placar_partida->jogador = placar_partida->jogador + 3;
						atualizaTela();
                        return 1;
                    }
                }
                break;
            case 14:
                acao = 0;
                escarta = 0;
                break;
            case 16:
                acao = 0;
                escarta = 1;
                break;
            case 18:
                acao = 0;
                escarta = 2;
                break;
            }
        }
		atualizaTela();
        teclado = 0;
    }
    mesa = tirarcarta(jogador,escarta);
    limpa_tela(PRETO);
	atualizaTela();
    tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,11,8);
    tprintf(10,8,BRANCO,PRETO,"VIRA:");
    tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,14);
	atualizaTela();
    int ran = rand() % blefe;
    if( ran == 1) *truco ++;
    if(*truco >= 1 && placar_partida->truco[1] == 1)
    {
        tprintf(10,14+(cartas*2),BRANCO,PRETO,"PC PEDIU TRUCO");
        tprintf(10,16+(cartas*2),BRANCO,PRETO,"APERTE SETA CIMA PARA ACEITAR E SETA BAIXO PARA CORRER");
		atualizaTela();
        while(teclado != 1 && teclado != 2) teclado = lertecla();
        switch (teclado)
        {
        ///jogador aceitou
        case 1:
            *truco --;
            placar_partida->truco[1] = 0;
            placar_partida->truco[0] = 1;
            if(placar_partida->pontuacao == 1) placar_partida->pontuacao = 3;
            else placar_partida->pontuacao = placar_partida->pontuacao + 3;
            break;
        ///jogador fugiu
        case 2:
            tprintf(10,16+(cartas*2),BRANCO,PRETO,"                                                       ");
            tprintf(10,14+(cartas*2),BRANCO,PRETO,"O COVARDE CORREU.....");
            tprintf(10,16+(cartas*2),BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
			atualizaTela();
            lertecla();
            placar_partida->computador = placar_partida->computador + 3;
			atualizaTela();
            return 0;
            break;
        }
    }
    mesa2 = tirarcarta(computador,0); /// pc tira a carta dele
    limpa_tela(PRETO);
	atualizaTela();
    tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,11,8);
    tprintf(10,8,BRANCO,PRETO,"VIRA:");
    tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,14);
	atualizaTela();
    turno = rodada(placar_partida,&mesa,&mesa2,vira); /// compara as cartas e retorna o vencedor ou se emmpaxou
    tprintf(10,14+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,14+(cartas*2));
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,16+(cartas*2));
	atualizaTela();

    if(turno == 2) /// se rodada retornar empaxado
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->computador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 0;
    }

    if(turno == 1) /// se rodada retornar com vitoria do jogador
    {
        placar_partida->jogador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 1;
    }

    if(turno == 0) /// se rodada retornar com vitoria do pc
    {
        placar_partida->computador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 0;
    }
}
///vez do computador
int vez2(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{

    int teclado = 0,turno = 1,acao = 1;
    int escarta = 0;
    int posx = 10,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);
	atualizaTela();
    mesa2 = tirarcarta(computador,0);
    tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,16,10);
    tprintf(10,10,BRANCO,PRETO,"VIRA:");
    tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,14,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,16);
	atualizaTela();

    int ran = rand() % blefe;
    if( ran == 1) *truco ++;

    ///computador pediu truco
    if(*truco >= 1 && placar_partida->truco[1] == 1)
    {
        tprintf(10,16+(cartas*2),BRANCO,PRETO,"PC PEDIU TRUCO");
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"APERTE SETA CIMA PARA ACEITAR E SETA BAIXO PARA CORRER");
		atualizaTela();
        while(teclado != 1 && teclado != 2) teclado = lertecla();
        switch (teclado)
        {
            ///o jogador aceitou
        case 1:
            *truco --;
            placar_partida->truco[1] = 0;
            placar_partida->truco[0] = 1;
            if(placar_partida->pontuacao == 1) placar_partida->pontuacao = 3;
            else placar_partida->pontuacao = placar_partida->pontuacao + 3;
            break;
            ///o jogador fugiu
        case 2:
            tprintf(10,18+(cartas*2),BRANCO,PRETO,"                                                       ");

            tprintf(10,16+(cartas*2),BRANCO,PRETO,"O COVARDE CORREU.....");
            tprintf(10,18+(cartas*2),BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
			atualizaTela();
            lertecla();
            placar_partida->computador = placar_partida->computador + 3;
            return 0;
            break;
        }
    }
    limpa_tela(PRETO);

    while(acao == 1)
    {
        tprintf(10,6,BRANCO,PRETO,"PC JOGOU:");
        exibirmao(&mesa2,19,6);
        tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
        exibirmao(vira,16,10);
        tprintf(10,10,BRANCO,PRETO,"VIRA:");
        tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
		atualizaTela();
        if (placar_partida->truco[0] == 1) tprintf(10,14,BRANCO,PRETO,"--- TRUCO");
        exibirmao(jogador,10,16);
		atualizaTela();

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();
        ///para cima
        if(teclado == 1)
        {
            if(posx>14) posx = posx - 2;
            else posx = 14 + (cartas*2);
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        ///para baixo
        if(teclado == 2)
        {
            if(posx<14 + (cartas*2)) posx = posx + 2;
            else posx = 14;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        ///apertou ENTER
        if(teclado == 5)
        {
            switch(posx)
            {
                ///o jogador pediu truco
            case 14:
                if(placar_partida->truco[0] == 1)
                {
                    ///o computador pediu truco
                    if(*truco > 0)
                    {
                        *truco --;
                        placar_partida->truco[1] = 1;
                        placar_partida->truco[0] = 0;
                        if(placar_partida->pontuacao == 1) placar_partida->pontuacao = 3;
                        else placar_partida->pontuacao = placar_partida->pontuacao + 3;
                        limpa_tela(PRETO);
						atualizaTela();
                    }
                    ///o computador fugiu
                    else
                    {
                        tprintf(10,16+(cartas*2),BRANCO,PRETO,"COMPUTADOR CORREU.....");
                        tprintf(10,18+(cartas*2),BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
						atualizaTela();
                        lertecla();
                        placar_partida->jogador = placar_partida->jogador + 3;
                        return 1;
                    }
                }
                break;
                ///o jogador joga as cartas
            case 16:
                acao = 0;
                escarta = 0;
                break;
            case 18:
                acao = 0;
                escarta = 1;
                break;
            case 20:
                acao = 0;
                escarta = 2;
                break;
            }
        }
        teclado = 0;
    }
    mesa = tirarcarta(jogador, escarta);
    turno = rodada(placar_partida,&mesa,&mesa2,vira);
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,16+(cartas*2));
    tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,18+(cartas*2));
	atualizaTela();

    ///empatou
    if(turno == 2)
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->jogador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 1;
    }

    ///o jogador venceu
    if(turno == 1)
    {

        placar_partida->jogador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 1;
    }

    ///o computador venceu
    else
    {
        placar_partida->computador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 0;
    }
}
///mão de onze do jogador e o jogador começa
int vez11(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{
    int teclado = 0,turno = 1,acao = 1;
    int escarta = 0;
    int posx = 10,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);
    if(placar_partida->vez[0] == 1)
    {
        placar_partida->vez[0] = 0;
        exibirmao(vira,11,8);
        tprintf(10,8,BRANCO,PRETO,"VIRA:");
        tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
        exibirmao(jogador,10,12);
        tprintf(10,18,BRANCO,PRETO,"DESEJA CONTINUAR?");
        tprintf(10,20,BRANCO,PRETO,"APERTE SETA CIMA PARA ACEITAR E SETA BAIXO PARA CORRER");
        while(teclado != 1 && teclado != 2) teclado = lertecla();
        if(teclado == 1)
            placar_partida->pontuacao = 3;
        if(teclado == 2)
        {
            tprintf(10,20+(cartas*2),BRANCO,PRETO,"                                                       ");
            tprintf(10,18+(cartas*2),BRANCO,PRETO,"O COVARDE CORREU.....");
            tprintf(10,20+(cartas*2),BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
            lertecla();
            placar_partida->computador = placar_partida->computador + 3;
            return 0;
        }
    }
    while(acao == 1)
    {
        tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
        exibirmao(vira,11,8);
        tprintf(10,8,BRANCO,PRETO,"VIRA:");
        tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
		atualizaTela();
        if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
        exibirmao(jogador,10,14);

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

        if(teclado == 1)
        {
            if(posx>12) posx = posx - 2;
            else posx = 12 + (cartas*2);
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 2)
        {
            if(posx<12 + (cartas*2)) posx = posx + 2;
            else posx = 12;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 5)
        {
            switch(posx)
            {
            case 12:
                tprintf(10,14+(cartas*2),BRANCO,PRETO,"MAS NUM PODE");
				atualizaTela();
                placar_partida->computador += 5;
                return 0;
                break;
            case 14:
                acao = 0;
                escarta = 0;
                break;
            case 16:
                acao = 0;
                escarta = 1;
                break;
            case 18:
                acao = 0;
                escarta = 2;
                break;
            }
        }
        teclado = 0;
    }
    mesa = tirarcarta(jogador,escarta);
    limpa_tela(PRETO);
    tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,11,8);
    tprintf(10,8,BRANCO,PRETO,"VIRA:");
    tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
	exibirmao(jogador, 10, 14);
	atualizaTela();
    mesa2 = tirarcarta(computador,0);
    limpa_tela(PRETO);
    tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,11,8);
    tprintf(10,8,BRANCO,PRETO,"VIRA:");
    tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,14);
	atualizaTela();
    turno = rodada(placar_partida,&mesa,&mesa2,vira);
    tprintf(10,14+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,14+(cartas*2));
	atualizaTela();
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,16+(cartas*2));
	atualizaTela();

    if(turno == 2)
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->computador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 0;
    }

    if(turno == 1)
    {
        placar_partida->jogador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        free(mesa);
        free(mesa2);
        return 1;
    }
    else
    {
        placar_partida->computador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        free(mesa);
        free(mesa2);
        return 0;
    }
}
///mão de onze do jogador e o computador começa
int vez12(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{
    int teclado = 0,turno = 1,acao = 1;
    int escarta = 0;
    placar_partida->truco[0]=0;
    placar_partida->truco[1]=0;
    int posx = 14,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);
    if(placar_partida->vez[0] == 1)
    {
        placar_partida->vez[0] = 0;
        exibirmao(vira,11,8);
        tprintf(10,8,BRANCO,PRETO,"VIRA:");
        tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
        exibirmao(jogador,10,12);
        tprintf(10,18,BRANCO,PRETO,"DESEJA CONTINUAR?");
        tprintf(10,20,BRANCO,PRETO,"APERTE SETA CIMA PARA ACEITAR E SETA BAIXO PARA CORRER");
		atualizaTela();
        while(teclado != 1 && teclado != 2) teclado = lertecla();
        if(teclado == 1)
            placar_partida->pontuacao = 3;
        if(teclado == 2)
        {
            tprintf(10,20+(cartas*2),BRANCO,PRETO,"                                                       ");
            tprintf(10,18+(cartas*2),BRANCO,PRETO,"O COVARDE CORREU.....");
            tprintf(10,20+(cartas*2),BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
            lertecla();
            placar_partida->computador = placar_partida->computador + 3;
            return 0;
        }
    }
    mesa2 = tirarcarta(computador,0);
    tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,16,10);
    tprintf(10,10,BRANCO,PRETO,"VIRA:");
    tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,14,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,16);
	atualizaTela();
    limpa_tela(PRETO);

    while(acao == 1)
    {
        tprintf(10,6,BRANCO,PRETO,"PC JOGOU:");
        exibirmao(&mesa2,19,6);
        tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
        exibirmao(vira,16,10);
        tprintf(10,10,BRANCO,PRETO,"VIRA:");
        tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
        exibirmao(jogador,10,14);
		atualizaTela();

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

        if(teclado == 1)
        {
            if(posx>14) posx = posx - 2;
            else posx = 14 + (cartas*2)- 2;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 2)
        {
            if(posx<14 + (cartas*2)- 2) posx = posx + 2;
            else posx = 14;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 5)
        {
            switch(posx)
            {
                break;
            case 14:
                acao = 0;
                escarta = 0;
                break;
            case 16:
                acao = 0;
                escarta = 1;
                break;
            case 18:
                acao = 0;
                escarta = 2;
                break;
            }
        }
        teclado = 0;
    }
    mesa = tirarcarta(jogador, escarta);
    turno = rodada(placar_partida,&mesa,&mesa2,vira);
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,16+(cartas*2));
	atualizaTela();
    tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,18+(cartas*2));
	atualizaTela();

    if(turno == 2)
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->jogador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 1;
    }

    if(turno == 1)
    {

        placar_partida->jogador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 1;
    }
    else
    {
        placar_partida->computador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 0;
    }
}
///mão de onze do computador e o computador começa
int vez21(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{
    int teclado = 0,turno = 1,acao = 1;
    int escarta = 0;
    placar_partida->truco[0]=0;
    placar_partida->truco[1]=0;
    int posx = 14,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);
    if(placar_partida->vez[1] == 1)
    {
        placar_partida->vez[1] = 0;
        if(*truco > 0)
        {
            placar_partida->pontuacao = 3;
        }
        else
        {
            tprintf(10,10,BRANCO,PRETO,"O COVARDE CORREU.....");
            tprintf(10,12,BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
			atualizaTela();
            lertecla();
            placar_partida->jogador = placar_partida->jogador + 3;
            return 0;
        }
    }
    mesa2 = tirarcarta(computador,0);
    tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,16,10);
    tprintf(10,10,BRANCO,PRETO,"VIRA:");
    tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,14,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,16);
	atualizaTela();
    limpa_tela(PRETO);

    while(acao == 1)
    {
        tprintf(10,6,BRANCO,PRETO,"PC JOGOU:");
        exibirmao(&mesa2,19,6);
        tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
        exibirmao(vira,16,10);
        tprintf(10,10,BRANCO,PRETO,"VIRA:");
        tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
        exibirmao(jogador,10,14);
		atualizaTela();

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

        if(teclado == 1)
        {
            if(posx>14) posx = posx - 2;
            else posx = 14 + (cartas*2)- 2;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 2)
        {
            if(posx<14 + (cartas*2)- 2) posx = posx + 2;
            else posx = 14;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 5)
        {
            switch(posx)
            {
                break;
            case 14:
                acao = 0;
                escarta = 0;
                break;
            case 16:
                acao = 0;
                escarta = 1;
                break;
            case 18:
                acao = 0;
                escarta = 2;
                break;
            }
        }
        teclado = 0;
    }
    mesa = tirarcarta(jogador, escarta);
    turno = rodada(placar_partida,&mesa,&mesa2,vira);
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,16+(cartas*2));
	atualizaTela();
    tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,18+(cartas*2));
	atualizaTela();
    if(turno == 2)
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->jogador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 1;
    }

    if(turno == 1)
    {

        placar_partida->jogador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 1;
    }
    else
    {
        placar_partida->computador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 0;
    }
}
///mão de onze do computador e o jogador começa
int vez22(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{
    int teclado = 0,turno = 1,acao = 1;
    int escarta = 0;
    int posx = 10,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);
    if(placar_partida->vez[1] == 1)
    {
        placar_partida->vez[1] = 0;
        if(*truco > 0)
        {
            placar_partida->pontuacao = 3;
        }
        else
        {
            tprintf(10,10,BRANCO,PRETO,"O COVARDE CORREU.....");
            tprintf(10,12,BRANCO,PRETO,"APERTE ENTER PARA CONTINUAR");
			atualizaTela();
            lertecla();
            placar_partida->jogador = placar_partida->jogador + 3;
            return 0;
        }
    }
    while(acao == 1)
    {
        tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
        exibirmao(vira,11,8);
        tprintf(10,8,BRANCO,PRETO,"VIRA:");
        tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
		atualizaTela();
        if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
        exibirmao(jogador,10,14);
		atualizaTela();

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

        if(teclado == 1)
        {
            if(posx>12) posx = posx - 2;
            else posx = 12 + (cartas*2);
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 2)
        {
            if(posx<12 + (cartas*2)) posx = posx + 2;
            else posx = 12;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 5)
        {
            switch(posx)
            {
            case 12:
                tprintf(10,14+(cartas*2),BRANCO,PRETO,"MAS NUM PODE");
				atualizaTela();
                placar_partida->computador += 5;
                return 0;
                break;
            case 14:
                acao = 0;
                escarta = 0;
                break;
            case 16:
                acao = 0;
                escarta = 1;
                break;
            case 18:
                acao = 0;
                escarta = 2;
                break;
            }
        }
        teclado = 0;
    }
    mesa = tirarcarta(jogador,escarta);
    limpa_tela(PRETO);
    tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,11,8);
    tprintf(10,8,BRANCO,PRETO,"VIRA:");
    tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,14);
	atualizaTela();
    mesa2 = tirarcarta(computador,0);
    limpa_tela(PRETO);
    tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,11,8);
    tprintf(10,8,BRANCO,PRETO,"VIRA:");
    tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
	atualizaTela();
    if (placar_partida->truco[0] == 1) tprintf(10,12,BRANCO,PRETO,"--- TRUCO");
    exibirmao(jogador,10,14);
	atualizaTela();
    turno = rodada(placar_partida,&mesa,&mesa2,vira);
    tprintf(10,14+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,14+(cartas*2));
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,16+(cartas*2));
	atualizaTela();

    if(turno == 2)
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->computador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 0;
    }

    if(turno == 1)
    {
        placar_partida->jogador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        free(mesa);
        free(mesa2);
        return 1;
    }
    else
    {
        placar_partida->computador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        free(mesa);
        free(mesa2);
        return 0;
    }
}
///mão de onze dos dois e o jogador começa
int vez31(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{
    int teclado = 0,turno = 1,acao = 1;
    int escarta = 0;
    int posx = 10,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);

    while(acao == 1)
    {
        if(placar_partida->vez[2]== 1)
        {
            exibirmao2(vira,11,8);
        }
        else
            exibirmao(vira,11,8);

        tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
        tprintf(10,8,BRANCO,PRETO,"VIRA:");
        tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
        exibirmao2(jogador,10,12);
		atualizaTela();

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

        if(teclado == 1)
        {
            if(posx>12) posx = posx - 2;
            else posx = 12 + (cartas*2) -2;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 2)
        {
            if(posx<12 + (cartas*2)-2) posx = posx + 2;
            else posx = 12;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 5)
        {
            switch(posx)
            {
            case 12:
                acao = 0;
                escarta = 0;
                break;
            case 14:
                acao = 0;
                escarta = 1;
                break;
            case 16:
                acao = 0;
                escarta = 2;
                break;
            }
        }
        teclado = 0;
    }
    placar_partida->vez[2]= 0 ;
    mesa = tirarcarta(jogador,escarta);
    limpa_tela(PRETO);
    tprintf(10,6,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
    exibirmao(vira,11,8);
    tprintf(10,8,BRANCO,PRETO,"VIRA:");
    tprintf(10,10,BRANCO,PRETO,"--- SUA MAO!!");
    exibirmao2(jogador,10,14);
    turno = rodada(placar_partida,&mesa,&mesa2,vira);
    tprintf(10,14+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,14+(cartas*2));
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,16+(cartas*2));
	atualizaTela();

    if(turno == 2)
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->computador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 0;
    }

    if(turno == 1)
    {
        placar_partida->jogador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 1;
    }
    else
    {
        placar_partida->computador++;
        tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 0;
    }
}
///mão de onze dos dois e o computador começa
int vez32(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira,placar *placar_partida,int *truco)
{
    int teclado = 0,turno = 1,acao = 1;
    int escarta = 0;
    int posx = 10,cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
    limpa_tela(PRETO);
	atualizaTela();

    mesa2 = tirarcarta(computador,rand()%cartas);
	atualizaTela();

    tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
	atualizaTela();
    if(placar_partida->vez[2]== 1)
    {
        exibirmao2(vira,11,8);
    }
    else
        exibirmao(vira,11,8);
    tprintf(10,10,BRANCO,PRETO,"VIRA:");
    tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
    exibirmao2(jogador,10,16);
    limpa_tela(PRETO);
	atualizaTela();

    while(acao == 1)
    {
        tprintf(10,6,BRANCO,PRETO,"PC JOGOU:");
        exibirmao2(&mesa2,19,6);
        tprintf(10,8,BRANCO,PRETO,"--- VALENDO :%d pontos",placar_partida->pontuacao);
		atualizaTela();
        if(placar_partida->vez[2]== 1)
        {
			exibirmao2(vira,11,10);//aqui
        }
        else
			exibirmao2(vira,11,10);//aqui
        tprintf(10,10,BRANCO,PRETO,"VIRA:");
        tprintf(10,12,BRANCO,PRETO,"--- SUA MAO!!");
        exibirmao2(jogador,10,14);
		atualizaTela();

        while(teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

        if(teclado == 1)
        {
            if(posx>14) posx = posx - 2;
            else posx = 14 + (cartas*2) -2;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 2)
        {
            if(posx<14 + (cartas*2)-2) posx = posx + 2;
            else posx = 14;
            limpa_tela(PRETO);
            tprintf(26,posx,BRANCO,PRETO,"<--");
			atualizaTela();
        }
        if(teclado == 5)
        {
            switch(posx)
            {
            case 14:
                acao = 0;
                escarta = 0;
                break;
            case 16:
                acao = 0;
                escarta = 1;
                break;
            case 18:
                acao = 0;
                escarta = 2;
                break;
            }
        }
        teclado = 0;
    }
    placar_partida->vez[2] = 0;
    mesa = tirarcarta(jogador, escarta);
    turno = rodada(placar_partida,&mesa,&mesa2,vira);
    tprintf(10,16+(cartas*2),BRANCO,PRETO,"VC JOGOU:");
    exibirmao(&mesa,19,16+(cartas*2));
    tprintf(10,18+(cartas*2),BRANCO,PRETO,"PC JOGOU:");
    exibirmao(&mesa2,19,18+(cartas*2));
	atualizaTela();

    if(turno == 2)
    {
        if(placar_partida->computador == 1 && placar_partida->jogador == 1)
        {
            placar_partida->jogador++;
        }
        else
        {
            placar_partida->computador++;
            placar_partida->jogador++;
        }
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"EMPAXOU");
		atualizaTela();
        lertecla();
        return 1;
    }


    if(turno == 1)
    {

        placar_partida->jogador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"VC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 1;
    }
    else
    {
        placar_partida->computador++;
        tprintf(10,20+(cartas*2),BRANCO,PRETO,"PC VENCEU");
        tprintf(10,22+(cartas*2),BRANCO,PRETO,"VC :%d",placar_partida->jogador);
        tprintf(10,24+(cartas*2),BRANCO,PRETO,"PC :%d",placar_partida->computador);
		atualizaTela();
        lertecla();
        return 0;
    }
}

///truco as escuras
int vez4(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira, placar *placar_partida, int *truco)
{
	int teclado = 0, turno = 1, acao = 1;
	int empaxou = 0;
	///a carta a colocar na mesa
	int escarta = 0;
	int posx = 10, cartas = tamanho(*jogador);
	ListaCarta *mesa = NULL;
	ListaCarta *mesa2 = NULL;
	limpa_tela(PRETO);

	///fica no while enquanto nenhuma "acao" for tomada
	while (acao == 1)
	{
		tprintf(10, 6, BRANCO, PRETO, "--- VALENDO :%d pontos", placar_partida->pontuacao);
		exibirmao(vira, 11, 8);
		tprintf(10, 8, BRANCO, PRETO, "VIRA:");
		tprintf(10, 10, BRANCO, PRETO, "--- SUA MAO!!");
		if (placar_partida->truco[0] == 1) tprintf(10, 12, BRANCO, PRETO, "--- TRUCO");
		exibirmao2(jogador, 10, 14);
		atualizaTela();

		while (teclado != 1 && teclado != 2 && teclado != 5) teclado = lertecla();

		///para cima
		if (teclado == 1)
		{
			if (posx > 12) posx = posx - 2;
			else posx = 12 + (cartas * 2);
			limpa_tela(PRETO);
			tprintf(26, posx, BRANCO, PRETO, "<--");
			atualizaTela();
		}
		///para baixo
		if (teclado == 2)
		{
			if (posx < 12 + (cartas * 2)) posx = posx + 2;
			else posx = 12;
			limpa_tela(PRETO);
			tprintf(26, posx, BRANCO, PRETO, "<--");
			atualizaTela();
		}

		///apertou ENTER
		if (teclado == 5)
		{
			switch (posx)
			{
				///pediu truco
			case 12:
				if (placar_partida->truco[0] == 1)
				{
					///computador aceitou o truco
					if (*truco > 0)
					{
						*truco--;
						placar_partida->truco[1] = 1;
						placar_partida->truco[0] = 0;
						if (placar_partida->pontuacao == 1) placar_partida->pontuacao = 3;
						else placar_partida->pontuacao = placar_partida->pontuacao + 3;
						limpa_tela(PRETO);
						atualizaTela();
					}
					///computador correu
					else
					{
						tprintf(10, 14 + (cartas * 2), BRANCO, PRETO, "COMPUTADOR CORREU.....");
						tprintf(10, 16 + (cartas * 2), BRANCO, PRETO, "APERTE ENTER PARA CONTINUAR");
						atualizaTela();
						lertecla();
						atualizaTela();
						placar_partida->jogador = placar_partida->jogador + 3;
						atualizaTela();
						return 1;
					}
				}
				break;
			case 14:
				acao = 0;
				escarta = 0;
				break;
			case 16:
				acao = 0;
				escarta = 1;
				break;
			case 18:
				acao = 0;
				escarta = 2;
				break;
			}
		}
		atualizaTela();
		teclado = 0;
	}
	mesa = tirarcarta(jogador, escarta);
	limpa_tela(PRETO);
	atualizaTela();
	tprintf(10, 6, BRANCO, PRETO, "--- VALENDO :%d pontos", placar_partida->pontuacao);
	exibirmao(vira, 11, 8);
	tprintf(10, 8, BRANCO, PRETO, "VIRA:");
	tprintf(10, 10, BRANCO, PRETO, "--- SUA MAO!!");
	atualizaTela();
	if (placar_partida->truco[0] == 1) tprintf(10, 12, BRANCO, PRETO, "--- TRUCO");
	exibirmao2(jogador, 10, 14);
	atualizaTela();
	int ran = rand() % blefe;
	if (ran == 1) *truco++;
	if (*truco >= 1 && placar_partida->truco[1] == 1)
	{
		tprintf(10, 14 + (cartas * 2), BRANCO, PRETO, "PC PEDIU TRUCO");
		tprintf(10, 16 + (cartas * 2), BRANCO, PRETO, "APERTE SETA CIMA PARA ACEITAR E SETA BAIXO PARA CORRER");
		atualizaTela();
		while (teclado != 1 && teclado != 2) teclado = lertecla();
		switch (teclado)
		{
			///jogador aceitou
		case 1:
			*truco--;
			placar_partida->truco[1] = 0;
			placar_partida->truco[0] = 1;
			if (placar_partida->pontuacao == 1) placar_partida->pontuacao = 3;
			else placar_partida->pontuacao = placar_partida->pontuacao + 3;
			break;
			///jogador fugiu
		case 2:
			tprintf(10, 16 + (cartas * 2), BRANCO, PRETO, "                                                       ");
			tprintf(10, 14 + (cartas * 2), BRANCO, PRETO, "O COVARDE CORREU.....");
			tprintf(10, 16 + (cartas * 2), BRANCO, PRETO, "APERTE ENTER PARA CONTINUAR");
			atualizaTela();
			lertecla();
			placar_partida->computador = placar_partida->computador + 3;
			atualizaTela();
			return 0;
			break;
		}
	}
	mesa2 = tirarcarta(computador, 0); /// pc tira a carta dele
	limpa_tela(PRETO);
	atualizaTela();
	tprintf(10, 6, BRANCO, PRETO, "--- VALENDO :%d pontos", placar_partida->pontuacao);
	exibirmao(vira, 11, 8);
	tprintf(10, 8, BRANCO, PRETO, "VIRA:");
	tprintf(10, 10, BRANCO, PRETO, "--- SUA MAO!!");
	atualizaTela();
	if (placar_partida->truco[0] == 1) tprintf(10, 12, BRANCO, PRETO, "--- TRUCO");
	exibirmao2(jogador, 10, 14);
	atualizaTela();
	turno = rodada(placar_partida, &mesa, &mesa2, vira); /// compara as cartas e retorna o vencedor ou se emmpaxou
	tprintf(10, 14 + (cartas * 2), BRANCO, PRETO, "VC JOGOU:");
	exibirmao(&mesa, 19, 14 + (cartas * 2));
	tprintf(10, 16 + (cartas * 2), BRANCO, PRETO, "PC JOGOU:");
	exibirmao(&mesa2, 19, 16 + (cartas * 2));
	atualizaTela();

	if (turno == 2) /// se rodada retornar empaxado
	{
		if (placar_partida->computador == 1 && placar_partida->jogador == 1)
		{
			placar_partida->computador++;
		}
		else
		{
			placar_partida->computador++;
			placar_partida->jogador++;
		}
		tprintf(10, 18 + (cartas * 2), BRANCO, PRETO, "EMPAXOU");
		atualizaTela();
		lertecla();
		return 0;
	}

	if (turno == 1) /// se rodada retornar com vitoria do jogador
	{
		placar_partida->jogador++;
		tprintf(10, 18 + (cartas * 2), BRANCO, PRETO, "VC VENCEU");
		tprintf(10, 20 + (cartas * 2), BRANCO, PRETO, "VC :%d", placar_partida->jogador);
		tprintf(10, 22 + (cartas * 2), BRANCO, PRETO, "PC :%d", placar_partida->computador);
		atualizaTela();
		lertecla();
		return 1;
	}

	if (turno == 0) /// se rodada retornar com vitoria do pc
	{
		placar_partida->computador++;
		tprintf(10, 18 + (cartas * 2), BRANCO, PRETO, "PC VENCEU");
		tprintf(10, 20 + (cartas * 2), BRANCO, PRETO, "VC :%d", placar_partida->jogador);
		tprintf(10, 22 + (cartas * 2), BRANCO, PRETO, "PC :%d", placar_partida->computador);
		atualizaTela();
		lertecla();
		return 0;
	}
}
///truco as cegas
int blind()
{
	limpa_tela(PRETO);
	atualizaTela();
	int vez1_1 = 1;
	int vez1_2 = 1;
	int vez1_3 = 1;
	///variável que diz se o computador vai pedir truco, correr ou aceitar
	int truco = 0;
	int turno = rand() % 2;
	int pre_jogo = 1;
	ListaCarta *baralho = NULL;
	ListaCarta *jogador = NULL;
	ListaCarta *computador = NULL;
	ListaCarta *vira = NULL;
	placar placar_jogo;
	placar placar_partida;
	placar_jogo.jogador = 0;
	placar_jogo.computador = 0;
	placar_partida.jogador = 0;
	placar_partida.computador = 0;
	while (1)
	{
		///inicia tudo antes de começar a partida
		if (pre_jogo == 1)
		{
			limpa_tela(PRETO);
			pre_jogo = prejogo(&baralho, &jogador, &computador, &vira, &placar_partida, &placar_jogo, &truco);
			limpa_tela(PRETO);
			atualizaTela();
		}
		else
		{
			///mão de onze
			if (placar_jogo.jogador == 11 || placar_jogo.computador == 11)
			{
				///mão de ferro
				if (placar_jogo.jogador == 11 && placar_jogo.computador == 11)
				{
					if (turno == 1)
						turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
					else
						turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
				}
				else
				{
					///se o jogador está com 11
					if (placar_jogo.jogador == 11)
					{
						if (turno == 1)
							turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
						else
							turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
					}
					///se o computador está com 11
					if (placar_jogo.computador == 11)
					{
						if (turno == 1)
							turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
						else
							turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
					}
				}
				atualizaTela();
			}
			///se não é mão de onze
			else
			{
				///vez do jogador
				if (turno == 1)
				{
					turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
				}
				///vez do computador
				else
				{
					turno = vez4(&jogador, &computador, &vira, &placar_partida, &truco);
				}
			}
			///se o jogador ganhou, soma a pontuação da partida
			if (placar_partida.jogador > 1)
			{
				placar_jogo.jogador = placar_jogo.jogador + placar_partida.pontuacao;
				pre_jogo = 1;
			}
			///se o computador ganhou, soma a pontuação da partida
			if (placar_partida.computador > 1)
			{
				placar_jogo.computador = placar_jogo.computador + placar_partida.pontuacao;
				pre_jogo = 1;
			}
			///se o jogador ganhou
			if (placar_jogo.jogador >= 12)
			{
				limpa_tela(PRETO);
				tprintf(54, 29, BRANCO, PRETO, "YOU WON");
				atualizaTela();
				lertecla();
				menu();
				return 0;
			}
			///se o computador ganhou
			if (placar_jogo.computador >= 12)
			{
				limpa_tela(PRETO);
				tprintf(54, 29, BRANCO, PRETO, "YOU LOSE");
				atualizaTela();
				lertecla();
				menu();
				return 0;
			}
		}
	}
}

int prejogo(ListaCarta **baralho,ListaCarta **jogador,ListaCarta **computador,ListaCarta **vira,placar *placar_partida,placar *placar_jogo, int *truco)
{
    reiniciarmao(jogador);
    reiniciarmao(computador);
    reiniciarmao(vira);
    reiniciarmao(baralho);
    iniciarBaralho(baralho);
    iniciarmaos(baralho,jogador,computador,vira);
    *truco = PC_pensa(computador,*vira);
    placar_partida->computador = 0;
    placar_partida->jogador = 0;
    placar_partida->pontuacao = 1;
    placar_partida->vez[0] = 1;
    placar_partida->vez[1] = 1;
    placar_partida->vez[2] = 1;
    placar_partida->truco[0] = 1;
    placar_partida->truco[1] = 1;
    tprintf(50,22,BRANCO,PRETO,"SUA PONTUACAO: %d",placar_jogo->jogador);
    tprintf(50,24,BRANCO,PRETO,"PC  PONTUACAO: %d",placar_jogo->computador);
    tprintf(50,26,BRANCO,PRETO,"LOADING........");
	atualizaTela();
	delay(1500);
    return 0;
}

///reinicia a mão
int reiniciarmao(ListaCarta **cartas)
{
    while(tamanho(*cartas)>0)
    {
        tirarcarta(cartas,0);
    }
    return 0;
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int lertecla()
{
    while(1)
    {
        if(lerTecla(CIMA))
        {
            delay(250);
            return 1;
        }

        if(lerTecla(BAIXO))
        {
            delay(250);
            return 2;
        }

        if(lerTecla(ENTER))
        {
            delay(250);
            return 5;
        }
    }
}

int exibirmao(ListaCarta **jogador,int y, int x)
{
    if(*jogador== NULL) return -1;
    int i,z,j;
    for (z=0; z<tamanho(*jogador); z++)
    {
        mostracarta(*jogador,z,&i,&j);
        tprintf(y,((z*2)+x),BRANCO,PRETO,"--- ");
        switch (i)
        {
        case 0:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"QUATRO DE");
            break;

        case 1:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"CINCO  DE");
            break;

        case 2:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"SEIS   DE");
            break;

        case 3:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"SETE   DE");
            break;

        case 4:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"DAMA   DE");
            break;

        case 5:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"VALETE DE");
            break;

        case 6:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"REI    DE");
            break;

        case 7:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"AS     DE");
            break;

        case 8:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"DOIS   DE");
            break;

        case 9:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"TRES   DE");
            break;
        }
        switch (j)
        {
        case 0:
            tprintf(y+14,((z*2)+x),VERMELHO_CLARO,PRETO,"\4");
            break;

        case 1:
            tprintf(y+14,((z*2)+x),BRANCO,PRETO,"\6");
            break;

        case 2:
            tprintf(y+14,((z*2)+x),VERMELHO_CLARO,PRETO,"\3");
            break;

        case 3:
            tprintf(y+14,((z*2)+x),BRANCO,PRETO,"\5");
            break;
        }
    }
    return 0;
}

int exibirmao2(ListaCarta **jogador,int y, int x)
{
    if(*jogador== NULL) return -1;
    int i,z,j;
    for (z=0; z<tamanho(*jogador); z++)
    {
        mostracarta(*jogador,z,&i,&j);
        tprintf(y,((z*2)+x),BRANCO,PRETO,"--- ");
        switch (i)
        {
        case 0:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 1:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 2:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 3:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 4:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 5:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 6:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 7:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 8:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;

        case 9:
            tprintf(y+4,((z*2)+x),BRANCO,PRETO,"XXXXXXXXX");
            break;
        }
        switch (j)
        {
        case 0:
            tprintf(y+14,((z*2)+x),BRANCO,PRETO,"X");
            break;

        case 1:
            tprintf(y+14,((z*2)+x),BRANCO,PRETO,"X");
            break;

        case 2:
            tprintf(y+14,((z*2)+x),BRANCO,PRETO,"X");
            break;

        case 3:
            tprintf(y+14,((z*2)+x),BRANCO,PRETO,"X");
            break;
        }
    }
    return 0;
}

///inicia as mãos 
int iniciarmaos(ListaCarta **baralho, ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira)
{
    ListaCarta *aux = NULL;
    reiniciarmao(jogador);
    reiniciarmao(computador);
    reiniciarmao(vira);
    tirar3cartasale(baralho, jogador);
    tirar3cartasale(baralho, computador);
    aux = tirarcarta(baralho, rand()%tamanho(*baralho));
    colocarCarta(vira,aux->Cart.valor,aux->Cart.naipe);
    return 0;
}

///pega 3 cartas aleatórias
int tirar3cartasale(ListaCarta **carta1, ListaCarta **carta2)
{
    if(*carta1 == NULL ||*carta1 == NULL && *carta2 == NULL) return -1;
    ListaCarta *aux = NULL;
    int i;
    for(i=0; i<3; i++)
    {
        aux = tirarcarta(carta1, rand()%tamanho(*carta1));
        colocarCarta(carta2,aux->Cart.valor,aux->Cart.naipe);
        free(aux);
    }
    return 0;
}


ListaCarta *tirarcarta(ListaCarta **carta, int posicao)
{
    int i;
    if(*carta == NULL) return NULL;
    if (posicao == 0)
    {
        ListaCarta *temp = *carta;
        *carta = (*carta)->proxima;
        temp->proxima = NULL;
        return temp;
    }
    if(posicao>0&&posicao<tamanho(*carta))
    {
        ListaCarta *and = *carta;
        for(i=0; i<posicao-1; i++) and = and->proxima;
        ListaCarta *temp = and->proxima;
        if((and->proxima)->proxima == NULL) and->proxima = NULL;
        else and->proxima = (and->proxima)->proxima;
        temp->proxima = NULL;
        return temp;
    }
    else return NULL;
}

///cria uma carta
int colocarCarta(ListaCarta ** carta, int valor, int naipe)
{
    if(*carta==NULL)
    {
        ListaCarta *nov = malloc(sizeof(ListaCarta));
        nov->Cart.valor = valor;
        nov->Cart.naipe = naipe;
        nov->proxima = NULL;
        *carta=nov;
        return 0;
    }
    ListaCarta *and = *carta;
    while(and->proxima!= NULL)
    {
        and=and->proxima;
    }
    ListaCarta *nov = malloc(sizeof(ListaCarta));
    nov->Cart.valor = valor;
    nov->Cart.naipe = naipe;
    nov->proxima= NULL;
    and->proxima= nov;
    return 0;
}

int tamanho(ListaCarta *carta)
{
    if(carta==NULL) return -1;
    int tam=0;
	ListaCarta *and=carta;
    while(and!=NULL)
    {
        and=and->proxima;
        tam ++;
    }
    return tam;
}

int mostracarta(ListaCarta *carta, int posicao, int *valor, int *naipe)
{
    if(posicao>tamanho(carta)||posicao<0) return -1;
    int i;
	ListaCarta *and = carta;
    for(i=0; i<posicao; i++) and=and->proxima;
    *valor = and->Cart.valor;
    *naipe = and->Cart.naipe;
    return 0;
}

///retorna 1 se o jogador ganhar, 0 se o computador e 2 se empate
int rodada(placar *placar_partida, ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira)
{
    if (*jogador == NULL || *vira == NULL || *computador == NULL) return -1;

    ///manilha
    if((*jogador)->Cart.valor-1 == (*vira)->Cart.valor && (*computador)->Cart.valor-1 == (*vira)->Cart.valor)
    {
        if((*jogador)->Cart.naipe > (*computador)->Cart.naipe)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    /// cartas iguais
    if((*jogador)->Cart.valor == (*computador)->Cart.valor)
    {

        return 2;
    }

    ///jogador jogou uma manilha
    if((*jogador)->Cart.valor-1 == (*vira)->Cart.valor || (*vira)->Cart.valor == 9 && (*jogador)->Cart.valor == 0)
    {
        return 1;
    }

    ///computador jogou uma manilha
    if((*computador)->Cart.valor-1 == (*vira)->Cart.valor || (*vira)->Cart.valor == 9 && (*computador)->Cart.valor == 0)
    {
        return 0;
    }
    ///compara duas cartas
    if((*jogador)->Cart.valor < (*computador)->Cart.valor)
    {
        return 0;
    }
    else
    {
        return 1;
    }

    return -1;
}

///cria todas as cartas do baralho
int iniciarBaralho(ListaCarta **lista)
{
    colocarCarta(lista,quatro,ouro);
    colocarCarta(lista,quatro,espada);
    colocarCarta(lista,quatro,copas);
    colocarCarta(lista,quatro,paus);
    colocarCarta(lista,cinco,ouro);
    colocarCarta(lista,cinco,espada);
    colocarCarta(lista,cinco,copas);
    colocarCarta(lista,cinco,paus);
    colocarCarta(lista,seis,ouro);
    colocarCarta(lista,seis,espada);
    colocarCarta(lista,seis,copas);
    colocarCarta(lista,seis,paus);
    colocarCarta(lista,sete,ouro);
    colocarCarta(lista,sete,espada);
    colocarCarta(lista,sete,copas);
    colocarCarta(lista,sete,paus);
    colocarCarta(lista,dama,ouro);
    colocarCarta(lista,dama,espada);
    colocarCarta(lista,dama,copas);
    colocarCarta(lista,dama,paus);
    colocarCarta(lista,valete,ouro);
    colocarCarta(lista,valete,espada);
    colocarCarta(lista,valete,copas);
    colocarCarta(lista,valete,paus);
    colocarCarta(lista,rei,ouro);
    colocarCarta(lista,rei,espada);
    colocarCarta(lista,rei,copas);
    colocarCarta(lista,rei,paus);
    colocarCarta(lista,as,ouro);
    colocarCarta(lista,as,espada);
    colocarCarta(lista,as,copas);
    colocarCarta(lista,as,paus);
    colocarCarta(lista,dois,ouro);
    colocarCarta(lista,dois,espada);
    colocarCarta(lista,dois,copas);
    colocarCarta(lista,dois,paus);
    colocarCarta(lista,tres,ouro);
    colocarCarta(lista,tres,espada);
    colocarCarta(lista,tres,copas);
    colocarCarta(lista,tres,paus);
    return 0;
}

int sorteia_mao(ListaCarta **baralho, ListaCarta **mao_aleatoria, ListaCarta *computador)
{
    if(*baralho == NULL ||*baralho == NULL && *mao_aleatoria == NULL) return -1;
    ListaCarta *aux = NULL;
    int i;
    for(i=0; i<3; i++)
    {
        aux = tirarcarta(baralho, rand()%tamanho(*baralho));
        ///tira uma carta que não está na mão do computador
        while((aux->Cart.valor == computador->Cart.valor && aux->Cart.naipe == computador->Cart.naipe) ||
                (aux->Cart.valor == computador->proxima->Cart.valor && aux->Cart.naipe == computador->proxima->Cart.naipe) ||
                (aux->Cart.valor == computador->proxima->proxima->Cart.valor && aux->Cart.naipe == computador->proxima->proxima->Cart.naipe))
        {
            aux = tirarcarta(baralho, rand()%tamanho(*baralho));
        }

        colocarCarta(mao_aleatoria,aux->Cart.valor,aux->Cart.naipe);
        free(aux);
    }
    return 0;
}

int comparar_cartas(ListaCarta **jogador, ListaCarta **computador, ListaCarta **vira)
{
    if (*jogador == NULL || *vira == NULL || *computador == NULL) return -1;

    ///manilha
    if((*jogador)->Cart.valor-1 == (*vira)->Cart.valor && (*computador)->Cart.valor-1 == (*vira)->Cart.valor)
    {
        if((*jogador)->Cart.naipe > (*computador)->Cart.naipe)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    ///jogador jogou uma manilha
    if((*jogador)->Cart.valor-1 == (*vira)->Cart.valor)
    {
        return 0;
    }

    ///computador jogou uma manilha
    if((*computador)->Cart.valor-1 == (*vira)->Cart.valor)
    {
        return 1;
    }

    ///compara duas cartas
    if((*jogador)->Cart.valor < (*computador)->Cart.valor)
    {
        return 1;
    }
    else
    {
        return 0;
    }

    /// cartas iguais
    if((*jogador)->Cart.valor == (*computador)->Cart.valor)
    {
        if((*jogador)->Cart.naipe > (*computador)->Cart.naipe)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return -1;
}

int possibilidades(ListaCarta *carta, ListaCarta *vira)
{
    ListaCarta *baralho = NULL;
    int x,y;
    x = rand()%10;
    y = rand()%4;
    while (x == carta->Cart.valor && y == carta->Cart.naipe)
    {
        x = rand()%10;
        y = rand()%4;
    }
    colocarCarta(&baralho, x, y);

    return comparar_cartas(&baralho, &carta, &vira);
}

///retorna se o computador vai pedir truco ou fugir ou aceitar
int PC_pensa(ListaCarta **computador, ListaCarta *vira)
{
    int i, j, min, aux, x, y;
    int soma_vit = 0;
    int vit[3] = {0};
    int vit2[3] = {0,1,2};
    ListaCarta *carta[3] = {NULL, NULL, NULL};

    for(i = 0; i < 3; i++)
    {
        mostracarta(*computador, i, &x, &y);
        colocarCarta(&carta[i], x, y);
    }

    for(i = 0 ; i < 3; i++ )
    {
        for (j = 0; j < 10000 ; j ++)
        {
            if(possibilidades(carta[i], vira) == 1) vit[i]++;
        }
    }

    soma_vit = vit[0]+vit[1]+vit[2];
	reiniciarmao(computador);
    for (i = 0; i < 2; i++)
    {
        min = i;
        for (j = i+1; j < 3; j++) if (vit[j] > vit[min]) min = j;
        if (i != min)
        {
            aux = vit2[i];
            vit2[i] = vit2[min];
            vit2[min] = aux;
        }
    }

    for(i = 0 ; i < 3 ; i ++)
    {
        colocarCarta(computador,carta[vit2[i]]->Cart.valor,carta[vit2[i]]->Cart.naipe);
    }
    ///o computador foge
    int truco = 0;

    ///o computador aceita o truco
    if(soma_vit > vida1) truco = 1;

    ///o computador pede truco
    if(soma_vit > vida2) truco = 2;

    return truco;
}

