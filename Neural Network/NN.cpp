#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<vector<double>>> weights = {{{0.2, 0.6}, {0.4, 0.1}}};
vector<vector<double>> biases;
int epochs = 1;
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}
vector<double> forwardPass(vector<double>input){
    vector<double> newVector;
    double cur;
    for (int layer = 0; layer < weights.size(); layer ++){
        for (int node = 0; node < weights[layer].size(); node++){
            cur = 0;
            for (int i = 0; i <input.size(); i++){
                cur += input[i]*weights[layer][node][i];
            }
            cur += biases[layer][node];
            cur = sigmoid(cur);
            newVector.push_back(cur);
        }
        input = newVector;
        newVector = {};
    }
    return input;
}

void train(vector<vector<double>>inputs, vector<double> trueYs){
    vector<vector<double>> dError; //derivative of the error with respect to the pre-actavtion weighted sum of a node
    // OUTPUT LAYER
    vector<vector<double>> predictions;
    for(auto tc: inputs){
        predictions.push_back(forwardPass(tc));
    }
    // OUTPUT LAYER
    for (int epoch = 0; epoch < epochs; epoch++){
        // Runs for set number of epochs/training cycle
        for (int dataPoint = 0; dataPoint < predictions.size(); dataPoint++){
            // Stochastic GD -> updates every data point
            for (int layer = weights.size()-1; layer>=0; layer--){
                // Calculate Gradient
                // Gradient = Derivative of the Loss with respect to the preactivation output of the layer
                for (int node = 0; node < weights[layer].size(); node++){
                    for (int weight = 0; weight < weights[layer][weight].size(); weight++){
                        // Update Weight
                    }

                    // Update Bias
                }
            }
        }
    }
}
int main(){
    // weights;
    biases = {{0}, {0}};
    vector<double> test = forwardPass({0.5, 0.3});
    for (int i; i < test.size(); i++){
        cout<<test[i] << " ";
    }

}