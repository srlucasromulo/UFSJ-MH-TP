#include "ag.h"


solution_t** gera_populacao_inicial(int num_spots, int num_cams, spot_t** spot_list){

	solution_t** populacao;
	populacao = (solution_t**) malloc (TAM_POP * sizeof(solution_t*));

	for(int i = 0; i < TAM_POP; i++){

		populacao[i] = (solution_t*) malloc (sizeof(solution_t));
		populacao[i] = random_valid_solution(num_spots, num_cams, spot_list);

	}

	return populacao;
}

int seleciona_pai(float total_fitness, solution_t** populacao){

	srand(time(NULL));

	int valor_sorteado, pai = -1;
	int soma = 0;

	valor_sorteado = total_fitness * (rand() / RAND_MAX);

	do {
		
		pai++;
		soma += populacao[pai]->fitness;		

	} while(soma < valor_sorteado);

	return pai;
}

solution_t** crossover(solution_t* pai1, solution_t* pai2){

	solution_t** solution = (solution_t**) malloc (2 * sizeof(solution_t*));

	for(int i = 0; i < 2; i++)
		solution[i] = (solution_t*) malloc (sizeof(solution_t));

	int ponto1, ponto2;

	do {

		ponto1 = rand() % pai1->num_cams;
		ponto2 = rand() % pai1->num_cams;

	}while(ponto1 != ponto2);

	if(ponto1 > ponto2){

		int aux = ponto1;
		ponto1 = ponto2;
		ponto2 = aux;

	}

	for(int i = 0; i < pai1->num_cams; i++){

		if(i <= ponto1 || i >= ponto2){

			solution[0]->binary_solution[i] = pai1->binary_solution[i];
			solution[1]->binary_solution[i] = pai2->binary_solution[i];

		}else{

			solution[0]->binary_solution[i] = pai2->binary_solution[i];
			solution[1]->binary_solution[i] = pai1->binary_solution[i];

		}
	}
	
	return solution;
}

void mutacao(solution_t* individuo){

	for(int i = 0; i < individuo->num_cams; i++){

		if((rand() / RAND_MAX) < PROB_MUT){

			if(individuo->binary_solution[i] == 0)
				individuo->binary_solution[i] = 1;

			else
				individuo->binary_solution[i] = 0;

		}
	}
}

solution_t* elitismo(solution_t** populacao){

	int menor = 0;

	for(int i = 1; i < TAM_POP; i++){

		if(populacao[i]->cost < populacao[menor]->cost)
			menor = i;

	}

	return populacao[menor];

}

void calcula_fitness(solution_t* individuo){

	int sem_cobertura = 0;
	
	for(int i = 0; i < individuo->num_cams; i++){

		if(individuo->coverage_spots[i] == 0)
			sem_cobertura++;

	}

	individuo->fitness = K / (individuo->cost * ALFA * sem_cobertura);

}

float total_fitness_(solution_t** populacao){	// change name

	float total = 0;

	for(int i = 0; i < TAM_POP; i++)
		total += populacao[i]->fitness;

	return total;
}

int pega_melhor(solution_t** populacao){

	int maior = 0;

	for(int i = 1; i < TAM_POP; i++){

		if(populacao[i]->fitness > populacao[maior]->fitness)
			maior = i;

	}
	return maior;
}

solution_t* algoritmo_genetico(int num_spots, int num_cams, spot_t** spot_list){

	int indice_pai1, indice_pai2, melhor;
	solution_t** populacao = gera_populacao_inicial(num_spots, num_cams, spot_list);

	float total_fitness = total_fitness_(populacao);

	melhor = pega_melhor(populacao);

	solution_t* solucao_corrente;
	solucao_corrente = populacao[melhor];
	
	for(int i = 0; i < NUM_GER; i++){

		solution_t** aux = (solution_t**) malloc (2 * sizeof(solution_t*));

		for(int j = 0; j < 2; j++)
			aux[j] = (solution_t*) malloc (sizeof(solution_t));

		// ordenar

		indice_pai1 = seleciona_pai(total_fitness, populacao);
		indice_pai2 = seleciona_pai(total_fitness, populacao);

		solution_t* pai1 = populacao[indice_pai1];
		solution_t* pai2 = populacao[indice_pai2];

		for(int j = 0; j < TAM_POP; j += 2){

			aux = crossover(pai1, pai2);
			populacao[j] = aux[0];
			populacao[j + 1] = aux[1];

			mutacao(populacao[j]);
			mutacao(populacao[j + 1]);

			calcula_fitness(populacao[j]);
			calcula_fitness(populacao[j + 1]);

		}

		melhor = pega_melhor(populacao);

		if(solucao_corrente->fitness < populacao[melhor]->fitness)
			solucao_corrente = populacao[melhor];

	}

	return solucao_corrente;
}

