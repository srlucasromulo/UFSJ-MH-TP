#ifndef __GA__
#define __GA__
#define TAM_POP 40		// population size
#define NUM_GEN 600		// number of generations (iterations)
#define PROB_MUT 0.1	// mutation probability


#include <stdio.h>
#include <math.h>
#include "TAD.h"
#include "constructive.h"


solution_t** generate_init_population(int, int, spot_t**);
solution_t* genetic_algorithm(int, int, spot_t**);


#endif
