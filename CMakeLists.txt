cmake_minimum_required(VERSION 3.5)
project(log4cpp)

set(CMAKE_CXX_STANDARD		11)

set(CMAKE_CXX_FLAGS		"${CMAKE_CXX_FLAGS} -O3 -Wall")

set(SOURCES			src/logger.hpp
				src/logger.cpp)

add_library(log4cpp STATIC ${SOURCES})
target_include_directories(log4cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(log4cpp PROPERTIES PUBLIC_HEADER "src/logger.hpp")

install(TARGETS log4cpp DESTINATION /usr/lib PUBLIC_HEADER DESTINATION /usr/include)

