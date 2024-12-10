#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <random>
#include <ostream>
using namespace std;
double stepSize = 1e-7;
vector<vector<double>> input;
vector<vector<double>> stuff = {{3, 2}, {2, 6}, {5, 6}};
vector<double> trainingY;
vector<double> predicted;
double b = 0;
vector<vector<string>> DATA;
// Initialize a vector with random doubles
int independentVars;
vector<double> initialize(int vars)
{
    vector<double> randomVector(vars); // Resize vector to the required size
    random_device rd;
    mt19937 gen(rd());                               // Fix: mt19937 gen(); is a function declaration, needs to be object initialization
    uniform_real_distribution<double> dis(0.0, 1.0); // Explicitly specify double
                                                     // Range [0.0, 1.0]
    for (int i = 0; i < vars; ++i)
    {
        randomVector[i] = dis(gen);
    }
    return randomVector;
}
vector<double> predict(vector<vector<double>> input, vector<double> coefficients, double bias, double cutoff){
    vector<double> prediction = {};
    for (int i = 0; i < input.size(); i++){
        double cur = 0;
        for (int w = 0; w < coefficients.size(); w++){
            cur += input[i][w] * coefficients[w];
        }
        cur += bias;
        if (cur < cutoff){
            prediction.push_back(0.0);
        }
        else{
            prediction.push_back(1.0);
        }
    }
    return prediction;
}
vector<double> train(vector<double> coefficients, double epochs)
{
    // I'm not sure how the DATA's gonna be formatted but I don't want to find out
    // so I'm just doing this for now.
    for (int i = 0; i < coefficients.size(); i++)
    {
        cout << "Before";
        cout << coefficients[i];
    }
    cout << b;
    cout << endl;
    for (int x = 0; x < epochs; x++)
    {
        vector<double> predicted;
        for (int i = 0; i < input.size(); i++)
        {
            double current = 0;
            for (int g = 0; g < independentVars; g++)
            {
                current += coefficients[g] * input[i][g];
            }
            current += b;
            predicted.push_back(current);
            current = 0;
        }
        // if (x%1000 == 0){
        //     double loss = 0.0;
        //     for (int i = 0; i < trainingY.size(); ++i) {
        //         loss += pow((trainingY[i] - predicted[i]), 2);
        //     }
        //     cout << "MSE: " << loss / trainingY.size() << endl;}

        // Loop for gradient descent-like updates
        for (int weight = 0; weight < independentVars; weight++)
        {
            double loss = 0.0;
            double gradient = 0.0;
            double sum = 0.0;
            for (int DATAPoint = 0; DATAPoint < DATA.size(); DATAPoint++)
            {
                sum += (trainingY[DATAPoint] - predicted[DATAPoint]) * input[DATAPoint][weight];
            }
            gradient = -sum + (0.01 * coefficients[weight]); // Update as needed
            coefficients[weight] -= stepSize * gradient;
        }

        double gradient = 0.0;
        double sum = 0.0;
        for (int DATAPoint = 0; DATAPoint < DATA.size(); DATAPoint++)
        {
            sum += (trainingY[DATAPoint] - predicted[DATAPoint]);
        }
        gradient = -sum; // Update as needed
        b -= stepSize * gradient;

        // https://docs.google.com/document/d/14ry9NPSmFEA3wiCSeEVnyAETmLxW3ImQfHby9SPorpo/edit?usp=sharing
        // Comment with a link
    }
    for (int i = 0; i < coefficients.size(); i++)
    {
        cout << "After";
        cout << coefficients[i];
    }
    cout << endl;
    cout << "B";
    cout << b;
    cout << endl;
    cout << endl;
    return coefficients;
}
vector<vector<string>> getData(string filename)
{
    fstream fin;
    fin.open(filename, ios::in);
    vector<vector<string>> res;
    string row, temp, line, col;
    vector<string> curr;
    while (getline(fin, line, '\n'))
    {
        stringstream s(line);
        // read every column and store it into col
        while (getline(s, col, ','))
        {
            // add all the column DATA into a vector
            if (!col.empty())
            {
                curr.push_back(col);
            }
            else
            {
                curr.push_back("0");
            }
        }
        res.push_back(curr);
        // pushes the vector into a 2d array DATA
        curr.clear();
    }
    return res;
}
void output(vector<double> results, string filename, int startingIndex, string header){
    fstream fout;
    fout.open(filename, ios::out);
    fout << header;
    for (int i = startingIndex; i < startingIndex+results.size(); i++){
        fout << endl << i << "," << results[i-startingIndex];
    }
}

int main()
{
    // INTIALIZING NECESSARY STUFF;
    fstream fout;
    fout.open("results.csv", ios::out);
    DATA = getData("train.csv");
    independentVars = 5;
    // reads the data and puts the desired features into input
    for (int i = 0; i < DATA.size(); i++)
    {
        vector<double> init;
        input.push_back(init);
        input[i].push_back(stod(DATA[i][2]));
        if (DATA[i][4] == "male")
        {
            input[i].push_back(1.0);
            input[i].push_back(stod(DATA[i][2]));
        }
        else
        {
            input[i].push_back(0.0);
            input[i].push_back(0.0);
        }
        double family_size = stod(DATA[i][7]) + stod(DATA[i][6]);  // SibSp + Parch
        input[i].push_back(family_size);
        input[i].push_back(stod(DATA[i][10]));
        trainingY.push_back(stod(DATA[i][1]));
    }
    b = 0;
    // vector<double> coefficients = initialize(independentVars);
    vector<double> coefficients = initialize(independentVars);
    vector<double> final = train(coefficients, 100000);
    vector<double> prediction = predict(input, final, b, 0.46);
    double error = 0;
    for (int i = 0; i < input.size(); i++){
        error += pow(trainingY[i] - prediction[i],2);
    }
    cout << "MSE: " << error/891;
    DATA = getData("test.csv");
    input = {};
    for (int i = 0; i < DATA.size(); i++)
    {
        vector<double> init = {};
        input.push_back(init);
        input[i].push_back(stod(DATA[i][1]));
        if (DATA[i][3] == "male")
        {
            input[i].push_back(1.0);
            input[i].push_back(stod(DATA[i][1]));
        }
        else
        {
            input[i].push_back(0.0);
            input[i].push_back(0.0);
        }
        double family_size = stod(DATA[i][5]) + stod(DATA[i][6]);  // SibSp + Parch
        input[i].push_back(family_size);
        input[i].push_back(stod(DATA[i][9]));
    }
    
    prediction = predict(input, final, b, 0.46);
    output(prediction, "results.csv", 892, "PassengerId,Survived");
    }
