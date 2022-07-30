#include <iostream>
#include <vector>
#include <cmath>

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
  W.resize(3);
  for(int i = 0; i < 8; i++){
    W[0].push_back(randomWeight());
  }
  for(int i = 0; i < 16; i++){
    W[1].push_back(randomWeight());
  }
  for(int i = 0; i < 4; i++){
    W[2].push_back(randomWeight());
  }

  // FEEDFOWARD
  for(int i = 0; i < 4; i++){

    vector<vector<double>> Z;
    vector<vector<double>> S;
    vector<vector<double>> d;

    Z.resize(3);
    S.resize(3);
    d.resize(3);

    Z[0].push_back((X1[i] * W[0][1]) + (X2[i] * W[0][1]));
    Z[0].push_back((X1[i] * W[0][2]) + (X2[i] * W[0][3]));
    Z[0].push_back((X1[i] * W[0][4]) + (X2[i] * W[0][5]));
    Z[0].push_back((X1[i] * W[0][6]) + (X2[i] * W[0][7]));

    S[0].push_back(Sigmoid(Z[0][0]));
    S[0].push_back(Sigmoid(Z[0][1]));
    S[0].push_back(Sigmoid(Z[0][2]));
    S[0].push_back(Sigmoid(Z[0][3]));

    Z[1].push_back(
      (S[0][0] * W[1][0]) + (S[0][1] * W[1][1]) + (S[0][2] * W[1][2]) + (S[0][3] * W[1][3])
    );
    Z[1].push_back(
      S[0][0] * W[1][4] + S[0][1] * W[1][5] + S[0][2] * W[1][6] + S[0][3] * W[1][7]
    );
    Z[1].push_back(
      S[0][0] * W[1][8] + S[0][1] * W[1][9] + S[0][2] * W[1][10] + S[0][3] * W[1][11]
    );
    Z[1].push_back(
      S[0][0] * W[1][12] + S[0][1] * W[1][13] + S[0][2] * W[1][14] + S[0][3] * W[1][15]
    );

    S[1].push_back(Sigmoid(Z[1][0]));
    S[1].push_back(Sigmoid(Z[1][1]));
    S[1].push_back(Sigmoid(Z[1][2]));
    S[1].push_back(Sigmoid(Z[1][3]));

    Z[2].push_back(
      S[1][0] * W[2][0] + S[1][1] * W[2][1] + S[1][2] * W[2][2] + S[1][3] * W[2][3]
    );

    double y_hat = Sigmoid(Z[2][0]);
    double E = (1.0/2.0) * pow((y_hat - y[i]), 2);

    cout << "OUTPUT: " << y_hat << endl;
    cout << "ERROR: " << E << endl << endl;

    // BACKPROGATION
    W[2][0] -= l_rate * S[1][0] * y_hat * (1 - y_hat) * (y_hat - y[i]);
    W[2][1] -= l_rate * S[1][1] * y_hat * (1 - y_hat) * (y_hat - y[i]);
    W[2][2] -= l_rate * S[1][2] * y_hat * (1 - y_hat) * (y_hat - y[i]);
    W[2][3] -= l_rate * S[1][3] * y_hat * (1 - y_hat) * (y_hat - y[i]);

    d[0].push_back(y_hat * (1 - y_hat) * (y_hat - y[i]));

    W[1][0] -= l_rate * S[0][0] * S[1][0] * (1 - S[1][0]) * W[2][0] * d[0][0];
    W[1][1] -= l_rate * S[0][1] * S[1][0] * (1 - S[1][0]) * W[2][0] * d[0][0];
    W[1][2] -= l_rate * S[0][2] * S[1][0] * (1 - S[1][0]) * W[2][0] * d[0][0];
    W[1][3] -= l_rate * S[0][3] * S[1][0] * (1 - S[1][0]) * W[2][0] * d[0][0];
    W[1][4] -= l_rate * S[0][0] * S[1][1] * (1 - S[1][1]) * W[2][1] * d[0][0];
    W[1][5] -= l_rate * S[0][1] * S[1][1] * (1 - S[1][1]) * W[2][1] * d[0][0];
    W[1][6] -= l_rate * S[0][2] * S[1][1] * (1 - S[1][1]) * W[2][1] * d[0][0];
    W[1][7] -= l_rate * S[0][3] * S[1][1] * (1 - S[1][1]) * W[2][1] * d[0][0];
    W[1][8] -= l_rate * S[0][0] * S[1][2] * (1 - S[1][2]) * W[2][2] * d[0][0];
    W[1][9] -= l_rate * S[0][1] * S[1][2] * (1 - S[1][2]) * W[2][2] * d[0][0];
    W[1][10] -= l_rate * S[0][2] * S[1][2] * (1 - S[1][2]) * W[2][2] * d[0][0];
    W[1][11] -= l_rate * S[0][3] * S[1][2] * (1 - S[1][2]) * W[2][2] * d[0][0];
    W[1][12] -= l_rate * S[0][0] * S[1][3] * (1 - S[1][3]) * W[2][3] * d[0][0];
    W[1][13] -= l_rate * S[0][1] * S[1][3] * (1 - S[1][3]) * W[2][3] * d[0][0];
    W[1][14] -= l_rate * S[0][2] * S[1][3] * (1 - S[1][3]) * W[2][3] * d[0][0];
    W[1][15] -= l_rate * S[0][3] * S[1][3] * (1 - S[1][3]) * W[2][3] * d[0][0];
    
    d[1].push_back(S[1][0] * (1 - S[1][0]) * W[2][0] * d[0][0]);
    d[1].push_back(S[1][1] * (1 - S[1][1]) * W[2][1] * d[0][0]);
    d[1].push_back(S[1][2] * (1 - S[1][2]) * W[2][2] * d[0][0]);
    d[1].push_back(S[1][3] * (1 - S[1][3]) * W[2][3] * d[0][0]);

    W[0][0] -= l_rate * X1[i] * S[0][0] * (1 - S[0][0]) * W[1][0] * W[1][4] * W[1][8] * W[1][12] * d[1][0];
    W[0][1] -= l_rate * X2[i] * S[0][0] * (1 - S[0][0]) * W[1][0] * W[1][4] * W[1][8] * W[1][12] * d[1][0];
    W[0][2] -= l_rate * X1[i] * S[0][1] * (1 - S[0][1]) * W[1][1] * W[1][5] * W[1][9] * W[1][13] * d[1][1];
    W[0][3] -= l_rate * X2[i] * S[0][1] * (1 - S[0][1]) * W[1][1] * W[1][5] * W[1][9] * W[1][13] * d[1][1];
    W[0][4] -= l_rate * X1[i] * S[0][2] * (1 - S[0][2]) * W[1][2] * W[1][6] * W[1][10] * W[1][14] * d[1][2];
    W[0][5] -= l_rate * X2[i] * S[0][2] * (1 - S[0][2]) * W[1][2] * W[1][6] * W[1][10] * W[1][14] * d[1][2];
    W[0][6] -= l_rate * X1[i] * S[0][3] * (1 - S[0][3]) * W[1][3] * W[1][7] * W[1][11] * W[1][15] * d[1][3];
    W[0][7] -= l_rate * X2[i] * S[0][3] * (1 - S[0][3]) * W[1][3] * W[1][7] * W[1][11] * W[1][15] * d[1][3];
  }
}
