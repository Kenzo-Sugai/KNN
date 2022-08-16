#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Network.hpp"
#include "csvreader.hpp"

using namespace Eigen;

int main(){

  std::vector<unsigned int> N {4, 8, 8, 8, 8, 1};
  MatrixXd Input(4, 1);
  MatrixXd Output;
  MatrixXd Target(1, 1);
  double l_rate = 0.500;

  CsvReader csv("iris.csv");

  Network net(N);
  for(int i = 0; i < 150; i++){
    MatrixXd Input(4, 1);
    MatrixXd Target(1, 1);

    for(int line = 0; line < Input.rows(); line++){
      for(int column = 0; column < Input.cols() - 1; column++){
        Input(line, column) = csv.parse[i][column];
      }
    }
    
    Target << csv.parse[i][csv.parse[i].size() - 1];
    
    Output = net.feedFoward(Input);
    std::cout << "Epoch " << i+1 << std::endl;
    std::cout << "Output: " << Output << std::endl;
    std::cout << "Error: "; 
    net.showError(Output, Target);
    std::cout << std::endl;
    net.backPropagation(Output, Target, l_rate);
  }
}
