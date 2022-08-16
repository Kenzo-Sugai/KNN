#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <Eigen/Dense>
#include <chrono>
#include <cstdlib>

using namespace std;
 
class CsvReader {

  public:

    string csvname;
    vector<vector<double>> parse;

    CsvReader(const string name);
    void csvPrint();
    void shuffle();

};

CsvReader::CsvReader(const string csvname){
  string fname = csvname;
  vector<vector<string>> content;
  vector<string> row;
  string line, word;
  
  fstream file (fname, ios::in);
  if(file.is_open()){

    while(getline(file, line)){
      row.clear();
      
      stringstream str(line);
      
      while(getline(str, word, ','))
      row.push_back(word);
      content.push_back(row);
    }
  } else cout<<"Could not open the file\n";
  this->parse.resize(content.size());
  for(int i=1;i<content.size();i++){
    for(int j=1;j<content[i].size();j++){ 
      double num = stod(content[i][j]);
      this->parse[i - 1].push_back(num);
    }
  }

  CsvReader::shuffle();
}

void CsvReader::shuffle(){
  MatrixXd matriz(this->parse.size(), this->parse[0].size());
  for(int i = 0; i < matriz.rows(); i++){
    for(int j = 0; j < matriz.cols(); j++){
      matriz(i, j) = this->parse[i][j];
    }
  }

  std::cout << "A" << std::endl;

  matriz.transposeInPlace();

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  for(auto row: matriz.rowwise()){

    shuffle(row.begin(), row.end(), std::default_random_engine(seed));

    matriz.transposeInPlace();

    std::cout << matriz << std::endl;
  }
}

void CsvReader::csvPrint(){
  for(unsigned int i = 0; i < parse.size(); i++){

    for(unsigned int j = 0; j < parse[i].size(); j++){

      cout << parse[i][j] << " ";
    }
    cout << endl;
  }
}
