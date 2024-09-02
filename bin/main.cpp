/**
 * @file main.cpp
 * @brief estimate a probability distribution of the class variable of Bayesian Network Classifiers
 * @author Koya KATO 
 * @date 2024-08-08 10:51:47
 */

#include<iostream>
#include<exception>
#include<stdexcept>
#include<boost/program_options.hpp>
#include<boost/program_options/positional_options.hpp>
#include<boost/program_options/option.hpp>
#include<boost/program_options/options_description.hpp>
#include<boost/timer/timer.hpp>
#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<fstream>
#include"load_matrix.hpp"
#include"load_data.hpp"
#include"load_ldata.hpp"
#include"load_tdata.hpp"
#include"make_cft.hpp"
#include"est_dist.hpp"

namespace po = boost::program_options;


std::string matrix_path;
std::string data_path;
std::string output_path;
int validation_num = 0; // DO NOT CHANGE
int target_variable;


void estimate(){
    std::vector<std::vector<double> > p_distribution;    
    std::vector<int> number_state;
    std::vector<std::vector<int> >  learning_data;
    std::vector<std::vector<int> > test_data;
    std::vector<std::map<long long, std::vector<int>>> cft;
    int max_state = 0;

    // set up matrix
    std::vector<std::vector<int> > matrix = load_matrix(matrix_path);
    int variable_num = matrix.size();


    // set up data
    std::vector<std::vector<int> > data = load_data(data_path);
    for(int i = 0; i <  variable_num; ++i){
        number_state.push_back(0);
    }

    std::vector<int> max(variable_num, 0);
    for(int i = 0; i < data.size(); ++i){
        for(int j = 0; j < variable_num; ++j){
            if(max[j] < data[i][j]){
                max[j] = data[i][j];
            }
        }
    }
    for(int i = 0; i < variable_num; ++i){
        number_state[i] = max[i] + 1;
        if(max_state < number_state[i]){
            max_state = number_state[i];
        }
    }

    // estimate the probabilistic distribution
    // for(int v = 0; v < validation_num; ++v){
        // std::cout << "validation: " << v << std::endl;
        int v = 0; // DO NOT CHANGE
        learning_data = load_ldata(data, v, validation_num);
        test_data = load_tdata(data, v, validation_num);


        // initialize p_distribution
        if(target_variable > variable_num - 1){
            std::cerr << "target variable: 0 ~ variable_num - 1" << std::endl;
            std::exit(1);
        }

        // initialize CFT
        cft = make_cft(learning_data, number_state, matrix, max_state);

        // estimate the class variable distribution
        p_distribution = est_dist(test_data, number_state, matrix, max_state, cft, target_variable );

        // check
        // for(int i = 0; i < test_data.size(); ++i){
        //     for(int v = 0; v < number_state[target_variable] - 1; ++v){
        //         printf("state[%d]: %f, ", v, p_distribution[i][v]);
        //     }
        //     printf("state[%d]: %f\n", number_state[target_variable] - 1, p_distribution[i][number_state[target_variable] - 1]);
        // }

        // output 
        std::ofstream ofs(output_path);
        if(ofs){
            for(int i = 0; i < test_data.size(); ++i){
                ofs << p_distribution[i][1] << std::endl;
            }
        }else{
            std::cerr << "Output path dose not exists." << std::endl;
            std::exit(1);
        }

    // }

}

/**
 * @fn int main (void)
 * @brief Main function to estimate a probability distribution of the class variable
 * @return 0 if the program completes successfully.
*/
int main(int argc, char** argv){
    boost::timer::auto_cpu_timer timer;
    boost::asio::io_service io; // A timer to keep track of how long the algorithm has been running.

    // description
    std::string description = std::string("Estimate a probability distribution of the class variable.");
    po::options_description desc(description);

    // add options
    desc.add_options()
        ("matrix_path", po::value<std::string > (&matrix_path)->required(), "The file containing the adjacency matrix in csv format. First positional argument.")
        ("data_path", po::value<std::string > (&data_path)->required(), "The file containing the sample data (start 0) in csv format. Second positional argument.")
        ("output_path", po::value<std::string > (&output_path)->required(), "The output file in csv format. Third positional argument.")
        // ("validation_num,v", po::value<int> (&validation_num)->default_value(10), "The maximum validation number  for the estimation. ")
        ("target_variable,t", po::value<int> (&target_variable)->default_value(0), "The target variable for the estimation. 0 ~ variable num - 1")
        ("help,h", "Show this help message.")
    ;

    // set options
    po::positional_options_description positionalOptions;
    positionalOptions.add("matrix_path", 1);
    positionalOptions.add("data_path", 2);
    positionalOptions.add("output_path", 3);
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc)
        .positional(positionalOptions).run(), vm);
    // show help message
    if(vm.count("help") || argc == 1){
        std::cout << desc;
        return 0;
    }
    po::notify(vm);


    // main function
    estimate();
    
    boost::asio::deadline_timer t(io);

    
    return 0;
}
