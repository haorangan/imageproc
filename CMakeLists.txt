cmake_minimum_required(VERSION 3.30)
project(cpp_imageproc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(imgcore src/image_gray8.cpp
        src/canny.cpp
        src/gaussian.cpp
        src/sobel.cpp
        src/nonmax.cpp
        src/hysteresis.cpp)
target_include_directories(imgcore PUBLIC include)

add_executable(cpp_imageproc app/imgproc.cpp
        include/gaussian.h
        include/sobel.h
        include/nonmax.h
        include/hysteresis.h
        include/canny.h)

target_compile_definitions(cpp_imageproc PRIVATE
        PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

target_link_libraries(cpp_imageproc PRIVATE imgcore)
