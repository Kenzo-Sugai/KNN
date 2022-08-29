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
  ofstream myfile;
  myfile.open("output.txt");
  std::vector<unsigned int> N {4, 8, 16, 32, 32, 3};
  MatrixXd Input(4, 1);
  MatrixXd Output;
  MatrixXd Target(3, 1);
  double l_rate = 0.500;
  unsigned int epoch,Epochs = 150;
  double error;

  CsvReader csv("iris.csv");

  Network net(N);

  for(epoch=0;epoch<Epochs;epoch++){
  //std::cout << "Epoch " << epoch+1 << std::endl;
  error = 0;
    for(int i = 0; i < 150; i++){
      MatrixXd Input(4, 1);
      MatrixXd Target(3, 1);

      for(int line = 0; line < Input.rows(); line++){
        for(int column = 0; column < Input.cols(); column++){
          Input(line, column) = csv.parse[i][line];
        }
      }

      for(int line = 0; line < Target.rows(); line++){
        for(int column = 0; column < Target.cols(); column++){
          Target(line, column) = csv.parse[i][csv.parse[i].size() - 3 + line ];
        }
      }

      // std::cout << Input << std::endl;
      // std::cout << Target << std::endl;
      
      Output = net.feedFoward(Input);
      //std::cout << Output << std::endl;
      //std::cout << "Output: " << Output << std::endl;
      //std::cout << "Error: ";
      error += net.showError(Output, Target)(0, 0);
      //myfile << error(0, 0) << '\n';
      net.backPropagation(Output, Target, l_rate);
    }
    error /= 150.0;
    std::cout << "EPOCH: " << epoch+1 << " ERROR: " << error << std::endl;
    myfile << error << '\n';
  }
  myfile.close();
}
