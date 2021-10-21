#ifndef __TAD__
#define __TAD__

#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define ON TRUE
#define OFF FALSE


typedef struct spot_t {
	int id;
	int num_cams;
	int* cams;
	int spotted;
} spot_t;

typedef struct solution_t {
	int cost;
	int num_cams;
	int* binary_solution;
} solution_t;


spot_t* new_spot(int, int, int*);
spot_t** new_spot_list(int);
solution_t* new_solution(int);
int validate_solution(spot_t**, int);


#endif
