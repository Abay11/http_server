cmake_minimum_required(VERSION 3.9.1)

project(HTTP_SERVER)

set(CMAKE_CXX_STANDARD 11)

file(GLOB final_src "*.h" "*.cpp")

message("sources: " "${final_src}")

find_package(Boost REQUIRED date_time regex)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(final "${final_src}")
target_link_libraries(final Boost::date_time Boost::regex)