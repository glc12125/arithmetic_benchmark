cmake_minimum_required(VERSION 2.8)

project(arithmetic_benchmark)

IF(APPLE)
#set(CMAKE_C_COMPILER "/usr/local/Cellar/gcc/7.3.0_1/bin/gcc-7")
#set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/7.3.0_1/bin/g++-7")
ENDIF(APPLE)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPTS} -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -std=c++11 -O3 -lpthread -lboost_system")

if(APPLE)
find_package(Eigen3 3.1.0 REQUIRED PATHS /usr/local/share/eigen3 NO_DEFAULT_PATH)
else(APPLE)
find_package(Eigen3 3.1.0 REQUIRED)
endif(APPLE)

find_package(Boost 1.54.0 COMPONENTS filesystem thread regex serialization REQUIRED)


#find_package(Gperftools REQUIRED)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${CMAKE_SOURCE_DIR}/include/"
                    ${Boost_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIR}
                   )


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})



add_executable(StdMatrix
  "${CMAKE_SOURCE_DIR}/src/StdMatrix_t.cpp"
)

add_executable(EigenMatrix
  "${CMAKE_SOURCE_DIR}/src/EigenMatrix_t.cpp"
)


#set_target_properties(MainServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/MainServer)
