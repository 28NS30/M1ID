#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <random>
using namespace std;

int stepSize = 1;

// Initialize a vector with random doubles
vector<double> initialize(int vars) {
    vector<double> randomVector(vars); // Resize vector to the required size
    random_device rd;
    mt19937 gen(rd()); // Fix: mt19937 gen(); is a function declaration, needs to be object initialization
    uniform_real_distribution<double> dis(0.0, 1.0);  // Explicitly specify double
 // Range [0.0, 1.0]
    for (int i = 0; i < vars; ++i) {
        randomVector[i] = dis(gen);
    }
    return randomVector;
}

int main() {
    // Test the initialize function
    vector<double> x = initialize(5);
    
    // Print the elements of the vector
    for (const auto& value : x) {
        cout << value << " ";
    }
    cout << endl;
    return 0;
}
void train() {
    vector<double> data;
    vector<double> trainingY;
    vector<double> predicted;
    vector<vector<double>> input;
    // I'm not sure how the data's gonna be formatted but I don't want to find out
    // so I'm just doing this for now.
    int independentVars;
    cin >> independentVars;
    vector<double> coefficients = initialize(independentVars);

    // Loop for gradient descent-like updates
    for (int weight = 0; weight < independentVars; weight++) {
        double gradient = 0.0;
        double sum = 0.0;
        for (int dataPoint = 0; dataPoint < data.size(); dataPoint++) {
            sum += (trainingY[dataPoint] - predicted[dataPoint]) * input[dataPoint][weight];
        }
        // Example: Calculate gradient (you may need a proper formula here)
        gradient = -sum; // Update as needed
        coefficients[weight] -= stepSize * gradient;

        // https://docs.google.com/document/d/14ry9NPSmFEA3wiCSeEVnyAETmLxW3ImQfHby9SPorpo/edit?usp=sharing
        // Comment with a link
    }
}