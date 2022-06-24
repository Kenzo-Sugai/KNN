#include <iostream>
#include <math.h>
#include <vector>
#include "random.hpp"

using namespace std; using namespace rad;

double activation_function(double S){
  return 1 / (1 + exp(-S));
}

vector<double> W{
    0.3, 0.4, 0.5, 0.6, 0.6, 0.7, 0.1,
    0.1, 0.4, 0.7, 0.0, 0.1, 0.1, 0.6,
    0.2, 0.2, 0.0, 0.0, 0.5, 0.2, 0.2,
    0.5, 0.4, 0.3, 0.3, 0.4, 0.0, 0.9
  };

vector<double> C1; // Array 1
vector<double> C2(4); // Array 2

int main(){
  int N = 4;
  double target = 0;
  double n1 = 4, n2 = 4, v1, v2; // Variaveis [(len array 1), (len array 2), (input 1), (input 2)]

  double w, Wi = 0;

  cin >> v1 >> v2; // inputs 1 e 2

  while(N--){
    Wi = 0;
    for(int i = 0; i < 4; i++, Wi++){
      C1.push_back(W[Wi]*v1);
      cout << v1 << " * " << W[Wi] << " = "<< C1[i] << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++, Wi++){
      cout << C1[i] << " + " << v2 << " * " << W[Wi] << " = ";
      C1[i] += W[Wi]*v2;
      cout << C1[i] << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++){
      C1[i] = activation_function(C1[i]);
      // cout << S << " + " << C1[i] << " * " << W[2][i] << " = ";
      // S += C1[i]*W[2][i];
      // cout << S << endl;
    }

    for(int i = 0; i < 4; i++){
      for(int j = 0; j < n1; j++, Wi++){
        cout << "C2 " << i << ": " << C2[i] << " + " << C1[j] << " * " << W[Wi] << " = ";
        C2[i] += C1[j]*W[Wi];
        cout << C2[i] << endl;
      }
    }

    double S = 0;

    for(int i = 0; i < n2; i++, Wi++){
      C2[i] = activation_function(C2[i]);
      cout << S << " + " << C2[i] << " * " << W[Wi] << " = ";
      S += C2[i]*W[Wi];
      cout << S << endl;
    }

    S = activation_function(S);
    cout << endl;
    printf("OUTPUT: %.4lf\n", S);
    double ERROR = pow(target-S, 2);
    printf("ERROR: %.4lf\n", ERROR);

    double dE = S*(target-S);

    double delta1 = dE*(1-activation_function(S));

    W[27] = delta1*C2[3];
    W[26] = delta1*C2[2];
    W[25] = delta1*C2[1];
    W[24] = delta1*C2[0];

  }
}
