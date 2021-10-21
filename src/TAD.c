#include "TAD.h"


spot_t* new_spot(int id, int num_cams, int* cams){

	spot_t* spot;
	spot = (spot_t*) malloc (sizeof(spot_t));

	spot->id = id;
	spot->num_cams = num_cams;

	spot->cams = (int*) malloc (num_cams * sizeof(int));
	for (int i = 0; i < num_cams; i++)
		spot->cams[i] = cams[i];

	return spot;

}

spot_t** new_spot_list(int num_spots) {

	spot_t** spots;

	spots = (spot_t**) malloc (num_spots * sizeof(spot_t*));
	for (int i = 0; i < num_spots; i++)
		spots[i] = (spot_t*) malloc (sizeof(spot_t));

	return spots;

}

solution_t* new_solution(int num_spots, int num_cams) {

	solution_t* solution;

	solution = (solution_t*) malloc (sizeof(solution_t));
	solution->cost = 0;
	solution->num_cams = num_cams;
	solution->num_spots = num_spots;

	solution->binary_solution = (int*) malloc (num_cams * sizeof(int));
	for (int i = 0; i < num_cams; i++)
		solution->binary_solution[i] = OFF;

	solution->coverage_spots = (int*) malloc (num_spots * sizeof(int));
	for (int i = 0; i < num_spots; i++)
		solution->coverage_spots[i] = FALSE;

	return solution;

}

// int validate_solution(spot_t** spots, int num_spots){

// 	for (int i = 0; i < num_spots; i++)
// 		if (!spots[i]->spotted)
// 			return FALSE;

// 	return TRUE;

// }
