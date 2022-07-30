#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> X1 {0, 0, 1, 1};
vector<int> X2 {0, 1, 0, 1};
vector<int> y = {0, 1, 1, 0};
double l_rate = 0.500;

double Sigmoid(double x){
  return 1/(1 + exp(-x));
}

double randomWeight(){
  return rand() / double(RAND_MAX);
}

vector<vector<double>> W;

int main(){

  // INICIALIZAÇÃO DOS PESOS
  W.resize(2);
  for(int i = 0; i < 8; i++){
    W[0].push_back(randomWeight());
  }
  for(int i = 0; i < 4; i++){
    W[1].push_back(randomWeight());
  }

  // FEEDFOWARD
  for(int i = 0; i < 4; i++){
    vector<vector<double>> Z;
    vector<double> S;
    vector<vector<double>> d;
    Z.resize(2);
    d.resize(2);
    Z[0].push_back(X1[i] * W[0][0] + X2[i] * W[0][1]);
    Z[0].push_back(X1[i] * W[0][2] + X2[i] * W[0][3]);
    Z[0].push_back(X1[i] * W[0][4] + X2[i] * W[0][5]);
    Z[0].push_back(X1[i] * W[0][6] + X2[i] * W[0][7]);

    S.push_back(Sigmoid(Z[0][0]));
    S.push_back(Sigmoid(Z[0][1]));
    S.push_back(Sigmoid(Z[0][2]));
    S.push_back(Sigmoid(Z[0][3]));

    Z[1].push_back(S[0] * W[1][0] + S[1] * W[1][1] + S[2] * W[1][2] + S[3] * W[1][3]);

    double y_hat = Sigmoid(Z[1][0]);
    double E = (1.0/2.0) * pow((y_hat - y[i]), 2);

    cout << "OUTPUT: " << y_hat << endl;
    cout << "ERROR: " << E << endl << endl;

    // BACKPROPAGAtiON
    W[1][0] -= l_rate*S[0]*y_hat*(1 - y_hat)*(y_hat - y[i]);
    W[1][1] -= l_rate*S[1]*y_hat*(1 - y_hat)*(y_hat - y[i]);
    W[1][2] -= l_rate*S[2]*y_hat*(1 - y_hat)*(y_hat - y[i]);
    W[1][3] -= l_rate*S[3]*y_hat*(1 - y_hat)*(y_hat - y[i]);

    d[0].push_back(y_hat*(1 - y_hat)*(y_hat - y[i]));

    W[0][7] -= l_rate*X2[i]*S[4]*(1 - S[4])*W[1][4]*d[0][0];
    W[0][6] -= l_rate*X1[i]*S[4]*(1 - S[4])*W[1][4]*d[0][0];
    W[0][5] -= l_rate*X2[i]*S[4]*(1 - S[3])*W[1][3]*d[0][0];
    W[0][4] -= l_rate*X1[i]*S[4]*(1 - S[3])*W[1][3]*d[0][0];
    W[0][3] -= l_rate*X2[i]*S[4]*(1 - S[2])*W[1][2]*d[0][0];
    W[0][2] -= l_rate*X1[i]*S[4]*(1 - S[2])*W[1][2]*d[0][0];
    W[0][1] -= l_rate*X2[i]*S[4]*(1 - S[1])*W[1][1]*d[0][0];
    W[0][0] -= l_rate*X1[i]*S[4]*(1 - S[1])*W[1][1]*d[0][0];
  }

}
