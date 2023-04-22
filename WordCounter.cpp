#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include "CLI11.hpp"
#include "bloom.h"


int main(int argc, char **argv) {

  CLI::App app{"WordCounter"};

  // std::string arg1, arg2;
  // app.add_option("arg1", arg1, "The first argument")->required();
  // app.add_option("arg2", arg2, "The second argument")->required();

  std::string s;
  long long int m = 1000000;
  int k = 2;
  app.add_option("-d, --dict", s, "Testing file");

  app.add_option("-m, --bits", m, "Allocating the size of the vector");

  app.add_option("-k, --hash", k, "Hashes to try");

  CLI11_PARSE(app, argc, argv);
  if (k < 2 || k > 3) {
    k = 2;
  }

  BloomFilter bf( m, k, s);
  bf.output();
  bf.WCStart();
  bf.outputMap();
  return 0;
}//end main
