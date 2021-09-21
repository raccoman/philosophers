cmake_minimum_required(VERSION 3.17)
project(philosophers_bonus C)

set(CMAKE_CXX_STANDARD 89)

include_directories(headers)

set(SRCS
		src/utils.c
		src/logger.c
		src/routines.c
		src/philosophers.c)

add_executable(${PROJECT_NAME} src/main.c ${SRCS})