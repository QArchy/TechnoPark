cmake_minimum_required(VERSION 3.20)
project(TechnoPark C)

set(CMAKE_C_STANDARD 99)

add_executable(TechnoPark main.c Chess/chess_coord.h Chess/chess_coord_array.h Chess/chess_coord_tree.h Chess/chess_coord_tree_array.h Chess/Chess.h Chess/figure_info.h SortAlgos/IntArray.h)