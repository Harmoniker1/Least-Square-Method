// --------------------
// Least Square Method
// 
// Apply least square method to two group of values
// Copyright © 2019 Howard C.
// --------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

// ----------------------------------------
// splitString
// ----------------------------------------

vector<double> splitString(string& str) {
      istringstream iss(str);
      string splitStr;
      vector<double> vecD;
      while (getline(iss, splitStr, ' ')) {
            double splitDouble = stod(splitStr);
            vecD.push_back(splitDouble);
      }
      return vecD;
}

// ----------------------------------------
// bar
// ----------------------------------------

double bar(vector<double> vec) {
      double bar = 0.0;
      for (size_t i = 0; i < vec.size(); ++i)
            bar += vec[i];
      bar /= vec.size();
      return bar;
}

// ----------------------------------------
// squareBar
// ----------------------------------------

double squareBar(vector<double> vec) {
      double squareBar = 0.0;
      for (size_t i = 0; i < vec.size(); ++i)
            squareBar += pow(vec[i], 2);
      squareBar /= vec.size();
      return squareBar;
}

// ----------------------------------------
// barTimesBar
// ----------------------------------------

double barTimesBar(vector<double> vec1, vector<double> vec2) {
      double barTimesBar = 0.0;
      for (size_t i = 0; i < vec1.size(); ++i)
            barTimesBar += vec1[i] * vec2[i];
      barTimesBar /= vec1.size();
      return barTimesBar;
}

// ----------------------------------------
// main
// ----------------------------------------

int main() {
      string indVars, depVars;
      vector<double> indD, depD;

      while (true) {
            cout << "Please input the values of the independent variable (x) one by one, with a space between each two:\n";
            while (getline(cin >> ws, indVars)) {
                  try { indD = splitString(indVars); break; }
                  catch (runtime_error e) { cout << "Wrong input, please try again:\n"; continue; }
            }
            cout << "\nPlease input the values of the dependent variable (y) in the same way:\n";
            while (getline(cin >> ws, depVars)) {
                  try { depD = splitString(depVars); break; }
                  catch (runtime_error e) { cout << "Wrong input, please try again:\n"; continue; }
            }

            if (indD.size() != depD.size()) {
                  cout << "\nTwo group of values aren't of the same amount, please try again from the start.\n";
                  continue;
            }
            else
                  break;
      }

      double indBar, depBar, indDepBar, indSquareBar;
      indBar = bar(indD); depBar = bar(depD); indDepBar = barTimesBar(indD, depD); indSquareBar = squareBar(indD);

      double a1, a0;
      if (indSquareBar - pow(indBar, 2) == 0) {
            cout << "\nThe values of the independent variable are illegal.\n";
            return 1;
      }
      a1 = (indDepBar - indBar * depBar) / (indSquareBar - pow(indBar, 2));
      a0 = depBar - a1 * indBar;

      cout << "\nThe relation between x and y is: y = " << a0 << " + " << a1 << " * x.\n\n";
      cout << setw(15)  << "Actual y" << setw(15) << "Calculated y" << setw(15) << "x" << "\n";
      for (size_t i = 0; i < indD.size(); ++i)
            cout << setw(15) << depD[i] << setw(15) << a0 + a1 * indD[i] << setw(15) << indD[i] << "\n";

      return 0;
}
