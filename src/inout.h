#ifndef __INOUT__
#define __INOUT__

#include <stdio.h>
#include <stdlib.h>

#include "TAD.h"


void load_values(FILE*, int*, int*);
void load_spots(FILE*, spot_t**, int);
void export_solution(solution_t*);


#endif
