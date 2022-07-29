#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>

using namespace std;

double Sigmoid(double x){
  return 1.0/(1.0 + exp(-x));
}

double dSigmoid(double x){
  return 1.0 - Sigmoid(x);
}

vector<vector<double>> W;

double randomWeight(){
  return rand() / double(RAND_MAX);
}

vector<vector<double>> Neuron;
int w {0}, b;
double Output {0}, Error {0}, Z [5];

void Feedfoward(int Layers, int Neurons, vector<int> input){
  Neuron.resize(Layers);
  for(int i = 0; i < Layers; i++){
    Neuron[i].resize(Neurons);
  }
  W.resize(Layers+1);
  for(int layer = 0; layer < Layers+1; layer++){
    //cout << layer << endl;
    if(layer == 0){
      for(int n = 0; n < Neurons; n++){
        for(int t = 0; t < input.size(); t++){
          W[layer].push_back(randomWeight());
          //cout << W[layer][W[layer].size()-1] << " ";
        }
      }
      //cout << endl;
    }
    else if(layer > 0 && layer < Layers){
      for(int n = 0; n < Neurons; n++){
        for(int t = 0; t < Neurons; t++){
          W[layer].push_back(randomWeight());
          //cout << W[layer][W[layer].size()-1] << " ";
        }
        //cout << endl;
      }
    }
    else{
      for(int n = 0; n < 4; n++){
        W[layer].push_back(randomWeight());
        //cout << W[layer][n] << " ";
      }
      //cout << endl;
    }

  }
  for(int i = 0; i <= Layers+1; i++){
    if(i == 0){ // Input Layer
      w = 0;
      for(int j = 0; j < Neurons; j++){
        for(int k = 0; k < input.size(); k++, w++){
          Neuron[i][j] = input[k] * W[i][w];
          Z[i] += Neuron[i][j];
          //cout << "N[" << i << "][" << j << "] = " << input[k] << " * " << W[i][w] << " = " << Neuron[i][j] << endl;
        }
        Neuron[i][j] = Sigmoid(Neuron[i][j]);
      }
    }
    if(i > 0 && i < Layers){ // Hidden Layer
      w = 0;
      for(int j = 0; j < Neurons; j++){
        for(int k = 0; k < Neurons; k++, w++){
          Neuron[i][j] = Neuron[i-1][k] * W[i][w];
          Z[i] += Neuron[i][j];
          //cout << "N[" << i << "][" << j << "] = " << Neuron[i-1][k] << " * " << W[i][w] << endl;
        }
        Neuron[i][j] = Sigmoid(Neuron[i][j]);
      }
    }
    if(i == Layers){ // Output Layer
      for(int j = 0; j < Neurons; j++){
        Z[i] += Neuron[i-1][j]*W[i][j];
        //cout << "Z5 = " << Neuron[i-1][j] << " * " << W[i][j] << endl;
        //cout << Z[i] << endl;
      }
      Output = Sigmoid(Z[i]);
    }
  }
}

void Backpropagation(double target, vector<int> &input){
  w = 0;
  Error = (target - Output);
  cout << "ERROR: " << std::abs(Error) << endl;
  double d4 = Error*dSigmoid(Z[3])*Output;
  double d3 = d4*dSigmoid(Z[2]);
  double d2 = d3*dSigmoid(Z[1]);
  double d1 = d2*dSigmoid(Z[0]);
  double d[4] = {d4, d3, d2, d1};

  for(int i = 3; i >= 0; i--){
    //cout << W[3][i] << " -> ";
    W[3][i] -= d[0]*Neuron[2][i];
    //cout << W[3][i] << endl;
  }

  for(int i = 0; i <= 1; i++){
    w = W[2-i].size()-1;
    for(int j = 0; j < W[2-i].size(); j++, w--){
      //cout << W[2-i][w] << " -> ";
      W[2-i][w] -= d[1+i]*W[2-i][w];
      //cout << W[2-i][w] << endl;
    }
  }
  w = W[0].size() - 1;
  for(int i = 0; i < W[0].size()/2; i++){
    for(int j = 0; j <= 1; j++, w--){
      //cout << W[0][w] << " -> ";
      W[0][w] -= d[3]*input[j];
      //cout << W[0][w] << endl;
    }
  }
}

int main(){
  int n, l, t, value, T = 1;

  vector<vector<int>> X {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  vector<double> Y {0, 1, 1, 0};
  int layerNumber = 3;
  int NeuronlayerNumber = 4;
  for(int i = 0; i < X.size(); i++){
    Feedfoward(layerNumber, NeuronlayerNumber, X[i]);

    cout << Output << endl;
    
    Backpropagation(Y[i], X[i]);
  }
}
