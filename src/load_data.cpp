/**
 * @file load_data.cpp
 * @brief load  sample data to solve
 * @author Koya KATO
 * @date 2024-08-08 11:16:14
 */

#include<vector>
#include<string>
#include<exception>
#include<iostream>
#include<fstream>
#include<sstream>
#include"load_data.hpp"


// delimiter 
std::vector<std::string> splitd(std::string &input, char delimiter) {
  std::istringstream stream(input);
  std::string field;
  std::vector<std::string> result;
  while (getline(stream, field, delimiter)) result.push_back(field);
  return result;
}

/**
 * @fn std::vector<std::vector<int> > load_data(std::string filename)
 * @brief load the adjacency matrix (csv format)
 * @return adjacency matrix (vector)
*/
std::vector<std::vector<int> > load_data(std::string filename){
    std::ifstream ifs(filename); // file stream
    std::vector<std::vector<int> > load_data; // adjacency matrix
    if (ifs) {
        std::string line;
        
        while (getline(ifs, line)) {
            std::vector<int> datvec;
            std::vector<std::string> strvec = splitd(line, ',');
            for (auto &&s : strvec) datvec.push_back(std::stoi(s)); // convert string -> int
            load_data.push_back(datvec);
        }
    }else{
        std::cerr << "No data file." << std::endl;
        std::exit(1);
    }
    return load_data;
}
