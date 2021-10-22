#include "inout.h"


void load_values(FILE* file, int* num_spots, int* num_cams){

	fscanf(file, "%d %d\n", num_spots, num_cams);
}

void load_spots(FILE* file, spot_t** spots, int num_spots){

	for (int i = 0; i < num_spots; i++){

		int id, num_cams;
		fscanf(file, "%d\n%d\n", &id, &num_cams);

		int cams[num_cams];

		for (int j = 0; j < num_cams; j++)
			fscanf(file, "%d ", &cams[j]);

		spot_t* spot;
		spot = new_spot(id, num_cams, cams);
		spots[i] = spot;

		fscanf(file, "\n");
	}
}

void export_solution(solution_t* solution){

	FILE* file = fopen("./output.txt", "w");

	fprintf(file, "%i\n", solution->cost);

	for (int i = 0; i < solution->num_cams; i++)
		if (solution->binary_solution[i])
			fprintf(file, "%d ", i);

	fprintf(file, "\n");

	fclose(file);
}
