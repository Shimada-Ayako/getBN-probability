add_library(src SHARED load_data.cpp load_ldata.cpp load_matrix.cpp load_tdata.cpp make_cft.cpp est_dist.cpp)
add_definitions( -std=c++20 -Wall )
target_include_directories(src PUBLIC ../inc)
