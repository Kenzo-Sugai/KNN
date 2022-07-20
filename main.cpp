#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

double Sigmoid(double x){
  return 1.0/(1.0 + exp(-x));
}

double dSigmoid(double x){
  return 1.0 - Sigmoid(x);
}

vector<double> W{
    0.3, 0.4, 0.5, 0.6, 0.6, 0.7, 0.1,
    0.1, 0.4, 0.7, 0.0, 0.1, 0.1, 0.6,
    0.2, 0.2, 0.0, 0.0, 0.5, 0.2, 0.2,
    0.5, 0.4, 0.3, 0.3, 0.4, 0.0, 0.9,
    0.3, 0.4, 0.5, 0.6, 0.6, 0.7, 0.1,
    0.1, 0.4, 0.7, 0.0, 0.1, 0.1, 0.6,
    0.2, 0.2, 0.0, 0.0, 0.5, 0.2, 0.2,
    0.5, 0.4, 0.3, 0.3, 0.4, 0.1, 0.9,
    0.2, 0.2, 0.0, 0.0, 0.5, 0.2, 0.2,
    0.5, 0.4, 0.3, 0.3, 0.4, 0.1, 0.9
  };

vector<vector<double>> Neuron;
int w {0}, b;
double Output {0}, Error {0}, Z [5];

void Feedfoward(int Layers, int Neurons, vector<int> input){
  Neuron.resize(Layers);
  for(int i = 0; i < Layers; i++){
    Neuron[i].resize(Neurons);
  }
  for(int i = 0; i <= Layers+1; i++){
    if(i == 0){ // Input Layer
      for(int j = 0; j < Neurons; j++){
        for(int k = 0; k < input.size(); k++, w++){
          Neuron[i][j] = input[k] * W[w];
          Z[i] += Neuron[i][j];
          cout << "N[" << i << "][" << j << "] = " << input[k] << " * " << W[w] << " = " << Neuron[i][j] << endl;
        }
        Neuron[i][j] = Sigmoid(Neuron[i][j]);
      }
    }
    if(i > 0 && i < Layers){ // Hidden Layer
      for(int j = 0; j < Neurons; j++){
        for(int k = 0; k < Neurons; k++, w++){
          Neuron[i][j] = Neuron[i-1][k] * W[w];
          Z[i] += Neuron[i][j];
          cout << "N[" << i << "][" << j << "] = " << Neuron[i-1][k] << " * " << W[w] << endl;
        }
        Neuron[i][j] = Sigmoid(Neuron[i][j]);
      }
    }
    if(i == Layers){ // Output Layer
      for(int j = 0; j < Neurons; j++, w++){
        Z[i] += Neuron[i-1][j]*W[w];
        cout << "Z5 = " << Neuron[i-1][j] << " * " << W[w] << endl;
        cout << Z[i] << endl;
      }
      Output = Sigmoid(Z[i]);
    }
  }
}

void Backpropagation(double target){
  b = 43;
  Error = (target - Output);
  cout << "ERROR: " << pow(Error, 2)/2 << endl;
  double d5 = Error*dSigmoid(Z[3]);
  for(int i = 3; i >= 0; i--, b--){
    cout << "W[" << b << "] " << W[b] << " -> ";
    W[b] -= d5*Neuron[2][i];
    cout << W[b] << endl;
  }
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      
    }
  }
}

int main(){
  int n, l, t, value;
  cout << "-- Neural Network --" << endl;
  cout << "1. Input Layer Length: " << endl; cin >> n;
  cout << "2. Number of Layers: " << endl; cin >> l;
  cout << "3. Number of Neurons per Layer: " << endl; cin >> t;

  vector<int> X;

  for(int i = 0; i < n; i++){
    cin >> value;
    X.push_back(value);
  }
  
  Feedfoward(l, t, X);

  cout << Output << endl;

  Backpropagation(1);

}
