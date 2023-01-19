#include <iostream>
#include <stdio.h>
#include <random>

using namespace std;

double bin1;
double bin2;
double bin3;
double bin4;
double notInAnyBin;
double bin1Percentage;
double bin2Percentage;
double bin3Percentage;
double bin4Percentage;
double maxLatency = 0;
double frequency;

// This function calculates the frequencies of each bin
void computeBins(double mu, double sigma) {
    bin1 = 1 / (mu + 8 * sigma);
    bin2 = 1 / (mu + 4 * sigma);
    bin3 = 1 / (mu + 2 * sigma);
    bin4 = 1 / (mu + sigma);
}

// This function creates our normal distribution curve, determines the max latency of each processor
// and then calculates the frequency of said processor. Afterwards, one of five counters increases
// which will determine the number of processors in each bin. Finally, we calculate the percentage of processors
// in each bin.
void normalDistribution(double mu, double sigma, int random_seed, int numCriticalPaths, int numProcessors) {
    double bin[5] = {};
    default_random_engine generator (random_seed);
    normal_distribution<double> distribution (mu, sigma);

    for (int n = 0; n < numProcessors; n++) {
        maxLatency = 0;

        for (int i = 0; i < numCriticalPaths; i++) {
            double number = distribution(generator);
            if (number > maxLatency) {
                maxLatency = number;
            }
        }

        frequency = 1 / maxLatency;

        if (frequency < bin1) {
            bin[0]++;
        } else if (frequency >= bin1 && frequency < bin2) {
            bin[1]++;
        } else if (frequency >= bin2 && frequency < bin3) {
            bin[2]++;
        } else if (frequency >= bin3 && frequency < bin4) {
            bin[3]++;
        } else if (frequency >= bin4) {
            bin[4]++;
        }
    }

    notInAnyBin = (bin[0] / numProcessors) * 100;
    bin1Percentage = (bin[1] / numProcessors) * 100;
    bin2Percentage = (bin[2] / numProcessors) * 100;
    bin3Percentage = (bin[3] / numProcessors) * 100;
    bin4Percentage = (bin[4] / numProcessors) * 100;
}

// This function prints the percentage of processors that are in each bin and those that
// are not in any bin.
void printSimulation() {
    printf("Frequency bin 1 (Frequency %.2f GHz): %.4f%%\n", bin1, bin1Percentage);
    printf("Frequency bin 2 (Frequency %.2f GHz): %.4f%%\n", bin2, bin2Percentage);
    printf("Frequency bin 3 (Frequency %.2f GHz): %.4f%%\n", bin3, bin3Percentage);
    printf("Frequency bin 4 (Frequency %.2f GHz): %.4f%%\n", bin4, bin4Percentage);
    printf("Unclassified processors (Frequency less than bin 1's %.2f GHz): %.4f%%\n", bin1, notInAnyBin);
}

int main(int argc, char* argv[]) {

    if (argc >= 6) {
        int numProcessors = atoi(argv[1]);
        int numCriticalPaths = atoi(argv[2]);
        double mu = atof(argv[3]);
        double sigma = atof(argv[4]);
        int random_seed = atoi(argv[5]);

        // Add error checks for input variables here, exit if incorrect input
        if (numProcessors <= 0) {
            printf("Lambda must not be negative!\n");
            return -1;
        }
        if (numCriticalPaths <= 0) {
            printf("Mu must not be negative!\n");
            return -1;
        }
        if (mu <= 0) {
            printf("The period must be positive!\n");
            return -1;
        }
        if (sigma <= 0) {
            printf("Total departures must be a positive number!\n");
            return -1;
        }

        // If there are no input errors then we compute the Bins using the given assignment formulas
        computeBins(mu, sigma);

        printf("Running %d simulations for processors with %d critical paths with distribution on N(%f, %f), Random seed %d\n", numProcessors, numCriticalPaths, mu, sigma, random_seed);
        printf("Output Histogram\n");

        // Start Monte Carlo simulation
        normalDistribution(mu, sigma, random_seed, numCriticalPaths, numProcessors);
        printSimulation();

    } else {
        printf("Insufficient number of arguments provided!\n");
        return -1;
    }


    return 0;
}