#include <stdio.h>
#include <stdlib.h>

#include "inout.h"
#include "TAD.h"


int main (int argc, char* argv[]) {

	// FILE* file = fopen("../data/AC_01_cover.txt", "r");	// deploy
	FILE* file = fopen("./data/AC_01_cover.txt", "r");	// production
	if (! file){
		printf("%s\n", "File not found!!");
		exit(1);
	}

	int num_spots, num_cams;
	load_values(file, &num_spots, &num_cams);
	
	spot_t** spots;
	spots = new_spot_list(num_spots);

	// DBG
	// spots = (spot_t**) malloc (num_spots * sizeof(spot_t*));
	// for (int i = 0; i < num_spots; i++)
	// 	spots[i] = (spot_t*) malloc (sizeof(spot_t));

	load_spots(file, spots, num_spots);

	fclose(file);

	// DBG
	// for (int i = 0; i < num_spots; i++){
	// 	for (int j = 0; j < spots[i]->num_cams; j++)
	// 		printf("%d ", spots[i]->cams[j]);
	// 	printf("\n\n");
	// }

	solution_t* solution;
	solution = new_solution(num_cams);

	// DBG 
	// printf("cost: %d, num_cams: %d \n", solution->cost, solution->num_cams);

}
