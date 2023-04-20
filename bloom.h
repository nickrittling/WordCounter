
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <sstream>
#include <string>
#include <vector>

class BloomFilter {
public:
  BloomFilter(long long int m, int k, std::string s)
      : m_(m), k_(k), file(s), dict(m, 0), conflict(0), n_(0) {
    std::ifstream infile;
    infile.open(file);
    if (!infile)
      std::cout << "File not found\n";
    std::string line;
    while (getline(infile, line)) {
      n_++;
      insert(line);
    }
    infile.close();
  }

  int getConfilct() { return conflict; }

  size_t hash1(std::string s) { return std::hash<std::string>{}(s) % m_; }

  size_t hash2(std::string s) {
    unsigned char sha256_result[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)s.c_str(), s.length(), sha256_result);
    size_t result;
    std::memcpy(&result, sha256_result, sizeof(size_t));
    return result % m_;
  }
  size_t hash3(std::string s) {
    unsigned char md5_result[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)s.c_str(), s.length(), md5_result);
    size_t result;
    std::memcpy(&result, md5_result, sizeof(size_t));
    return result % m_;
  }

  void insert(std::string s) {
    if (k_ == 2) {
      if (dict[hash1(s)]) {
        conflict++;
      }

      dict[hash1(s)] = 1;
      if (dict[hash2(s)]) {
        conflict++;
      }

      dict[hash2(s)] = 1;

    } // end k 2
    else {
      if (dict[hash1(s)]) {
        conflict++;
      }

      dict[hash1(s)] = 1;

      if (dict[hash2(s)]) {
        conflict;
      }

      dict[hash2(s)] = 1;

      if (dict[hash3(s)]) {
        conflict++;
      }

      dict[hash3(s)] = 1;
    }
  } // end insert

  void output() {
    double prob = std::pow((1 - std::pow((1 - (1 / m_)), k_ * n_)), k_);
    std::cout << "m:" << m_ << " k:" << k_ << " n:" << n_ << std::endl;
    std::cout << "false positive probability: " << prob << std::endl;
    std::cout << "number of conflict: " << conflict << std::endl;
  }

private:
  long long int m_;
  int k_;
  int n_;
  int conflict;
  std::string file;
  std::vector<bool> dict;

}; // end class BloomFIlter