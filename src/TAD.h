#ifndef __TAD__
#define __TAD__

#include <stdlib.h>


#define TRUE 1
#define FALSE 0


typedef struct spot_t {
	int id;
	int num_cams;
	int* cams;
	int spotted;	// não gostei do nome
} spot_t;

typedef struct solution_t {
	int profit;
	int num_cams;
	int* binary_solution;
} solution_t;


spot_t* new_spot(int, int, int*);
spot_t** new_spot_list(int);
solution_t* new_solution(int);


#endif
