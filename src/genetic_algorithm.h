#ifndef __GA__
#define __GA__
#define TAM_POP 40
#define NUM_GEN 600
#define PROB_MUT 0.1


#include <stdio.h>
#include <math.h>
#include "TAD.h"
#include "constructive.h"


solution_t** generate_init_population(int, int, spot_t**);
solution_t* genetic_algorithm(int, int, spot_t**);


#endif
