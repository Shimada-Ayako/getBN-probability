/**
 * @file make_cft.hpp
 * @author Koya KATO 
 * @date 2024-08-08 14:43:42
 */

#ifndef MAKE_CFT_HPP
#define MAKE_CFT_HPP

#include<vector>
#include<string>
#include<map>

long long make_key(std::vector<int> data, int i, std::vector<std::vector<int>> matrix, int max_state);
std::vector<std::map<long long, std::vector<int>>> make_cft(std::vector<std::vector<int> > learning_data, std::vector<int> number_state, std::vector<std::vector<int> > matrix, int max_state);

#endif