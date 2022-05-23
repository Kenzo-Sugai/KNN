#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

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
    {0.3, 0.4, 0.5, 0.6}, // W1
    {0.6, 0.7, 0.1, 0.1}, // W2
    {0.4, 0.7, 0.0, 0.1}, // W3 (Sigmoid [first])
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

  double S = 0;

  for(int i = 0; i < n2; i++){
    C2.push_back(C1[i]*W[2][i]);
  }

  for(int i = 0; i < n1; i++){
    C1[i] = activation_function(C1[i]);
    cout << S << " + " << C1[i] << " * " << W[2][i] << " = ";
    S += C1[i]*W[2][i];
    cout << S << endl;
  }

  S = activation_function(S);
  printf("%.4lf\n", S);



  // for(int i = 0; i < n1; i++){
  //   for(int j = 0; j < n2; j++){
  //     if(i == 0){
  //       C2[j] = 0;
  //     }
  //     cin >> w;
  //     W.push_back(w);
  //     C2[j] += w*C1[i];
  //     C2[j] = 1/(1 + exp(-C2[j]));
  //   }
  // }
  // double S = 0;
  // for(int i = 0; i < n2; i++){
  //   cin >> w;
  //   W.push_back(w);
  //   S += C2[i]*w;
  // }

  // S = 1/(1 + exp(-S));
  // cout << "S = " << S << endl;

  // S = output
  // E = (S - target)²
  // dE/dw16 = dE/dS
}
