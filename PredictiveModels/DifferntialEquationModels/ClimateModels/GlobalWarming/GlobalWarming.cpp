#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
double curTemp = 15.25;
double curCO2 = 424.61;
double futureCO2 = 424.61;
double futureTemp;
double CO2rate = 6;
double year = 2024;

int main(){
    for (int i = 0; i < 50; i++){
        futureCO2 += i*CO2rate;
        futureTemp = curTemp + 3 * log2(futureCO2/curCO2);
        cout << "Year: " << year+i << endl << "Temperature: " << futureTemp << endl;
    }
}