cmake_minimum_required(VERSION 3.15)
project(rest_api)

set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_PREFIX_PATH /home/linuxbrew/)

find_package(spdlog REQUIRED)
find_package(libmongocxx REQUIRED)

add_executable(rest_api main.cpp src/dbConnector.cpp headers/dbConnector.h)
target_include_directories(rest_api PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS})
target_link_libraries(rest_api PRIVATE spdlog::spdlog boost_system ${LIBMONGOCXX_LIBRARIES})
target_compile_definitions(rest_api PRIVATE ${LIBMONGOCXX_DEFINITIONS})
