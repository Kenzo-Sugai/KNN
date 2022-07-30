#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<double>> W;

double Sigmoid(double x){
  return 1.0/(1.0 + exp(-x));
}

double randomWeight(){
  return rand() / double(RAND_MAX);
}

class Network{

  public:

    int layerNumber;
    int X1 {0};
    int X2 {0};
    int Y {0};
    int l_rate = 0.500;
    double Y_hat;
    double Error;
    vector<vector<double>> Z;
    vector<vector<double>> S;
    vector<vector<double>> d;

    Network(){};
    void weight_Initialize();
    void print_Weights();
    void feedFoward();
    void print_Output();
    void backPropagation();
};

void Network::weight_Initialize(){
  int layer = layerNumber - 1;
  W.resize(layerNumber+1);

  for(int i = 0; i < 8; i++){
    W[0].push_back(randomWeight());
  }

  for(int i = 1; i <= layer; i++){
    for(int j = 0; j < 16; j++){
      W[i].push_back(randomWeight());
    }
  }

  for(int i = 0; i < 4; i++){
    W[layer+1].push_back(randomWeight());
  }
}

void Network::print_Weights(){
  for(int i = 0; i < W.size(); i++){
    for(int j = 0; j < W[i].size(); j++){
      cout << W[i][j] << " ";
    }
    cout << endl;
  }
}

void Network::feedFoward(){

  Z.resize(layerNumber+1);
  S.resize(layerNumber+1);
  d.resize(layerNumber+1);

  for(int i = 0; i < 8; i += 2){
    Z[0].push_back(X1 * W[0][i + 0] + X2 * W[0][i + 1]);
    S[0].push_back(Sigmoid(Z[0].back()));
  }

  for(int i = 1; i <= layerNumber - 1; i++){
    for(int j = 0; j < 16; j += 4){
      Z[i].push_back(
        S[i - 1][0] * W[i][j + 0] + S[i - 1][1] * W[i][j + 1] + S[i - 1][2] * W[i][j + 2] + S[i - 1][3] * W[i][j + 3]
        );
      S[i].push_back(Sigmoid(Z[i].back()));
    }
  }

  Z[layerNumber].push_back(
    S[layerNumber - 1][0] * W[layerNumber][0] +
    S[layerNumber - 1][1] * W[layerNumber][1] + 
    S[layerNumber - 1][2] * W[layerNumber][2] +
    S[layerNumber - 1][3] * W[layerNumber][3]);

  Network::Y_hat = Sigmoid(Z[layerNumber][0]);
  Network::Error = (1.0/2.0) * pow(Network::Y_hat - Network::Y, 2);
  
}

void Network::print_Output(){
  cout << "OUTPUT: " << Network::Y_hat << endl;
  cout << "ERROR: " << Network::Error << endl;
}

void Network::backPropagation(){
  
  for(int i = 0; i < 4; i++){
    W[layerNumber][i] -= l_rate * S[layerNumber - 1][i] * Y_hat * (1 - Y_hat) * (Y_hat - Y);
  }

  d[0].push_back(Y_hat * (1 - Y_hat) * (Y_hat * Y));

  for(int i = 1; i <= 1; i++){
    for(int j = 0; j < 16; j++){
      W[layerNumber - i][j] -= l_rate * S[layerNumber - i - 1][j % 4] * S[i][i / 4] * (1 - S[i][i / 4]) * W[layerNumber - i + 1][i / 4] * d[0][0];
      d[1].push_back(S[i][i / 4] * (1 - S[i][i / 4]) * W[layerNumber - i + 1][i / 4] * d[0][0]);
    }
  }

  for(int i = 0, j = 0; i < 8; i += 2, j++){
    W[0][i] -= X1 * S[0][0] * (1 - S[0][0]) * W[1][j + 0] * W[1][j + 4] * W[1][j + 8] * W[1][j + 12] * d[1][i];
    W[0][i + 1] -= X2 * S[0][0] * (1 - S[0][0]) * W[1][j + 0] * W[1][j + 4] * W[1][j + 8] * W[1][j + 12] * d[1][i];
  }
}

int main(){

  // INICIALIZAÇÃO DA CLASSE NETWORK
  Network net;
  net.layerNumber = 2;

  // INICIALIZAÇÃO DOS PESOS
  net.weight_Initialize();
  //net.print_Weights();
  net.feedFoward();
  net.backPropagation();
  net.print_Output();
}
