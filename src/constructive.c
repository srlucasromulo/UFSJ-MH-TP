#include "constructive.h"


void update_solution(int position, solution_t* solution, spot_t** spot_list){

	if(solution->binary_solution[position]){
		return;
	}

	solution->cost += 1;
	solution->binary_solution[position] = ON;

	for(int i = 0; i < solution->num_spots || solution->coverage_spots[i] == 0; i++)
		
		for(int j = 0; position >= spot_list[i]->cams[j]; j++)
		
			if(position == spot_list[i]->cams[j])
		
				solution->coverage_spots[i] = TRUE;
}

solution_t* random_valid_solution(int num_spots, int num_cams, spot_t** spot_list){

	solution_t* solution;
	solution = new_solution(num_spots, num_cams);

	srand(time(NULL));

	do {

		int position = rand() % num_cams;

		update_solution(position, solution, spot_list);

	} while(!validate_solution(solution));	

	// printf("fitness : %i \n", solution->cost);

	// for(int i = 0; i < num_spots; i++)
	// 	printf("%i", solution->coverage_spots[i]);

	return solution;

}
