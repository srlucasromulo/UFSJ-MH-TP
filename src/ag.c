#include "ag.h"


void preenche_cobertura_pontos(int id, solution_t* solution, spot_t** spot_list){

	int i;

	for(i = 0; i < solution->num_spots || solution->coverage_spots[i] == 0; i++){

		for(int j = 0; id >= spot_list[i]->cams[j]; j++){

			if(id == spot_list[i]->cams[j])
				solution->coverage_spots[i] = TRUE;
										
		}		
	}
}


int verifica_viabilidade(solution_t* solution){

	for(int i = 0; i < solution->num_spots; i++){

		if(solution->coverage_spots[i] == 0)
			return FALSE;

	}

	return TRUE;
}


solution_t* gera_individuo(int num_spots, int num_cams, spot_t** spot_list){

	solution_t* solution;
	solution = new_solution(num_spots, num_cams);

	int position, verify = FALSE;

	srand(time(NULL));

	do {

		position = rand() % num_cams;

		if(!solution->binary_solution[position]){

			solution->cost += 1;
			preenche_cobertura_pontos(position, solution, spot_list);
			verify = verifica_viabilidade(solution);

		}


	} while(!verify);	

	printf("fitness : %i \n", solution->cost);

	for(int i = 0; i < num_spots; i++)
		printf("%i", solution->coverage_spots[i]);

	return solution;

}


solution_t** gera_populacao_inicial(int num_individuos, int num_spots, int num_cams, spot_t** spot_list){

	solution_t** populacao;
	populacao = (solution_t**) malloc (num_individuos * sizeof(solution_t*));

	for(int i = 0; i < num_individuos; i++){

		populacao[i] = (solution_t*) malloc (sizeof(solution_t));
		populacao[i] = gera_individuo(num_spots, num_cams, spot_list);

	}

	return populacao;
}



