#include "constructive.h"

#include <stdio.h>	// DBG


void add_cam_to_solution(int position, solution_t* solution, spot_t** spot_list){

	if(solution->binary_solution[position]){
		return;
	}

	solution->cost += 1;
	solution->binary_solution[position] = ON;

	for(int i = 0; i < solution->num_spots; i++)

		if (solution->coverage_spots[i] == FALSE)

			for(int j = 0; position >= spot_list[i]->cams[j]; j++)
			
				if(position == spot_list[i]->cams[j])
			
					solution->coverage_spots[i] = TRUE;
}

solution_t* random_valid_solution(int num_spots, int num_cams, spot_t** spot_list){

	solution_t* solution;
	solution = new_solution(num_spots, num_cams);

	do {

		int cam_id = rand() % num_cams;

		add_cam_to_solution(cam_id, solution, spot_list);

	} while(!validate_solution(solution));	

	return solution;
}
