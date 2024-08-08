/**
 * @file est_dist.cpp
 * @brief estimate the probabilistic distribution of the  class variable 
 * @author Koya KATO
 * @date 2024-08-08 15:05:23
 */

#include<vector>
#include<string>
#include<exception>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<map>
#include"est_dist.hpp"
#include"make_cft.hpp"


std::vector<std::vector<double> > est_dist(std::vector<std::vector<int> > test_data, std::vector<int> number_state, std::vector<std::vector<int> > matrix, int max_state, std::vector<std::map<long long, std::vector<int>>> cft, int target_variable){
    int variable_num = test_data[0].size();
    std::vector<std::vector<double>> p_dist;
    for(int t = 0; t < test_data.size(); ++t){
        std::vector<int> current_test_data(test_data[0].size());
        for(int i = 0; i < variable_num; ++i){
            current_test_data[i] = test_data[t][i];
            // std::cout << current_test_data[i] << " ";
        }
        // std::cout << std::endl;
        std::vector<double> p(number_state[target_variable], 0.0);

        double alpha_i = 1.0;
        for(int i = 0; i < variable_num; ++i){
            // ハイパーパラメータ alpha_ijk, alpha_ijの準備
            double alpha_ij = alpha_i;
            double denominator = 1.0;
            for(int j = 0; j < matrix[i].size(); ++j){
                if(matrix[j][i] == 1){
                    denominator *= number_state[j];
                }
            }
            alpha_ij /= denominator;

            double alpha_ijk = alpha_i / (denominator * number_state[i]);

            for(int v = 0; v < number_state[target_variable]; ++v){
                current_test_data[target_variable] = v;
                long long hash = make_key(current_test_data, i, matrix, max_state);
                // std::cout << hash << std::endl;
                double n_ij = 0.0;
                for(int k = 0; k < number_state[i]; ++k){
                    int sum = 0;
                    if(cft[i].contains(hash)){
                        sum = cft[i].at(hash)[k];
                    }else{
                        sum = 0;
                    }
                    n_ij += sum;
                }

                double n_ijk = 0.0;
                int sum = 0;
                if(cft[i].contains(hash)){
                    sum = cft[i].at(hash)[current_test_data[i]];
                }else{
                    sum = 0;
                }
                n_ijk = sum;
                p[v] += std::log(n_ijk + alpha_ijk) - std::log(n_ij + alpha_ij);
            }
        }
        double total = 0.0;
        for(int n = 0; n < number_state[target_variable]; ++n){
            total += std::exp(p[n]);
            if(total == 0){
                total = 1;
            }
        }
        // std::cout << "total: " <<  total << " p[0]: " << std::exp(p[0]) << " p[1]: " << std::exp(p[1]) << std::endl;
        for(int j = 0; j < number_state[target_variable]; ++j){
            p[j] = std::exp(p[j]) / total;
        }
        // std::cout << "total: " <<  total << " p[0]: " << p[0] << " p[1]: " << p[1] << std::endl << std::endl;
        p_dist.push_back(p);
    }
    std::cout << std::endl;

    return p_dist;
}