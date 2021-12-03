#include "constructive.h"


// creates a valid solution using a random heuristics  
solution_t* random_valid_solution(int num_spots, int num_cams, spot_t** spot_list){

	solution_t* solution;
	solution = new_solution(num_spots, num_cams);

	do {	// creates a valid solution

		// adds a random cam to solution
		int cam_id = rand() % num_cams;
		add_cam_to_solution(cam_id, solution, spot_list);

	} while(!validate_solution(solution));

	calc_cost(solution);

	return solution;
}
