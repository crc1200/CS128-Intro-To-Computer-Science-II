#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "functions.hpp"

// int main(int argc, char** argv) {
//   if (argc != 2) {
//     std::cerr << "Usage: ./bin/exec word" << std::endl;
//     return 1;
//   }

//   std::string word = argv[1];
//   std::cout << Base(word) << std::endl;
// }

int main() {
  std::vector<int> fart = {1,2,3,4,5,6};
  fart[1] = fart + sizeof(int);
  return 0;
}