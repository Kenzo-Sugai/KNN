#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>

using namespace Eigen;

double Sigmoid(double x){
  return 1.0 / (1.0 + exp(-x));
}

double Derivative_Sigmoid(double x){
  return Sigmoid(x) * (1 - Sigmoid(x)); 
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

class Network {
  
  public:

  std::vector<unsigned int> layers; // tamanho de cada layer
  std::vector<MatrixXd> Weight; // Matriz de pesos
  std::vector<MatrixXd> Z; // Matriz peso * input
  std::vector<MatrixXd> Input; // Matriz de inputs
    
  Network(const std::vector<unsigned int> &layers);
  void randomInitialize(MatrixXd &Matrix);
  MatrixXd feedFoward(const MatrixXd &input);
  void backPropagation(const MatrixXd &output, const MatrixXd &target, double l_rate);
  MatrixXd multiplicationMatrix(const MatrixXd &A_Matrix, const MatrixXd &B_Matrix);
  void showError(const MatrixXd &output, const MatrixXd &target);
};

Network::Network(const std::vector<unsigned int> &layers){
  this->layers = layers;

  this->Input = std::vector<MatrixXd>(layers.size());
  this->Z = std::vector<MatrixXd>(layers.size());

  // percorrer cada layer do vetor de layers
  for(unsigned int layer = 1; layer < layers.size(); layer++){
    
    MatrixXd w(layers[layer], layers[layer - 1]); // criar matriz com 
    Network::randomInitialize(w); // preenchimento da matriz com pesos aleatórios
    Weight.push_back(w); // preenchimento do vetor peso com matrizes

    std::cout << Weight.back() << std::endl << std::endl;
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

void Network::showError(const MatrixXd &output, const MatrixXd &target){
  std::cout << std::fixed;
  std::cout << std::setprecision(2) << (1.0/2.0) * Network::multiplicationMatrix((output - target), (output - target)) * 100 << std::fixed << "%" <<std::endl;
}

void Network::randomInitialize(MatrixXd &Matrix){
  for(int line = 0; line < Matrix.rows(); line++){
    for(int column = 0; column < Matrix.cols(); column++){
      Matrix(line, column) = 2 * rand() / double(RAND_MAX) - 1;
    }
  }
}

MatrixXd Network::feedFoward(const MatrixXd &Input){
  this->Input[0] = Input;

  for(unsigned int layer = 1; layer < this->layers.size(); layer++){
    
    Z[layer] = this->Weight[layer - 1] * this->Input[layer - 1];
    this->Input[layer] = activationFunction(this->Z[layer], Sigmoid);
  
  }

  return this->Input[this->layers.size() - 1];
}

void Network::backPropagation(const MatrixXd &output, const MatrixXd &target, double l_rate){

  std::vector<MatrixXd> Delta(this->layers.size()); // size Delta

  Delta[this->layers.size() - 1] = activationFunction(this->Z[this->layers.size() - 1], Derivative_Sigmoid) * (output - target); // Delta da ultima layer

  for(unsigned int layer = layers.size() - 2; layer > 0; layer--){

    Delta[layer] = multiplicationMatrix(activationFunction(this->Z[layer], Derivative_Sigmoid), this->Weight[layer].transpose() * Delta[layer + 1]);
  
  }

  for(unsigned int layer = 0; layer < layers.size() - 1; layer++){

    this->Weight[layer] -= l_rate * Delta[layer + 1] * this->Input[layer].transpose();

  }
}
