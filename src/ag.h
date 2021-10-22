#ifndef __AG__
#define __AG__
#define TAM_POP 10
#define NUM_GER 100
#define PROB_MUT 0.1
#define K 1000000
#define ALFA 2


#include <stdio.h>
#include "TAD.h"
#include "constructive.h"


solution_t* gera_individuo(int, int, spot_t** );
solution_t** gera_populacao_inicial(int, int, spot_t**);


#endif
