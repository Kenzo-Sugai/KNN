#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace d{

  int drv(string formula, int x){
    string aux = "";
    vector<int> cash;
    for(int i = 0; formula[i] != 'x'; i++){
      aux += formula[i];
      cash.push_back(stoi(aux));
    }
    
  }

}
