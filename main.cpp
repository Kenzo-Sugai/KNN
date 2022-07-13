#include <iostream>
#include <math.h>
#include <vector>
#include "random.hpp"
#include "neuron.hpp"

using namespace std; using namespace rad;

double dE;

vector<double> W{
    0.3, 0.4, 0.5, 0.6, 0.6, 0.7, 0.1,
    0.1, 0.4, 0.7, 0.0, 0.1, 0.1, 0.6,
    0.2, 0.2, 0.0, 0.0, 0.5, 0.2, 0.2,
    0.5, 0.4, 0.3, 0.3, 0.4, 0.0, 0.9
  };

vector<double> C1; // Array 1
vector<double> C2(4); // Array 2

double activation_function(double S){
  return 1 / (1 + exp(-S));
}

double delta1(double S){
  return dE*(1-activation_function(S));
}

double delta2(double delta1, int i){
  return delta1*(1-activation_function(C2[i]));
}

double delta3(double delta2, int i){
  return delta2*(1-activation_function(C1[i]));
}

int main(){
  int N = 1;
  double target = 0;
  double n1 = 4, n2 = 4, v1, v2; // Variaveis [(len array 1), (len array 2), (input 1), (input 2)]

  double w, Wi = 0;

  cin >> v1 >> v2; // inputs 1 e 2

  double input[2] {v1, v2};

  while(N--){
    Wi = 0; // reset indice do peso
    for(int i = 0; i < 4; i++, Wi++){
      cout << v1 << " -> " << Wi+1 << " -> " << "C1[" << i << "]" << endl;
      C1.push_back(W[Wi]*v1); Wi++;
      cout << v2 << " -> " << Wi+1 << " -> " << "C1[" << i << "]" << endl;
      C1[i] += W[Wi]*v2;
    }

    cout << endl; 

    for(int i = 0; i < 4; i++){
      C1[i] = activation_function(C1[i]);
    }

    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++, Wi++){
        cout << "C1[" << j << "]" << " -> " << Wi+1 << " -> " << "C2[" << i << "]" << endl;
        C2[i] += C1[j]*W[Wi];
      }
    }

    double S = 0;

    cout << endl;

    for(int i = 0; i < n2; i++, Wi++){
      C2[i] = activation_function(C2[i]);
      cout << "C2[" << i << "]" << " -> " << Wi+1 << " -> S" << endl;
      S += C2[i]*W[Wi];
    }

    S = activation_function(S);
    cout << endl;
    printf("OUTPUT: %.4lf\n", S);
    double ERROR = (1.0/2.0)*pow(target-S, 2);
    printf("ERROR: %.4lf %.2lf%%\n\n", ERROR, ERROR*100);

    dE = S*(target-S);

    cout << "w27: " << W[27] << " -> ";
    
    W[27] -= delta1(S)*C2[3];

    cout << W[27] << endl;
    cout << "w26: " << W[26] << " -> ";

    W[26] -= delta1(S)*C2[2];

    cout << W[26] << endl;
    cout << "w25: " << W[25] << " -> ";

    W[25] -= delta1(S)*C2[1];

    cout << W[25] << endl;
    cout << "w24: " << W[24] << " -> ";

    W[24] -= delta1(S)*C2[0];

    cout << W[24] << endl;

    int t = 0;
    for(int i = 0; i < 4; i++){
      for(int j = 3; j >= 0; j--, t++){
        cout << "w" << 23-t << ": " << W[23-t] << " -> ";
        W[23-t] -= delta2(delta1(S), i)*W[27-i]*C1[j];
        cout << W[23-t] << endl;
      }
    }

    int k = 1;
    for(int i = 0; i < 4; i++){
      for(int j = 0, p = 0; j < 8; j+=4, t++, p++){
        //cout << j << " - " << 23-i-j << endl;
        cout << "w" << 23-t << ": " << W[23-t] << " -> ";
        W[23-t] -= delta3(delta2(delta1(S), i), p)*W[23-i-j]*input[k];
        cout << W[23-t] << endl;
        //cout << k << endl;
        if(k == 0)
          k = 1;
        else if(k == 1){
          k = 0;
        }
      }
    }
  }
}
