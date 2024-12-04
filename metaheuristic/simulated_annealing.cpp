#include <iostream>
#include <cmath>
#include <random>
#include <vector>

// Struct to encapsulate the parameters
struct Params {
    std::vector<double> values;

    Params(double x, double y) : values({x, y}) {}

    double getX() const { return values[0]; }
    double getY() const { return values[1]; }
    void setX(double x) { values[0] = x; }
    void setY(double y) { values[1] = y; }
};

// Function to calculate the energy (cost) of the current state
double calculate_energy(const Params &params) {
    double x = params.getX();
    double y = params.getY();
    return x * x + y * y;
}

// Function to generate a neighbor state
void generate_neighbor(Params &params, double step_size, std::mt19937 &gen) {
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    double new_x = params.getX() + dis(gen) * step_size;
    double new_y = params.getY() + dis(gen) * step_size;
    params.setX(new_x);
    params.setY(new_y);
}

// Simulated Annealing algorithm with adaptive cooling
void simulated_annealing(Params &params, double initial_temperature, double cooling_rate, int max_iterations) {
    std::random_device rd;
    std::mt19937 gen(rd());

    double current_temperature = initial_temperature;
    double current_energy = calculate_energy(params);
    Params best_params = params;
    double best_energy = current_energy;

    for (int iteration = 0; iteration < max_iterations; ++iteration) {
        Params new_params = params;
        generate_neighbor(new_params, current_temperature, gen);
        double new_energy = calculate_energy(new_params);

        if (new_energy < current_energy) {
            params = new_params;
            current_energy = new_energy;
            if (new_energy < best_energy) {
                best_params = new_params;
                best_energy = new_energy;
            }
        } else {
            std::uniform_real_distribution<> dis(0.0, 1.0);
            double acceptance_probability = exp((current_energy - new_energy) / current_temperature);
            if (dis(gen) < acceptance_probability) {
                params = new_params;
                current_energy = new_energy;
            }
        }

        // Adaptive cooling schedule
        if (iteration % 100 == 0) {
            if (current_energy < best_energy) {
                current_temperature *= 0.95; // Faster cooling if improving
            } else {
                current_temperature *= 1.05; // Slower cooling if not improving
            }
        } else {
            current_temperature *= cooling_rate;
        }
    }

    params = best_params;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-50.0, 50.0);

    double x = dis(gen); // Initial x in range [-50, 50]
    double y = dis(gen); // Initial y in range [-50, 50]
    Params params(x, y);
    double initial_temperature = 1000.0;
    double cooling_rate = 0.995;
    int max_iterations = 10000;

    std::cout << "Initial state: (" << params.getX() << ", " << params.getY() << "), Energy: " << calculate_energy(params) << std::endl;

    simulated_annealing(params, initial_temperature, cooling_rate, max_iterations);

    std::cout << "Final state: (" << params.getX() << ", " << params.getY() << "), Energy: " << calculate_energy(params) << std::endl;

    return 0;
}