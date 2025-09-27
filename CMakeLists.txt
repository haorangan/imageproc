cmake_minimum_required(VERSION 3.30)
project(cpp_imageproc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(imgcore src/image_gray8.cpp)
target_include_directories(imgcore PUBLIC include)

add_executable(cpp_imageproc app/imgproc.cpp)

target_link_libraries(cpp_imageproc PRIVATE imgcore)
