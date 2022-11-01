cmake_minimum_required(VERSION 3.23)
project(GetAVInfo)

set(CMAKE_CXX_STANDARD 17)

add_executable(GetAVInfo main.cpp)

find_path(AVCODEC_INCLUDE_DIR /usr/include/libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)

find_path(AVFORMAT_INCLUDE_DIR /usr/include/libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat)

target_include_directories(GetAVInfo PRIVATE ${AVCODEC_INCLUDE_DIR} ${AVFORMAT_INCLUDE_DIR})
target_link_libraries(GetAVInfo PRIVATE ${AVCODEC_LIBRARY} ${AVFORMAT_LIBRARY})
