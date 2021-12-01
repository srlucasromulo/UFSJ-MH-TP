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


void add_cam_to_solution(int position, solution_t* solution, spot_t** spot_list){

	solution->binary_solution[position] = ON;

	for(int i = 0; i < solution->num_spots; i++)

		if (solution->coverage_spots[i] == FALSE)

			for(int j = 0; position >= spot_list[i]->cams[j]; j++)
			
				if(position == spot_list[i]->cams[j])
			
					solution->coverage_spots[i] = TRUE;
}

int validate_solution(solution_t* solution){

	for(int i = 0; i < solution->num_spots; i++)
		if(!solution->coverage_spots[i])
			return FALSE;

	return TRUE;
}

void update_solution(solution_t* solution, spot_t** spot_list){

	calc_cost(solution);

	for(int i = 0; i < solution->num_spots; i++)
		solution->coverage_spots[i] = 0;

	for(int i = 0; i < solution->num_cams; i++)

		if(solution->binary_solution[i])

			add_cam_to_solution(i, solution, spot_list);
}

void repare_solution(solution_t* solution, spot_t** spot_list){

	for(int i = 0; i < solution->num_spots; i++){

		if(solution->coverage_spots[i] == FALSE){

			int random = rand() % spot_list[i]->num_cams;
			// printf("random: %i, num_cams: %i <----\n", random, spot_list[i]->num_cams);
			int cam_id = spot_list[i]->cams[random];

			add_cam_to_solution(cam_id, solution, spot_list);
		}
	}
	calc_cost(solution);
}

void calc_cost(solution_t* solution){

	solution->cost = 0;
	for(int i = 0; i < solution->num_cams; i++)
		if(solution->binary_solution[i])
			solution->cost++;
}
