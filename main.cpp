#include <iostream>
#include <math.h>
#include <vector>
#include "derivative.hpp"

using namespace std; using namespace d;

double activation_function(double S){
  return 1 / (1 + exp(-S));
}

int main(){


  double n1, n2, v1, v2; // Variaveis [(len array 1), (len array 2), (input 1), (input 2)]

  cin >> n1 >> n2;

  double w;

  vector<double> C1; // Array 1
  vector<double> C2; // Array 2

  vector<vector<double>> W = { // Vetor para guardar os pesos
    {0.3, 0.4, 0.5, 0.6}, // 0[w0, w1, w2, w3]
    {0.6, 0.7, 0.1, 0.1}, // 1[w4, w5, w6, w7]
    {0.4, 0.7, 0.0, 0.1}, // 2[w8, w9, w10, w11] (Sigmoid [first])
    {0.1, 0.6, 0.2, 0.2}, // 3[w12, w13, w14, w15]
    {0.0, 0.0, 0.5, 0.2}, // 4[w16, w17, w18, w19]
    {0.2, 0.5, 0.4, 0.3}, // 5[w20, w21, w22, w23]
    {0.3, 0.4, 0.0, 0.9}, // 6[w24, w25, w26, w27]
    {0.1, 0.6, 0.8, 0.0}, // 7[w28, w29, w30, w31]
  };

  vector<vector<double>> C; 

  C.resize(n1);

  cin >> v1 >> v2; // inputs 1 e 2

  for(int i = 0; i < n1; i++){
    C1.push_back(W[0][i]*v1);
    cout << v1 << " * " << W[0][i] << " = "<< C1[i] << endl;
  }

  cout << endl;

  for(int i = 0; i < n1; i++){
    cout << C1[i] << " + " << v2 << " * " << W[1][i] << " = ";
    C1[i] += W[1][i]*v2;
    cout << C1[i] << endl;
  }

  cout << endl;

  for(int i = 0; i < n1; i++){
    C1[i] = activation_function(C1[i]);
    // cout << S << " + " << C1[i] << " * " << W[2][i] << " = ";
    // S += C1[i]*W[2][i];
    // cout << S << endl;
  }

  C2.resize(n2);

  for(int i = 0; i < n2; i++){
    for(int j = 0; j < n1; j++){
      cout << "C2 " << i << ": " << C2[i] << " + " << C1[i] << " * " << W[i][j] << " = ";
      C2[i] += C1[j]*W[2+i][j];
      cout << C2[i] << endl;
    }
  }

  double S = 0;

  for(int i = 0; i < n2; i++){
    C2[i] = activation_function(C2[i]);
    cout << S << " + " << C2[i] << " * " << W[2][i] << " = ";
    S += C2[i]*W[6][i];
    cout << S << endl;
  }

  S = activation_function(S);
  printf("%.4lf\n", S);

  return 0;

  // S = output
  // E = (S - target)²
  // dE/dw16 = dE/dS
}
