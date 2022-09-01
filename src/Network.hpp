#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <Eigen/Dense>

using namespace Eigen;

double Sigmoid(double x){
  return 1.0 / (1.0 + exp(-x));
}

double Derivative_Sigmoid(double x){
  return Sigmoid(x) * (1 - Sigmoid(x)); 
}

double Identity(double x){
  return x;
}

double Derivative_Identity(double x){
  return 1;
}


double Tanh(double x){
   return tanh(x);
} 

double Derivative_Tanh(double x){
  double z=tanh(x);
   return 1.0-z*z;
} 


double ReLU(double x){
  if(x >= 0) return x; return 0;
} 


double Derivative_ReLU(double x){
  if(x >= 0) return 1; return 0;
}



double LReLU(double x){
  if(x >= 0) return x; return 0.01*x;
} 

double Derivative_LReLU(double x){
  if(x >= 0) return 1; return 0.01;
}

MatrixXd activationFunction(const MatrixXd &input, double (*func)(double x)){
  MatrixXd activationMatrix(input.rows(), input.cols()); // criar nova matriz identica a matriz de input

  for(int line = 0; line < input.rows(); line++){

    for(int column = 0; column < input.cols(); column++){

      activationMatrix(line, column) = func(input(line, column)); // Nova matriz ganha ela mesma com a função de ativação inserida
    }
  }
  return activationMatrix;
}

typedef double (*FuncPointer)(double) ;

class Network {
  
  public:

  std::vector<unsigned int> layers;     // tamanho de cada layer
  std::vector<MatrixXd> Weight;         // Matriz de pesos
  std::vector<MatrixXd> Z;              // Matriz peso * input
  std::vector<MatrixXd> Input;          // Matriz de inputs
  std::vector<MatrixXd> Bias;           // Matriz de bias
  std::vector<FuncPointer> Func;
  std::vector<FuncPointer> d_Func;
  
    
  Network(const std::vector<unsigned int> &layers, FuncPointer func, FuncPointer Dfunc);
  void randomInitialize(MatrixXd &Matrix);
  MatrixXd feedFoward(const MatrixXd &input);
  void backPropagation(const MatrixXd &output, const MatrixXd &target, double l_rate);
  MatrixXd multiplicationMatrix(const MatrixXd &A_Matrix, const MatrixXd &B_Matrix);
  MatrixXd showError(const MatrixXd &output, const MatrixXd &target);
  double error(const MatrixXd);
  void setFunction(int idx, FuncPointer func, FuncPointer Dfunc);
};

Network::Network(const std::vector<unsigned int> &layers, FuncPointer func, FuncPointer Dfunc){
  this->layers = layers;

  this->Input = std::vector<MatrixXd>(layers.size());
  this->Z = std::vector<MatrixXd>(layers.size());

  // percorrer cada layer do vetor de layers
  for(unsigned int layer = 1; layer < layers.size(); layer++){
    
    MatrixXd b(layers[layer], 1);                  // criar matriz de bias
    MatrixXd w(layers[layer], layers[layer - 1]);  // criar matriz de pesos 
    Network::randomInitialize(b);                  // preenchimento da matriz com bias aleatórios
    Network::randomInitialize(w);                  // preenchimento da matriz com pesos aleatórios
    Bias.push_back(b);                             // preenchimento do vetor bias com matrizes
    Weight.push_back(w);                           // preenchimento do vetor peso com matrizes
    Func.push_back(func);                          // preenchimento do vetor peso com matrizes
    d_Func.push_back(Dfunc);                       // preenchimento do vetor peso com matrizes

  }
}

MatrixXd Network::multiplicationMatrix(const MatrixXd &A_Matrix, const MatrixXd &B_Matrix){
  MatrixXd New_Matrix(A_Matrix.rows(), A_Matrix.cols());
  for(int line = 0; line < A_Matrix.rows(); line++){

    for(int column = 0; column < A_Matrix.cols(); column++){

      New_Matrix(line, column) = A_Matrix(line, column) * B_Matrix(line, column);
    }
  }
  return New_Matrix;
}

MatrixXd Network::showError(const MatrixXd &output, const MatrixXd &target){

  return (1.0/3.0) * ((output - target).transpose() * (output - target)) * 100;
}

void Network::randomInitialize(MatrixXd &Matrix){
  for(int line = 0; line < Matrix.rows(); line++){
    for(int column = 0; column < Matrix.cols(); column++){
      Matrix(line, column) = 2 * rand() / double(RAND_MAX) - 1;
    }
  }
}

MatrixXd Network::feedFoward(const MatrixXd &In){
  this->Input[0] = In;
  for(unsigned int layer = 1; layer < this->layers.size(); layer++){
    //this->Input[layer] = this->Bias[layer - 1];
    Z[layer] = this->Weight[layer - 1] * this->Input[layer - 1]+this->Bias[layer - 1];
    this->Input[layer] = activationFunction(this->Z[layer], this->Func[layer-1]);
    /*
    if(layer == layers.size() - 1){
      this->Input[layer] = activationFunction(this->Z[layer], Sigmoid);
    }
    else{
      this->Input[layer] = activationFunction(this->Z[layer], ReLU);
    }
    */
  }
  return this->Input[this->layers.size() - 1];
}

void Network::setFunction(int idx, FuncPointer func, FuncPointer Dfunc){
  this->Func[idx] = func;
  this->d_Func[idx] = Dfunc;
}

void Network::backPropagation(const MatrixXd &output, 
                              const MatrixXd &target, 
                              double l_rate){

  std::vector<MatrixXd> Delta(this->layers.size()); // size Delta

  MatrixXd F=activationFunction(this->Z[this->layers.size() - 1], this->d_Func[this->layers.size()-2]);
  Delta[this->layers.size() - 1]  =  multiplicationMatrix(F,output - target); // Delta da ultima layer
  for(unsigned int layer = layers.size() - 2; layer > 0; layer--){
    F=activationFunction(this->Z[layer], this->d_Func[layer-1]);
    Delta[layer] = multiplicationMatrix(F, this->Weight[layer].transpose() * Delta[layer + 1]);
  }
  
  for(unsigned int layer = 0; layer < layers.size() - 1; layer++){

    this->Weight[layer] -= (l_rate/(double)layers[layers.size() - 1]) * Delta[layer + 1] * this->Input[layer].transpose();

  }
 
  for(unsigned int layer = 0; layer < layers.size() - 1; layer++){

    this->Bias[layer] -= (l_rate/(double)layers[layers.size() - 1]) * Delta[layer + 1];

  }
  
}
