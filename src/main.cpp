#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Network.hpp"
#include "csvreader.hpp"

using namespace Eigen;

CsvReader csv("iris.csv");

MatrixXd Input(4, 1);
MatrixXd Target(3, 1);

void setValue(const int i, MatrixXd &temp, string type){
  for(int line = 0; line < temp.rows(); line++){
    for(int column = 0; column < temp.cols(); column++){
      if(type == "input")
        temp(line, column) = csv.parse[i][line];
      if(type == "target")
        temp(line, column) = csv.parse[i][csv.parse[i].size() - Target.rows() + line];
    }
  }
}

int main(){
  ofstream myfile;
  myfile.open("output.txt");
  std::vector<unsigned int> N {4, 8, 16, 16, 32, 3};
  MatrixXd Output;
  double l_rate = 0.900;
  unsigned int epoch,Epochs = 150;
  double error;

  Network net(N,Sigmoid,Derivative_Sigmoid);
  //net.setFunction(0,ReLU,Derivative_ReLU);

  for(epoch = 0; epoch < Epochs; epoch++){
    error = 0;
    for(int i = 0; i < 150; i++){
      setValue(i, Input, "input");
      setValue(i, Target, "target");

      Output = net.feedFoward(Input);
      error += net.showError(Output, Target)(0, 0);
      net.backPropagation(Output, Target, l_rate);
    }
    error /= 150.0;
    std::cout << "EPOCH: " << epoch+1 << " ERROR: " << error << std::endl;
    myfile << error << '\n';
  }
  myfile.close();
}
