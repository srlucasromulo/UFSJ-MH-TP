#include "inout.h"
#include "TAD.h"
#include "constructive.h"
#include "ag.h"


int main (int argc, char* argv[]) {

	// FILE* file = fopen("../data/AC_01_cover.txt", "r");	// deploy
	FILE* file = fopen("./data/AC_01_cover.txt", "r");	// production
	if (! file){
		printf("%s\n", "File not found!!");
		exit(1);
	}

	int num_spots, num_cams;
	load_values(file, &num_spots, &num_cams);
	
	spot_t** spot_list;
	spot_list = new_spot_list(num_spots);

	// DBG
	// spot_list = (spot_t**) malloc (num_spots * sizeof(spot_t*));
	// for (int i = 0; i < num_spots; i++)
	// 	spot_list[i] = (spot_t*) malloc (sizeof(spot_t));

	load_spots(file, spot_list, num_spots);

	fclose(file);

	solution_t* solution;
	solution = random_valid_solution(num_spots, num_cams, spot_list);

	// DBG
	// for (int i = 0; i < num_spots; i++){
	// 	for (int j = 0; j < spot_list[i]->num_cams; j++)
	// 		printf("%d ", spot_list[i]->cams[j]);
	// 	printf("\n\n");
	// }

	// solution_t* solution;
	// solution = new_solution(num_cams);

	// DBG 
	// printf("cost: %d, num_cams: %d \n", solution->cost, solution->num_cams);

}
