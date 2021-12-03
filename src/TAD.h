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
	int* cams;		// list of cams that covers the target spot
} spot_t;

typedef struct solution_t {
	int cost;
	int fitness;
	int num_cams;
	int num_spots;
	int* binary_solution;	// bin list that represents cams used
	int* coverage_spots;	// bin list that marks covered target spots
} solution_t;


spot_t* new_spot(int, int, int*);
spot_t** new_spot_list(int);
solution_t* new_solution(int, int);

void calc_cost(solution_t*);
int validate_solution(solution_t*);
void update_solution(solution_t*, spot_t**);
void repare_solution(solution_t*, spot_t**);
void add_cam_to_solution(int, solution_t*, spot_t**);


#endif
