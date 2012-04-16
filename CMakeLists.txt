project(scan-barcode CXX)
cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})

add_executable(scan-barcode main)
target_link_libraries(scan-barcode ${OpenCV_LIBS} zbar)
