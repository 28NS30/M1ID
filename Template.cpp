#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//file input output
//jared added this for you :D
using namespace std;
int main()
{
    fstream fout;
    fout.open("data.csv", ios::out);
    fstream fin;
    fin.open("train.csv",ios::in);
    //data collection
    string row,temp,line,col;
    vector<vector<string>> data;
    vector<string> curr;
while (getline(fin,line,'\n')) {
    stringstream s(line);
        // read every column and store it into col
        while (getline(s,col,','))
        {
            // add all the column data into a vector
            if (!col.empty()) {
            curr.push_back(col);
            } else {
curr.push_back("0");
            }
        }
            data.push_back(curr);
            //pushes the vector into a 2d array data
            curr.clear();
        }
}