#include <vector>
#include <iostream>
using namespace std;

double B = 4.375e-11;
double G = 0.14;
double S = 8e9;
double I = 1;
double  R = 0;
double dt = 1;
vector<vector<double>> res;

int main(){
    while (I >= 1){
        // res.push_back({round(S), round(I), round(R)});
        cout << "S: " << round(S) << "    " << "I: " << round(I) << "    " << "R: " << round(R) << endl;
        double new_S = S - B * I * S * dt;
        double new_I = I + B * I * S * dt - G * I* dt;
        double new_R = R + G * I * dt;

        S = new_S;
        I = new_I;
        R = new_R;

    }
}