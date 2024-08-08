/**
 * @file load_ldata.cpp
 * @brief load learning data
 * @author Koya KATO
 * @date 2024-08-08 11:23:12
 */

#include<vector>
#include<string>
#include<exception>
#include<iostream>
#include<fstream>
#include<sstream>
#include"load_ldata.hpp"


/**
 * @fn std::vector<std::vector<int> > load_ldata(std::vector<std::vector<int> > data)
 * @brief load the learning data 
 * @return adjacency matrix (vector)
*/
std::vector<std::vector<int> > load_ldata(std::vector<std::vector<int> > data, int v, int validation_num){
    std::vector<std::vector<int> > learning_data;
    if(v < validation_num - 1){
        for(int i = 0; i < data.size(); ++i){
            if(i < v * (data.size() / validation_num) || (v + 1) * (data.size() / validation_num) <= i){
                learning_data.push_back(data[i]);
            }
        }
    }else{
        for(int i = 0; i < (validation_num - 1) * (data.size() / validation_num); ++i){
            learning_data.push_back(data[i]);
        }
    }

    return learning_data;
}
