#include "genetic_algorithm.h"


// calcs a subject fitness
// fitness = cost^2
void calc_fitness(solution_t* solution){
	solution->fitness = pow(solution->cost, 2);
}

// compare function used in qsort
int cmp_func(const void* a, const void* b){

	solution_t* item_a = *(solution_t**)a;
	solution_t* item_b = *(solution_t**)b;

	return item_a->fitness < item_b->fitness ? -1 : 1;
}

// uses qsort to order a population by its subjects fitness
void order_population(solution_t** population){

	for(int i = 0; i < TAM_POP; i++)
		calc_fitness(population[i]);

	qsort(population, TAM_POP, sizeof(solution_t*), cmp_func);
}


// creates a new population of TAM_POP subjects using the construtive heuristic
solution_t** generate_init_population(int num_spots, int num_cams, spot_t** spot_list){

	solution_t** population;
	population = (solution_t**) malloc (TAM_POP * sizeof(solution_t*));

	for(int i = 0; i < TAM_POP; i++){

		// creates a subject using the constructive heuristic
		population[i] = (solution_t*) malloc (sizeof(solution_t));
		population[i] = random_valid_solution(num_spots, num_cams, spot_list);
	}

	return population;
}

// calcs the value that is going to be used in the fathers selection.
// its based on the subjects fitness
double calc_total_fitness(solution_t** population){

	double total = 0;

	// sum 1/(subject fitness) to the total value
	for(int i = 0; i < TAM_POP; i++)
		total += 1.0/population[i]->fitness;

	return total;
}

// select 1 father using the roulette wheel selection
int get_father(double total_fitness, solution_t** population){

	int father = -1;
	double sorted_value, sum = 0;

	// sorts a value in range 0 to calc_total_fitness value
	sorted_value = total_fitness * ((rand() * 1.0) / RAND_MAX);

	do {
		
		// roulette wheel
		father++;
		sum += 1.0/population[father]->fitness;		

	} while(sum < sorted_value);

	return father;
}

// crossover current population to create a new population
// selects two father to create two new subjects
void crossover(solution_t** population1, solution_t** population2){

	int num_cams = population1[0]->num_cams;
	int f1, f2;

	double total_fitness = calc_total_fitness(population1);

	for(int i = 0; i < TAM_POP; i+=2){

		// uses roulette wheel to selects the fathers
		f1 = get_father(total_fitness, population1);
		f2 = get_father(total_fitness, population1);

		// selects one crossover point
		int point = rand() % num_cams;

		// creates two new subjects
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

// mutates the subjects chromosomes trying to minimize the cost of the solution
void mutation(solution_t** population){

	int num_cams = population[0]->num_cams;

	// for each subject in the population
	for(int i = 0; i < TAM_POP; i++){

		// check all the possible cams
		for(int j = 0; j < num_cams; j++){

			// for each cam in the solution, tries to take it off
			if(population[i]->binary_solution[j] && (rand()*1.0 / RAND_MAX) < PROB_MUT)
				population[i]->binary_solution[j] = OFF;
		}
	}
}

// after the cration of a new population using crossover and mutation:
// updates the covered target spots, repares the population (makes it valid), calc its cost
void update_population(solution_t** population, spot_t** spot_list){

	for(int i = 0; i < TAM_POP; i++){
		update_solution(population[i], spot_list);
		repare_solution(population[i], spot_list);
		calc_cost(population[i]);
	}
}

// creates a new generation based on the union of current population and the population
// created using the crossover and mutation process
void elitism(solution_t** population1, solution_t** population2, solution_t** next_population){

	int p1 = 0;
	int p2 = 0;

	// select the TAM_POP best subjects to compose the new generation 
	for(int i = 0; i < TAM_POP; i++)

		if(population1[p1]->cost < population2[p2]->cost){
			*next_population[i] = *population1[p1];
			p1++;

		} else {
			*next_population[i] = *population2[p2];
			p2++;
		}
}

// implementation of the genetic algorithm
solution_t* genetic_algorithm(int num_spots, int num_cams, spot_t** spot_list){

	// current population (creates 1st population using the constructive heuristic)
	solution_t** population1 = generate_init_population(num_spots, num_cams, spot_list);
	// generated population (allocates memory)
	solution_t** population2 = generate_init_population(num_spots, num_cams, spot_list);
	// next generation (allocates memory)
	solution_t** new_population = generate_init_population(num_spots, num_cams, spot_list);

	order_population(population1);

	// current best subject
	solution_t* current_solution;
	current_solution = new_solution(num_spots, num_cams);
	*current_solution = *population1[0];

	// generation of the best subject
	int gen = 0;

	for(int i = 0; i < NUM_GEN; i++){

		crossover(population1, population2);

		mutation(population2);

		update_population(population2, spot_list);

		order_population(population1);
		order_population(population2);

		elitism(population1, population2, new_population);

		// if its required, updates the best current subject and its generation
		if(current_solution->cost > new_population[0]->cost){
			*current_solution = *new_population[0];
			gen = i;
		}

		// updates the current generation w/ the new generation
		// to be used int the next iteration
		for(int k = 0; k < TAM_POP; k++)
			*population1[k] = *new_population[k];
	}

	printf("%i %i %.1f %i ", TAM_POP, NUM_GEN, PROB_MUT*100, gen);

	return current_solution;
}
