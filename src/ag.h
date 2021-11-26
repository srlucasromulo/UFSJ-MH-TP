#ifndef __AG__
#define __AG__
#define TAM_POP 1000
#define NUM_GER 1000
#define PROB_MUT 0.05
#define ALFA 2


#include <stdio.h>
#include "TAD.h"
#include "constructive.h"


solution_t* gera_individuo(int, int, spot_t** );
solution_t** generate_init_population(int, int, spot_t**);

solution_t* ag(int, int, spot_t**);


#endif
