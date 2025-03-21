#include <vector>
#include <iostream>
using namespace std;

double B = 4.375e-11;
double G = 0.14;
double D = 1;
double S = 8e9;
double E = 1;
double I = 1;
double  R = 0;
double dt = 1;
vector<vector<double>> res;

int main(){
    while (I >= 1){
        // res.push_back({round(S), round(I), round(R)});
        cout << "S: " << round(S) << "    " <<"E: " << round(E) << "    " << "I: " << round(I) << "    " << "R: " << round(R) << endl;
        double new_S = S - (B * I * S * dt);
        double new_E = E + (B * I * S * dt) - (E * D * dt); 
        double new_I = I + (E * D * dt) - (G * I * dt);
        double new_R = R + (G * I * dt);

        S = new_S;
        E = new_E;
        I = new_I;
        R = new_R;
    }
}