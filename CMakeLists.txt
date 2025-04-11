cmake_minimum_required(VERSION 3.22)

project(eweda)

set(CMAKE_CXX_STANDARD 23)

add_executable(eweda
	src/eweda.cpp
	src/token.cpp
	src/lexer.cpp
	src/error.cpp
	src/ast.cpp
	src/parser.cpp
)
