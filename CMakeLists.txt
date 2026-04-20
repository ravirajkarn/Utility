cmake_minimum_required(VERSION 4.0)
project(utility CXX)


find_package(rapidxml REQUIRED)
find_package(fmt REQUIRED)
find_package(CLI11 REQUIRED)

add_executable(mvxml src/mvxml.cpp)
target_link_libraries(mvxml
    PRIVATE rapidxml::rapidxml
    PRIVATE fmt::fmt
    PRIVATE CLI11::CLI11    
)

# spell: ignore mvxml rapidxml