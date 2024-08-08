/**
 * @file load_tdata.cpp
 * @brief load test data
 * @author Koya KATO
 * @date 2024-08-08 11:58:32
 */

#include<vector>
#include<string>
#include<exception>
#include<iostream>
#include<fstream>
#include<sstream>
#include"load_tdata.hpp"


/**
 * @fn std::vector<std::vector<int> > load_tdata(std::vector<std::vector<int> > data)
 * @brief load the test data 
 * @return adjacency matrix (vector)
*/
std::vector<std::vector<int> > load_tdata(std::vector<std::vector<int> > data, int v, int validation_num){
    std::vector<std::vector<int> > test_data;
    if(v < validation_num - 1){
        for(int i = v * (data.size() / validation_num); i < (v + 1) * (data.size() / validation_num); ++i){
            test_data.push_back(data[i]);
        }
    }else{
        for(int i = v * (data.size() / validation_num); i < (v + 1)*(data.size() / validation_num) + data.size() % validation_num; ++i){
            test_data.push_back(data[i]);
        }
    }

    return test_data;
}
