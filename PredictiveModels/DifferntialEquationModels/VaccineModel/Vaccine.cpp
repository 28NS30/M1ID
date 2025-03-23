#include <vector>
#include <iostream>
using namespace std;

double B = 4.375e-11;
double G = 0.14;
double S = 8e9;
double I = 1;
double R = 0;
double V = 0;
double D = 0.0005;
double dt = 1;
double efficacy = 0.9;
vector<vector<double>> res;
int cur = 0;
int main(){
    while (I >= 1){
        // res.push_back({round(S), round(I), round(R)});
        cout << cur << "    " << "V: " << V << "    " << "S: " << round(S) << "    " << "I: " << round(I) << "    " << "R: " << round(R) << endl;
        double new_V = V + efficacy * S * D * dt;
        double new_S = S - B * I * S * dt - efficacy * S * D * dt;
        double new_I = I + B * I * S * dt - G * I * dt;
        double new_R = R + G * I * dt;
        cur += 1;
        V = new_V;
        S = new_S;
        I = new_I;
        R = new_R;

    }
}