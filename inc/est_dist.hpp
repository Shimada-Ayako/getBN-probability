/**
 * @file est_dist.hpp
 * @author Koya KATO 
 * @date 2024-08-08 15:00:48
 */

#ifndef EST_DIST_HPP
#define EST_DIST_HPP

#include<vector>
#include<string>
#include<map>

std::vector<std::vector<double> > est_dist(std::vector<std::vector<int> > test_data, std::vector<int> number_state, std::vector<std::vector<int> > matrix, int max_state, std::vector<std::map<long long, std::vector<int>>> cft, int target_variable);

#endif