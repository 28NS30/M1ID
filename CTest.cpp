#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <random>
using namespace std;

double stepSize = 0.1;
vector<vector <double>> stuff = {{1, 2}, {2, 4}, {3, 6}};
vector<double> trainingY = {2, 4, 6};
vector<double> predicted;
vector<vector<double>> input = {{1}, {2}, {3}};
// Initialize a vector with random doubles
int independentVars;
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

void train() {
    // I'm not sure how the data's gonna be formatted but I don't want to find out
    // so I'm just doing this for now.
    vector<double> coefficients = initialize(independentVars);  
    for (int i =0; i < coefficients.size(); i++){
        cout << "Before";
        cout << coefficients[i];
    }
    cout << endl;
    vector<double> predicted;
    for (int i = 0; i<input.size(); i++){
        double current = 0;
        for (int g = 0; g<independentVars; g++){
            current += coefficients[g]*input[i][g];
        }
        predicted.push_back(current);
        current = 0;
    }
    // Loop for gradient descent-like updates
    for (int weight = 0; weight < independentVars; weight++) {
        double gradient = 0.0;
        double sum = 0.0;
        for (int dataPoint = 0; dataPoint <stuff.size(); dataPoint++) {
            sum += (trainingY[dataPoint] - predicted[dataPoint]) * input[dataPoint][weight];
        }
        // Example: Calculate gradient (you may need a proper formula here)
        gradient = -2*sum/independentVars; // Update as needed
        cout << gradient;
        cout << endl;
        coefficients[weight] -= stepSize * gradient;

        // https://docs.google.com/document/d/14ry9NPSmFEA3wiCSeEVnyAETmLxW3ImQfHby9SPorpo/edit?usp=sharing
        // Comment with a link
    }
    for (int i =0; i < coefficients.size(); i++){
        cout << "After";
        cout << coefficients[i];
    }
    cout << endl;
}
int main() {
    cin >> independentVars;
    train();
    return 0;
}