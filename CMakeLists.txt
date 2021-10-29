cmake_minimum_required(VERSION 3.20)
project(TechnoPark C)

set(CMAKE_C_STANDARD 99)

add_executable(TechnoPark main.c chess_coord.h chess_coord_array.h chess_coord_tree.h chess_coord_tree_array.h Chess.h figure_info.h)
