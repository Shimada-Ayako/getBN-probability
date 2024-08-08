add_executable(main main.cpp)
add_definitions(-std=c++20 -Wall )
set(CMAKE_CXX_COMPILER clang++)

find_package(Boost 1.85 REQUIRED COMPONENTS
    chrono
    date_time
    iostreams
    program_options
    system
    thread
    timer
)

if(Boost_FOUND)
    target_include_directories(main PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(main PUBLIC ${Boost_LIBRARIES} src)
else()
    message(FATAL_ERROR "Cound not find Boost libraries.")
endif()


