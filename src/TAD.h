#ifndef __TAD__
#define __TAD__


#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define TRUE 1
#define FALSE 0
#define ON TRUE
#define OFF FALSE


typedef struct spot_t {
	int id;
	int num_cams;
	int* cams;
} spot_t;

typedef struct solution_t {
	int cost;
	int fitness;
	int num_cams;
	int num_spots;
	int* binary_solution;
	int* coverage_spots;
} solution_t;


spot_t* new_spot(int, int, int*);
spot_t** new_spot_list(int);
solution_t* new_solution(int, int);
int validate_solution(solution_t*);
void update_solution(solution_t*);
void repare_solution(solution_t*, spot_t**);

#endif
