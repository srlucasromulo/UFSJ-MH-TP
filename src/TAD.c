#include "TAD.h"


// creates a new target spot and lists the cams that reaches it
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

// creates a blank list of pointers to target spots 
spot_t** new_spot_list(int num_spots) {

	spot_t** spots;

	spots = (spot_t**) malloc (num_spots * sizeof(spot_t*));
	for (int i = 0; i < num_spots; i++)
		spots[i] = (spot_t*) malloc (sizeof(spot_t));

	return spots;
}

// creates a blank solution
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

// adds a cam to the solution and update the target spots
void add_cam_to_solution(int position, solution_t* solution, spot_t** spot_list){

	solution->binary_solution[position] = ON;

	// iterates in the list of target spots
	for(int i = 0; i < solution->num_spots; i++)

		// checks if the spot is already covered
		if (solution->coverage_spots[i] == FALSE)

			// iterates in the list of cams that reaches the spot
			for(int j = 0; position >= spot_list[i]->cams[j]; j++)
			
				// if the cam reaches the spot, marks it
				if(position == spot_list[i]->cams[j])
					solution->coverage_spots[i] = TRUE;
}

// checks if a solution is valid (all targets are covered)
int validate_solution(solution_t* solution){

	for(int i = 0; i < solution->num_spots; i++)
		if(!solution->coverage_spots[i])
			return FALSE;

	return TRUE;
}

// after crossover and mutation, updates the list of covered target spots
void update_solution(solution_t* solution, spot_t** spot_list){

	// clears the list of reached target spots
	for(int i = 0; i < solution->num_spots; i++)
		solution->coverage_spots[i] = 0;

	// calls add_cam_to_solution to every cam in the new solution
	// to fill the list of targeted spots
	for(int i = 0; i < solution->num_cams; i++)

		if(solution->binary_solution[i])
			add_cam_to_solution(i, solution, spot_list);
}

// checks if there is target spots uncovered and adds a cam that covers that spot
void repare_solution(solution_t* solution, spot_t** spot_list){

	// for each non covered target spot
	for(int i = 0; i < solution->num_spots; i++){

		if(solution->coverage_spots[i] == FALSE){

			// chooses a random cam (that covers the spot) and adds to solution
			int random = rand() % spot_list[i]->num_cams;
			int cam_id = spot_list[i]->cams[random];

			add_cam_to_solution(cam_id, solution, spot_list);
		}
	}
}

// calculates the cost of a solution
// cost = num of cams used to reaches all the target spots
void calc_cost(solution_t* solution){

	int cost = 0;

	for(int i = 0; i < solution->num_cams; i++)
		if(solution->binary_solution[i])
			cost++;

	solution->cost = cost;
}
