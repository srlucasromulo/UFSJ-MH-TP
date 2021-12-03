#include "inout.h"
#include "TAD.h"
#include "constructive.h"
#include "genetic_algorithm.h"

#include <string.h>


int main (int argc, char* argv[]) {

	// random seed and time count
	srand(time(NULL));
	clock_t t = clock();

	// selects the file
	char filepath[50] = "./data/";
	char filename[50] = "AC_01_cover.txt";
	strcat(filepath,filename);

	// try to open file
	FILE* file = fopen(filepath, "r");
	if (! file){
		printf("%s\n", "File not found!!");
		exit(1);
	}

	// read target number and cam number
	int num_spots, num_cams;
	load_values(file, &num_spots, &num_cams);
	
	// read target cams
	spot_t** spot_list;
	spot_list = new_spot_list(num_spots);
	load_spots(file, spot_list, num_spots);

	// close file
	fclose(file);

	// generate a solution using GA
	solution_t* solution;
	solution = genetic_algorithm(num_spots, num_cams, spot_list);

	// ends time count (Linux->CPU time, Win->Wall time)
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("%i %li \n", solution->cost, t);
}
