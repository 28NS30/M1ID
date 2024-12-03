#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <random>
#include <ostream>
using namespace std;
double stepSize = 0.1;
vector <vector<double>> input;
vector<vector <double>> stuff = {{3, 2}, {2, 6}, {5, 6}};
vector<double> trainingY;
vector<double> predicted;
double b = 0;
vector<vector<string>> DATA;
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
    // I'm not sure how the DATA's gonna be formatted but I don't want to find out
    // so I'm just doing this for now.
    vector<double> coefficients = initialize(independentVars);  
    for (int i =0; i < coefficients.size(); i++){
        cout << "Before";
        cout << coefficients[i];
    }
    cout << b;
    cout << endl;
    vector<double> predicted;
    for (int x = 0; x < 100000; x++){
        stepSize = 0.001;
        for (int i = 0; i<input.size(); i++){
            double current = 0;
            for (int g = 0; g<independentVars; g++){
                current += coefficients[g]*input[i][g];
            }
            current += b;
            predicted.push_back(current);
            current = 0;
        }
        // Loop for gradient descent-like updates
        for (int weight = 0; weight < independentVars; weight++) {
            double gradient = 0.0;
            double sum = 0.0;
            for (int DATAPoint = 0; DATAPoint <DATA.size(); DATAPoint++) {
                sum += (trainingY[DATAPoint] - predicted[DATAPoint]) * input[DATAPoint][weight];
            }
            gradient = -sum; // Update as needed
            cout << gradient;
            cout << endl;
            coefficients[weight] -= stepSize * gradient;}
        double gradient = 0.0;
        double sum = 0.0;
        for (int DATAPoint = 0; DATAPoint <DATA.size(); DATAPoint++) {
            sum += (trainingY[DATAPoint] - predicted[DATAPoint]);
        }
        gradient = -sum; // Update as needed
        b-= stepSize * gradient;

            // https://docs.google.com/document/d/14ry9NPSmFEA3wiCSeEVnyAETmLxW3ImQfHby9SPorpo/edit?usp=sharing
            // Comment with a link
    }
    for (int i =0; i < coefficients.size(); i++){
        cout << "After";
        cout << coefficients[i];
    }
    cout << endl;
    cout << "B";
    cout << b;
    cout << endl;
    cout << endl;
}
int main() {
    // Getting the DATA
    // 2 d array in the form PassengerId
    fstream fout;
    fout.open("results.csv", ios::out);
    fstream fin;
    fin.open("train.csv",ios::in);
    //DATA collection
    string row,temp,line,col;
    vector<string> curr;
while (getline(fin,line,'\n')) {
    stringstream s(line);
        // read every column and store it into col
        while (getline(s,col,','))
        {
            // add all the column DATA into a vector
            if (!col.empty()) {
            curr.push_back(col);
            } else {
curr.push_back("0");
            }
        }
            DATA.push_back(curr);
            //pushes the vector into a 2d array DATA
            curr.clear();
        }
    
    
    
    
    
    
    
    
    // Survived Pclass Name Sex Age SibSp Parch Ticket Fare
    for (int i = 0; i< DATA.size(); i++){
        vector<double> init;
        input.push_back(init);
        input[i].push_back(stod(DATA[i][2]));
        if (DATA[i][5] == "male"){
            input[i].push_back(stod("1"));
        }
        else{
            input[i].push_back(stod("0"));
        }
        input[i].push_back(stod(DATA[i][6]));
        input[i].push_back(stod(DATA[i][7]));
        input[i].push_back(stod(DATA[i][8]));
        trainingY.push_back(stod(DATA[i][1]));
    }

    // initialize True Y just for convenience
    // CHANGE THIS WHEN NEEDED
    
    independentVars = 5;
    train();
    return 0;
}   