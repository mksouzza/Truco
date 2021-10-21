#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "truco.h"
#include "Tristto.h"
int main()
{
	srand((unsigned)time(NULL));
	inicializaTela("truco");
	menu();
	finalizaTela();
	return 0;
}