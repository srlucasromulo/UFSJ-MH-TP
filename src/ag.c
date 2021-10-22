#include "ag.h"


solution_t** gera_populacao_inicial(int num_individuos, int num_spots, int num_cams, spot_t** spot_list){

	solution_t** populacao;
	populacao = (solution_t**) malloc (num_individuos * sizeof(solution_t*));

	for(int i = 0; i < num_individuos; i++){

		populacao[i] = (solution_t*) malloc (sizeof(solution_t));
		populacao[i] = random_valid_solution(num_spots, num_cams, spot_list);

	}

	return populacao;
}
