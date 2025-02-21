//generate a workload for a system (1000 processes), arrival rate of 2 per second
// poisson distribution, sevice time is exponentially distributed with average of 1 second

#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>


struct ProcessGen {
    int id;
    double arrival_time;
    double service_time;
};

std::vector<ProcessGen> generateProcesses(int num_processes, double arrival_rate, double service_time) {
    // create a vector to store the processes
    std::vector<ProcessGen> processes;
    // Create a random number generator
    std::default_random_engine generator;
    generator.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    // Create an exponential distribution for inter-arrival times
    std::exponential_distribution<double> arrival_dist(arrival_rate);
    // Create an exponential distribution for service times dividing 1 by the average service time
    std::exponential_distribution<double> service_dist(1.0 / service_time);

    // Initialize current time
    double current_time = 0.0;
     // Generate the processes
    for (int i = 0; i < num_processes; i++) {
        double arrival_interval = arrival_dist(generator);
        current_time += arrival_interval;
        double service_time = service_dist(generator);
        processes.push_back({i, current_time, service_time});
    }
    return processes;
}

int main() {
    int num_processes = 1000;
    double arrival_rate = 2; //lambda
    double service_time = 1; //mu

    std::vector<ProcessGen> processes = generateProcesses(num_processes, arrival_rate, service_time);

    // Calculate the average inter-arrival time
    double total_inter_arrival_time = 0.0;
    for (size_t i = 1; i < processes.size(); ++i) {
        // Calculate the inter-arrival time between the current and previous process
        total_inter_arrival_time += (processes[i].arrival_time - processes[i - 1].arrival_time);
    }
    // Calculate the average inter-arrival time
    double average_inter_arrival_time = total_inter_arrival_time / (num_processes - 1);

    // Print the generated processes
    for (const ProcessGen& process : processes) {
        std::cout << "ID: " << process.id << " A_T: " << process.arrival_time << " S_T: " << process.service_time << std::endl;
    }

    // Print the average inter-arrival time
    std::cout << "Average Inter-Arrival Time: " << average_inter_arrival_time << std::endl;

    return 0;
}

