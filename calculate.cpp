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
// xyBar
// ----------------------------------------

double xyBar(vector<double> vec1, vector<double> vec2) {
      double xyBar = 0.0;
      for (size_t i = 0; i < vec1.size(); ++i)
            xyBar += vec1[i] * vec2[i];
      xyBar /= vec1.size();
      return xyBar;
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
                  catch (invalid_argument e) { cout << "\nWrong input, please try again.\nMake sure there's only one space between two elements.\n"; continue; }
            }
            cout << "\nPlease input the values of the dependent variable (y) in the same way:\n";
            while (getline(cin >> ws, depVars)) {
                  try { depD = splitString(depVars); break; }
                  catch (invalid_argument e) { cout << "\nWrong input, please try again.\nMake sure there's only one space between two elements.\n"; continue; }
            }

            if (indD.size() != depD.size()) {
                  cout << "\nTwo group of values aren't of the same amount, please try again from the start.\n";
                  continue;
            }
            if (indD.size() == 1) {
                  cout << "\nOne pair of values isn't enough to define a line, please try again from the start.\n";
                  continue;
            }
            else
                  break;
      }

      double indBar, depBar, indDepBar, indSquareBar, depSquareBar;
      indBar = bar(indD); depBar = bar(depD); indDepBar = xyBar(indD, depD); indSquareBar = squareBar(indD); depSquareBar = squareBar(depD);

      double a1, a0;
      if (indSquareBar - pow(indBar, 2) == 0) {
            cout << "\nThe values of the independent variable are illegal.\n";
            return 1;
      }
      a1 = (indDepBar - indBar * depBar) / (indSquareBar - pow(indBar, 2));
      a0 = depBar - a1 * indBar;

      if (a1 >= 0)
            cout << "\nThe relation between x and y is: y = " << a0 << " + " << a1 << " * x.\n\n";
      else
            cout << "\nThe relation between x and y is: y = " << a0 << " - " << - a1 << " * x.\n\n";

      cout << setw(15)  << "Actual y" << setw(15) << "Calculated y" << setw(15) << "x" << "\n";
      for (size_t i = 0; i < indD.size(); ++i)
            cout << setw(15) << depD[i] << setw(15) << a0 + a1 * indD[i] << setw(15) << indD[i] << "\n";

      // coefficient of correlation
      double coc = (indDepBar - indBar * depBar) / sqrt((indSquareBar - pow(indBar, 2)) * (depSquareBar - pow(depBar, 2)));
      // uncertainty of a1
      double uncertainty = a1 * sqrt((1 / pow(coc, 2) - 1) / (indD.size() - 2));

      cout << "\nThe uncertainty of the scope is " << uncertainty << ".\n";

      return 0;
}
