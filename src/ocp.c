#include "inout.h"
#include "TAD.h"
#include "constructive.h"
#include "ag.h"


int main (int argc, char* argv[]) {

	FILE* file = fopen("./data/AC_01_cover.txt", "r");
	if (! file){
		printf("%s\n", "File not found!!");
		exit(1);
	}

	int num_spots, num_cams;
	load_values(file, &num_spots, &num_cams);
	
	spot_t** spot_list;
	spot_list = new_spot_list(num_spots);

	load_spots(file, spot_list, num_spots);

	fclose(file);

	solution_t* solution;
	solution = random_valid_solution(num_spots, num_cams, spot_list);

	export_solution(solution);
}
