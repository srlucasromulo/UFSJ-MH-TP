#include "ag.h"


void print_populacao(solution_t**);


solution_t** generate_init_population(int num_spots, int num_cams, spot_t** spot_list){

	solution_t** population;
	population = (solution_t**) malloc (TAM_POP * sizeof(solution_t*));

	for(int i = 0; i < TAM_POP; i++){

		population[i] = (solution_t*) malloc (sizeof(solution_t));
		population[i] = random_valid_solution(num_spots, num_cams, spot_list);
	}

	return population;
}

int get_father(double total_fitness, solution_t** population){

	int pai = -1;
	double valor_sorteado, soma = 0;

	valor_sorteado = total_fitness * ((rand() * 1.0) / RAND_MAX);

	do {
		
		pai++;
		soma += 1.0/population[pai]->cost;		

	} while(soma < valor_sorteado);

	return pai;
}

void crossover(solution_t** population, int father1, int father2){

	int num_spots = population[0]->num_spots;
	int num_cams = population[0]->num_cams;

	solution_t** father = (solution_t**) malloc (2 * sizeof(solution_t*));

	for(int i = 0; i < 2; i++){
		father[i] = (solution_t*) malloc (sizeof(solution_t));
		father[i] = new_solution(num_spots, num_cams);
	}

	*father[0] = *(solution_t*)population[father1];
	*father[1] = *(solution_t*)population[father2];


	for(int i = 0; i < TAM_POP; i+=2){

		int point = rand() % num_cams;

		for(int j = 0; j < num_cams; j++){

			if(j < point){

				population[i]->binary_solution[j] = father[0]->binary_solution[j];
				population[i+1]->binary_solution[j] = father[1]->binary_solution[j];

			}else{

				population[i]->binary_solution[j] = father[1]->binary_solution[j];
				population[i+1]->binary_solution[j] = father[0]->binary_solution[j];
			}
		}
	}
}

void mutation(solution_t** population){

	int num_cams = population[0]->num_cams;

	for(int i = 0; i < TAM_POP; i++){

		for(int j = 0; j < num_cams; j++){

			if((rand()*1.0 / RAND_MAX) < PROB_MUT){

				if(population[i]->binary_solution[j])
					population[i]->binary_solution[j] = 0;
				// else
				// 	population[i]->binary_solution[j] = 1;
			}
		}
	}
}

double calc_total_fitness(solution_t** populacao){

	double total = 0;

	for(int i = 0; i < TAM_POP; i++)
		total += 1.0/populacao[i]->cost;

	return (total);
}

int cmp_func(const void* a, const void* b){

	solution_t* item_a = *(solution_t**)a;
	solution_t* item_b = *(solution_t**)b;

	return item_a->cost < item_b->cost ? -1 : 1;
}

void order_population(solution_t** population){

	qsort(population, TAM_POP, sizeof(solution_t*), cmp_func);
}


solution_t* ag(int num_spots, int num_cams, spot_t** spot_list){

	solution_t** population = generate_init_population(num_spots, num_cams, spot_list);

	order_population(population);

	solution_t* current_solution;
	current_solution = new_solution(num_spots, num_cams);
	*current_solution = *population[0];

	printf("populacao inicial: ");
	for(int k = 0; k < TAM_POP; k++)
		printf("%i ", population[k]->cost);

	for(int i = 0; i < NUM_GER; i++){

		double total_fitness = calc_total_fitness(population);

		int father1 = get_father(total_fitness, population);

		int father2 = get_father(total_fitness, population);

		crossover(population, father1, father2);

		mutation(population);

		for(int j = 0; j < TAM_POP; j++)
			update_solution(population[j]);

		// for(int j = 0; j < TAM_POP; j++)
		// 	repare_solution(population[j], spot_list);

		order_population(population);

		// DBG
		if(population[0]->cost < current_solution->cost && validate_solution(population[0])){
			printf("TROCOU!! <--- pop0: %i, current: %i\n", population[0]->cost, current_solution->cost);
			*current_solution = *population[0];
		}

		// errado, atualizar coverage
		int count = 0;
		for(int k = 0; k < TAM_POP; k++)
			if(validate_solution(population[k]) == FALSE)
				count++;

		printf("\npopulacao%i: ", i+1);
		for(int k = 0; k < TAM_POP; k++)
			printf("%i ", population[k]->cost);

		printf(" -  invalidas: %i", count);
	}

	printf("\n");

	return current_solution;
}

// DBG
void print_populacao(solution_t** populacao){

	for (int i = 0; i < TAM_POP; i++){

		printf("Custo: %i \n", populacao[i]->cost);

		for (int j = 0; j < populacao[i]->num_cams; j++){

			if (populacao[i]->binary_solution[j])
				printf("%i ", j);

		}

		printf("\n");

	}
}