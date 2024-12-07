#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <random>
#include <ostream>
using namespace std;
double stepSize = 5e-7;
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

vector<double> train(vector<double> coefficients)
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
    for (int x = 0; x < 2000000; x++)
    {
        // cout << x << endl;
        vector<double> predicted;
        for (int i = 0; i < input.size(); i++)
        {
            double current = 0;
            for (int g = 0; g < independentVars; g++)
            {
                current += coefficients[g] * input[i][g];
            }
            current += b;
            predicted.push_back(round(current));
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
            gradient = -sum; // Update as needed
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
// void results()

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
        if (DATA[i][5] == "male")
        {
            input[i].push_back(stod("1"));
        }
        else
        {
            input[i].push_back(stod("0"));
        }
        input[i].push_back(stod(DATA[i][6]));
        input[i].push_back(stod(DATA[i][7]));
        input[i].push_back(stod(DATA[i][8]));
        trainingY.push_back(stod(DATA[i][1]));
    }

    // initialize True Y just for convenience
    // CHANGE THIS WHEN NEEDED

    double cutoff;
    double bestMSE = 99999999;
    b = 0;
    // vector<double> coefficients = initialize(independentVars);
    vector<double> coefficients = {-0.0188993,-0.0690367,0.00114887,-0.00672806-0.0017916};
    vector<double> final = train(coefficients);
    vector<double> predicted;


    // for (int h = 0; h <= 400; h++)
    // {
    //     predicted = {};
    //     for (int i = 0; i < input.size(); i++)
    //     {
    //         double current = 0;
    //         for (int g = 0; g < independentVars; g++)
    //         {
    //             current += final[g] * input[i][g];
    //         }
    //         current += b;
    //         if (current < h/100){
    //             predicted.push_back(stod("0"));
    //         }
    //         else{
    //             predicted.push_back(stod("1"));
    //         }
    //         current = 0;
    //     }
    //     double loss = 0.0;
    //     for (int i = 0; i < trainingY.size(); ++i)
    //     {
    //         loss += pow((trainingY[i] - predicted[i]), 2);
    //     }
    //     if (loss/trainingY.size() < bestMSE){
    //         bestMSE = loss/trainingY.size();
    //         cutoff = h/100;
    //     }
    // }
    // cout << "done" << endl;
    // cout << cutoff << endl;
    // cout << bestMSE;

    vector<vector<string>> test;
    fstream fin;
    fin.open("test.csv", ios::in);
    // DATA collection
    string row, temp, line, col;
    vector<string> curr;
    row = "";
    temp = "";
    line = "";
    col = "";
    curr = {};
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
        test.push_back(curr);
        // pushes the vector into a 2d array DATA
        curr.clear();
    }
    input = {};
    trainingY = {};
    // Put desired features into input
    for (int i = 0; i < test.size(); i++)
    {
        vector<double> init;
        input.push_back(init);
        input[i].push_back(stod(test[i][2]));
        if (test[i][5] == "male")
        {
            input[i].push_back(stod("1"));
        }
        else
        {
            input[i].push_back(stod("0"));
        }
        input[i].push_back(stod(test[i][6]));
        input[i].push_back(stod(test[i][7]));
        input[i].push_back(stod(test[i][8]));
        trainingY.push_back(stod(test[i][1]));
    }
    // getting the predictions
    predicted = {};
    for (int i = 0; i < input.size(); i++)
    {
        double current = 0;
        for (int g = 0; g < independentVars; g++)
        {
            current += final[g] * input[i][g];
        }
        current += b;
        if (current < 1){
            predicted.push_back(stod("0"));
        }
        else{
            predicted.push_back(stod("1"));
        }
        current = 0;
    }
    fout << "PassengerId,Survived";
    for (int i = 892; i <= 1309; i++){
        fout << endl;
        fout << i << "," << predicted[i-892];
    }

    return 0;
}
// After-0.143853After-0.50356After-0.00171229After-0.0336938After0.000439125