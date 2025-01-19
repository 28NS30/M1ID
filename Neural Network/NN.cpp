#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<vector<double>>> weights = {{{0.2, 0.6}, {0.4, 0.1}}};
vector<vector<double>> biases;

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
int main(){
    // weights;
    biases = {{0}, {0}};
    vector<double> test = forwardPass({0.5, 0.3});
    for (int i; i < test.size(); i++){
        cout<<test[i] << " ";
    }

}