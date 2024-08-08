/**
 * @file make_cft.cpp
 * @brief make conditional frequency table
 * @author Koya KATO
 * @date 2024-08-08 13:52:53
 */

#include<vector>
#include<string>
#include<exception>
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<chrono>
#include"make_cft.hpp"

long long prod(int a, int b){
    long long ans = 1;
    for(int i = 0; i < b; ++i){
        ans *= a;
    }
    return ans;
}

long long make_key(std::vector<int> data, int i, std::vector<std::vector<int>> matrix, int max_state){
    int number_parent_i = 0;
    for(int j = 0; j < matrix[i].size(); ++j){
        if(matrix[j][i] == 1){
            number_parent_i++;
        }
    }
    

    std::vector<int> parent_list;
    for(int j = 0; j < matrix[i].size(); ++j){
        if(matrix[j][i] == 1){
            parent_list.push_back(j);
        }
    }
   

   
    if(number_parent_i > 0){
        long long key = 0;
        for(int p = 0; p < parent_list.size(); ++p){
            key = key + (prod(max_state, p) * data[parent_list[p]]);
            // std::cout << "i " << i << " max_state: " << max_state << " p: " << p << " key: " << key  << std::endl;
        }
        
        return key;
    }else{
        return 0;
    }
   
}


std::vector<std::map<long long, std::vector<int>>> make_cft(std::vector<std::vector<int> > learning_data, std::vector<int> number_state, std::vector<std::vector<int> > matrix, int max_state){
    std::vector<std::map<long long, std::vector<int>>> cft(learning_data[0].size());
    

    // create cft
    for(int l = 0; l < learning_data.size(); ++l){
        std::vector<int> currentlearningdata;

        for(int i = 0; i < learning_data[0].size(); ++i){
            currentlearningdata.push_back(learning_data[l][i]);
        }
        for(int i = 0; i < learning_data[0].size(); ++i){
            long long hash = make_key(currentlearningdata, i, matrix, max_state);
            if(cft[i].contains(hash)){
                cft[i].at(hash)[currentlearningdata[i]]++;
            }else{
                std::vector<int> t(number_state[i], 0);
                t[currentlearningdata[i]] = 1;
                cft[i].insert(std::make_pair(hash, t));
            }
        }
    }

    return cft;
}
