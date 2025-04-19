cmake_minimum_required(VERSION 3.25)
project(segmentboundarymerger)

set(CMAKE_CXX_STANDARD 17)
find_package(GTest REQUIRED)

add_executable(segmentboundarymerger main.cpp SegmentMerger.cpp SegmentMerger.h)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

