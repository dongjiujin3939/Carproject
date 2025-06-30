cmake_minimum_required(VERSION 3.10)
project(CarProject)

set(CMAKE_CXX_STANDARD 17)

# 源文件
file(GLOB SRC_FILES src/*.cpp)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

# 链接库目录
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(CarProject ${SRC_FILES})

# 链接 EasyX 及依赖库
target_link_libraries(CarProject easyx gdi32 ole32 uuid)