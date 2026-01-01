cmake_minimum_required(VERSION 3.14)

#Setting the project name and version
project(QuantEngine VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Required for creating Python extensions. As in I want to make a library here and this ensures it.


include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.11.1 
)
#Make pybind11 available
FetchContent_MakeAvailable(pybind11)


#This creates the target 'quant_engine' which Python can import
pybind11_add_module(quant_engine
    src/BSModel.cpp #files I will make
    src/bindings.cpp
)

#To ensure that the module will see the headers
target_include_directories(quant_engine PRIVATE src)
