cmake_minimum_required(VERSION 2.8)

project(arithmetic_benchmark)

IF(APPLE)
#set(CMAKE_C_COMPILER "/usr/local/Cellar/gcc/7.3.0_1/bin/gcc-7")
#set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/7.3.0_1/bin/g++-7")
ENDIF(APPLE)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPTS} -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -std=c++11 -O3 -lpthread")

if(APPLE)
find_package(Eigen3 3.1.0 REQUIRED PATHS /usr/local/share/eigen3 NO_DEFAULT_PATH)
else(APPLE)
find_package(Eigen3 3.1.0 REQUIRED)
endif(APPLE)

find_package(Boost 1.54.0 COMPONENTS filesystem thread regex serialization REQUIRED)


#find_package(Gperftools REQUIRED)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${CMAKE_SOURCE_DIR}/include/"
                    ${EIGEN3_INCLUDE_DIR}
                    ${Boost_INCLUDE_DIRS}
                   )


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})



add_executable(StdMatrix
  "${CMAKE_SOURCE_DIR}/src/StdMatrix_t.cpp"
)
if(CROSS_COMPILE_ARCH STREQUAL "aarch64")
set_target_properties(StdMatrix PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_cross/)
else()
set_target_properties(StdMatrix PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
endif()

add_executable(EigenMatrix
  "${CMAKE_SOURCE_DIR}/src/EigenMatrix_t.cpp"
)
if(CROSS_COMPILE_ARCH STREQUAL "aarch64")
set_target_properties(EigenMatrix PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_cross/)
else()
set_target_properties(EigenMatrix PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
endif()

add_executable(FloatingCycle
  "${CMAKE_SOURCE_DIR}/src/Floating_cycle.cpp"
)
if(CROSS_COMPILE_ARCH STREQUAL "aarch64")
set_target_properties(FloatingCycle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_cross/)
else()
set_target_properties(FloatingCycle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
endif()

add_executable(FixedCycle
  "${CMAKE_SOURCE_DIR}/src/Fixed_cycle.cpp"
)
if(CROSS_COMPILE_ARCH STREQUAL "aarch64")
set_target_properties(FixedCycle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build_cross/)
else()
set_target_properties(FixedCycle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
endif()

#set_target_properties(MainServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/MainServer)
