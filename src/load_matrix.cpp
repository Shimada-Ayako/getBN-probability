/**
 * @file load_matrix.cpp
 * @brief load the matrix to solve
 * @author Koya KATO
 * @date 2024-08-08 11:07:21
 */

#include<vector>
#include<string>
#include<exception>
#include<iostream>
#include<fstream>
#include<sstream>
#include"load_matrix.hpp"


// delimiter 
std::vector<std::string> split(std::string &input, char delimiter) {
  std::istringstream stream(input);
  std::string field;
  std::vector<std::string> result;
  while (getline(stream, field, delimiter)) result.push_back(field);
  return result;
}

/**
 * @fn std::vector<std::vector<int> > load(std::string filename)
 * @brief load the adjacency matrix (csv format)
 * @return adjacency matrix (vector)
*/
std::vector<std::vector<int> > load_matrix(std::string filename){
    std::ifstream ifs(filename); // file stream
    std::vector<std::vector<int> > load_matrix; // adjacency matrix
    if (ifs) {
        std::string line;
        
        while (getline(ifs, line)) {
            std::vector<int> datvec;
            std::vector<std::string> strvec = split(line, ',');
            for (auto &&s : strvec) datvec.push_back(std::stoi(s)); // convert string -> int
            load_matrix.push_back(datvec);
        }
    }else{
        std::cerr << "No matrix file." << std::endl;
        std::exit(1);
    }
    return load_matrix;
}
