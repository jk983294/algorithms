#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

// Struct to encapsulate the parameters
struct Individual {
    std::vector<double> genes;
    double fitness;

    Individual(double x, double y) : genes({x, y}), fitness(std::numeric_limits<double>::max()) {}

    double getX() const { return genes[0]; }
    double getY() const { return genes[1]; }
    void setX(double x) { genes[0] = x; }
    void setY(double y) { genes[1] = y; }
};

// Function to calculate the fitness (cost) of the current state
double calculate_fitness(const Individual &individual) {
    double x = individual.getX();
    double y = individual.getY();
    return x * x + y * y;
}

// Genetic Algorithm implementation
void genetic_algorithm(std::vector<Individual> &population, double mutation_rate, int max_generations) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_real_distribution<> dis_gene(-50.0, 50.0);

    for (int generation = 0; generation < max_generations; ++generation) {
        // Calculate fitness for each individual
        for (auto &individual : population) {
            individual.fitness = calculate_fitness(individual);
        }

        // Sort population by fitness (ascending order)
        std::sort(population.begin(), population.end(), [](const Individual &a, const Individual &b) {
            return a.fitness < b.fitness;
        });

        // Print the best individual of the current generation
        std::cout << "Generation " << generation << ": Best fitness = " << population[0].fitness << ", Position = (" << population[0].getX() << ", " << population[0].getY() << ")\n";

        // Select the top half of the population for reproduction
        std::vector<Individual> new_population;
        for (size_t i = 0; i < population.size() / 2; ++i) {
            new_population.push_back(population[i]);
        }

        // Crossover and mutation to generate new population
        while (new_population.size() < population.size()) {
            // Select two parents
            std::uniform_int_distribution<> dis_parent(0, new_population.size() - 1);
            Individual parent1 = new_population[dis_parent(gen)];
            Individual parent2 = new_population[dis_parent(gen)];

            // Crossover
            Individual child(0.0, 0.0);
            child.setX((parent1.getX() + parent2.getX()) / 2.0);
            child.setY((parent1.getY() + parent2.getY()) / 2.0);

            // Mutation
            if (dis(gen) < mutation_rate) {
                child.setX(dis_gene(gen));
                child.setY(dis_gene(gen));
            }

            new_population.push_back(child);
        }

        population = new_population;
    }

    // Print the best individual of the final generation
    std::cout << "Final best position: (" << population[0].getX() << ", " << population[0].getY() << "), Fitness: " << population[0].fitness << std::endl;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-50.0, 50.0);

    int population_size = 20;
    std::vector<Individual> population;

    for (int i = 0; i < population_size; ++i) {
        double x = dis(gen); // Initial x in range [-50, 50]
        double y = dis(gen); // Initial y in range [-50, 50]
        population.emplace_back(x, y);
    }

    double mutation_rate = 0.1;
    int max_generations = 100;

    genetic_algorithm(population, mutation_rate, max_generations);

    return 0;
}