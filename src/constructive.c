#include "constructive.h"


solution_t* random_valid_solution(int num_spots, int num_cams, spot_t** spot_list){

	solution_t* solution;
	solution = new_solution(num_spots, num_cams);

	do {

		int cam_id = rand() % num_cams;

		add_cam_to_solution(cam_id, solution, spot_list);

		calc_cost(solution);

	} while(!validate_solution(solution));	

	return solution;
}
