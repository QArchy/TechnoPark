cmake_minimum_required(VERSION 3.20)
project(TechnoPark C)

set(CMAKE_C_STANDARD 99)

add_executable(TechnoPark main.c Chess/chess_coord.h Chess/chess_coord_array.h Chess/chess_coord_tree.h Chess/chess_coord_tree_array.h Chess/Chess.h Chess/figure_info.h DataStructures/IntArray.h DataStructures/SimplyLinkedList.h DataStructures/DoublyLinkedList.h SortAlgos/Bubble.h SortAlgos/Shaker.h SortAlgos/Comb.h SortAlgos/Insertion.h SortAlgos/Select.h SortAlgos/Quick.h SortAlgos/Merge.h SortAlgos/TestSort.h DataStructures/LIFOList.h DataStructures/FIFOList.h DataStructures/DequeList.h DataStructures/DequeArray.h DataStructures/BalancedBinarySearchTree.h)