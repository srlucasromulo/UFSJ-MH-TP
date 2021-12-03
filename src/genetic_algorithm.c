#include "genetic_algorithm.h"


void calc_fitness(solution_t* solution){
	solution->fitness = pow(solution->cost, 2);
}

int cmp_func(const void* a, const void* b){

	solution_t* item_a = *(solution_t**)a;
	solution_t* item_b = *(solution_t**)b;

	return item_a->fitness < item_b->fitness ? -1 : 1;
}

void order_population(solution_t** population){

	for(int i = 0; i < TAM_POP; i++)
		calc_fitness(population[i]);

	qsort(population, TAM_POP, sizeof(solution_t*), cmp_func);
}

solution_t** generate_init_population(int num_spots, int num_cams, spot_t** spot_list){

	solution_t** population;
	population = (solution_t**) malloc (TAM_POP * sizeof(solution_t*));

	for(int i = 0; i < TAM_POP; i++){

		population[i] = (solution_t*) malloc (sizeof(solution_t));
		population[i] = random_valid_solution(num_spots, num_cams, spot_list);
	}

	return population;
}

double calc_total_fitness(solution_t** populacao){

	double total = 0;

	for(int i = 0; i < TAM_POP; i++)
		total += 1.0/populacao[i]->fitness;

	return total;
}

int get_father(double total_fitness, solution_t** population){

	int pai = -1;
	double valor_sorteado, soma = 0;

	valor_sorteado = total_fitness * ((rand() * 1.0) / RAND_MAX);

	do {
		
		pai++;
		soma += 1.0/population[pai]->fitness;		

	} while(soma < valor_sorteado);

	return pai;
}

void crossover(solution_t** population1, solution_t** population2){

	int num_cams = population1[0]->num_cams;
	int f1, f2;

	double total_fitness = calc_total_fitness(population1);

	for(int i = 0; i < TAM_POP; i+=2){

		f1 = get_father(total_fitness, population1);
		f2 = get_father(total_fitness, population1);

		int point = rand() % num_cams;

		for(int j = 0; j < num_cams; j++){

			if(j < point){

				population2[i]->binary_solution[j] = population1[f1]->binary_solution[j];
				population2[i+1]->binary_solution[j] = population1[f2]->binary_solution[j];

			}else{

				population2[i]->binary_solution[j] = population1[f2]->binary_solution[j];
				population2[i+1]->binary_solution[j] = population1[f1]->binary_solution[j];
			}
		}
	}
}

void mutation(solution_t** population){

	int num_cams = population[0]->num_cams;

	for(int i = 0; i < TAM_POP; i++){

		for(int j = 0; j < num_cams; j++){

			if(population[i]->binary_solution[j] && (rand()*1.0 / RAND_MAX) < PROB_MUT)
				population[i]->binary_solution[j] = OFF;
		}
	}
}

void elitism(solution_t** population1, solution_t** population2, solution_t** next_population){

	int p1 = 0;
	int p2 = 0;

	for(int i = 0; i < TAM_POP; i++)

		if(population1[p1]->cost < population2[p2]->cost){
			*next_population[i] = *population1[p1];
			p1++;

		} else {
			*next_population[i] = *population2[p2];
			p2++;
		}
}

void update_population(solution_t** population, spot_t** spot_list){

	for(int i = 0; i < TAM_POP; i++){
		update_solution(population[i], spot_list);
		repare_solution(population[i], spot_list);
		calc_cost(population[i]);
	}
}

solution_t* genetic_algorithm(int num_spots, int num_cams, spot_t** spot_list){

	solution_t** population1 = generate_init_population(num_spots, num_cams, spot_list);
	solution_t** population2 = generate_init_population(num_spots, num_cams, spot_list);
	solution_t** new_population = generate_init_population(num_spots, num_cams, spot_list);

	order_population(population1);

	solution_t* current_solution;
	current_solution = new_solution(num_spots, num_cams);
	*current_solution = *population1[0];

	int gen = 0;

	for(int i = 0; i < NUM_GEN; i++){

		crossover(population1, population2);

		mutation(population2);

		update_population(population2, spot_list);

		order_population(population1);
		order_population(population2);

		elitism(population1, population2, new_population);

		if(current_solution->cost > new_population[0]->cost){
			*current_solution = *new_population[0];
			gen = i;
		}

		for(int k = 0; k < TAM_POP; k++)
			*population1[k] = *new_population[k];
	}

	printf("%i %i %.1f %i ", TAM_POP, NUM_GEN, PROB_MUT*100, gen);

	return current_solution;
}
