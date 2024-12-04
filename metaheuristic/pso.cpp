#include <iostream>
#include <cmath>
#include <random>
#include <vector>

// Struct to encapsulate the parameters
struct Particle {
    std::vector<double> position;
    std::vector<double> velocity;
    std::vector<double> best_position;
    double best_value;

    Particle(double x, double y) : position({x, y}), velocity({0.0, 0.0}), best_position({x, y}), best_value(std::numeric_limits<double>::max()) {}

    double getX() const { return position[0]; }
    double getY() const { return position[1]; }
    void setX(double x) { position[0] = x; }
    void setY(double y) { position[1] = y; }
};

// Function to calculate the energy (cost) of the current state
double calculate_energy(const Particle &particle) {
    double x = particle.getX();
    double y = particle.getY();
    return x * x + y * y;
}

// Particle Swarm Optimization algorithm
void particle_swarm_optimization(std::vector<Particle> &particles, double inertia_weight, double cognitive_weight, double social_weight, int max_iterations) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    Particle global_best_particle(0.0, 0.0);
    global_best_particle.best_value = std::numeric_limits<double>::max();

    for (int iteration = 0; iteration < max_iterations; ++iteration) {
        for (auto &particle : particles) {
            double current_value = calculate_energy(particle);

            if (current_value < particle.best_value) {
                particle.best_value = current_value;
                particle.best_position = particle.position;
            }

            if (current_value < global_best_particle.best_value) {
                global_best_particle.best_value = current_value;
                global_best_particle.best_position = particle.position;
            }
        }

        for (auto &particle : particles) {
            for (int i = 0; i < 2; ++i) {
                double r1 = dis(gen);
                double r2 = dis(gen);

                particle.velocity[i] = inertia_weight * particle.velocity[i] +
                                       cognitive_weight * r1 * (particle.best_position[i] - particle.position[i]) +
                                       social_weight * r2 * (global_best_particle.best_position[i] - particle.position[i]);

                particle.position[i] += particle.velocity[i];
            }
        }
    }

    std::cout << "Global best position: (" << global_best_particle.best_position[0] << ", " << global_best_particle.best_position[1] << "), Energy: " << global_best_particle.best_value << std::endl;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-50.0, 50.0);

    int num_particles = 20;
    std::vector<Particle> particles;

    for (int i = 0; i < num_particles; ++i) {
        double x = dis(gen); // Initial x in range [-50, 50]
        double y = dis(gen); // Initial y in range [-50, 50]
        particles.emplace_back(x, y);
    }

    double inertia_weight = 0.729;
    double cognitive_weight = 1.49445;
    double social_weight = 1.49445;
    int max_iterations = 1000;

    particle_swarm_optimization(particles, inertia_weight, cognitive_weight, social_weight, max_iterations);

    return 0;
}