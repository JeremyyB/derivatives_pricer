cmake_minimum_required(VERSION 3.31)
project(derivatives_pricer)

set(CMAKE_CXX_STANDARD 20)

# TODO : To modify according to .venv usage & python ver
#           which is found by ` python -c "import pybind11;print(pybind11.get_include())" `
include_directories(.venv/lib/python3.9/site-packages/pybind11/include)


include_directories(src/)

find_package(pybind11 REQUIRED)

add_executable(derivatives_pricer src/bindings/bind.cpp
        src/engine/products/eu_call.cpp
        src/engine/products/eu_call.h
        src/engine/products/eu_put.cpp
        src/engine/products/eu_put.h)
