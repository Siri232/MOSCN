#include <iostream>
#include <fstream>
#include <random>

using namespace std;

const double MSS = 1.0;            // Segment size
const double RTT = 0.1;            // Round Trip Time = 100 ms
const double SIM_TIME = 20.0;      // 20 seconds simulation

void simulateTCPReno(double lossProb, string filename) {
    ofstream file(filename);

    double cwnd = 1.0;             // Start with 1 MSS
    double ssthresh = 64.0;        // Initial slow-start threshold
    double time = 0.0;

    default_random_engine gen;
    uniform_real_distribution<double> dist(0.0, 1.0);

    double total_data = 0.0;       // For throughput

    file << "time,cwnd\n";

    while (time <= SIM_TIME) {

        // Save cwnd for graphing
        file << time << "," << cwnd << "\n";

        // Simulate sending cwnd packets in this RTT
        for (int i = 0; i < (int)cwnd; i++) {
            if (dist(gen) < lossProb) {
                // PACKET LOSS — Multiplicative Decrease
                ssthresh = cwnd / 2.0;
                cwnd = max(1.0, ssthresh);
            }
        }

        // If no loss occurred ? Update cwnd
        if (cwnd < ssthresh) {
            // SLOW START (exponential)
            cwnd *= 2.0;
        } else {
            // CONGESTION AVOIDANCE (linear increase)
            cwnd += 1.0;
        }

        total_data += cwnd; // For throughput
        time += RTT;
    }

    file.close();

    double avgThroughput = total_data / SIM_TIME;

    cout << "Simulation complete for loss = " << lossProb * 100 << "%\n";
    cout << "Average Throughput = " << avgThroughput << " MSS/second\n\n";
}

int main() {
    simulateTCPReno(0.001, "reno_0.1.csv");   // 0.1% loss
    simulateTCPReno(0.01,  "reno_1.csv");     // 1% loss
    simulateTCPReno(0.02,  "reno_2.csv");     // 2% loss

    cout << "Files generated: reno_0.1.csv, reno_1.csv, reno_2.csv\n";
    return 0;
}

