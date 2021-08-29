cmake_minimum_required(VERSION 3.17)
project(Threads C)

set(CMAKE_C_STANDARD 99)

add_executable(Threads main.c)
add_executable(Threads_1 costes_exo1.c)
add_executable(Threads_2 costes_exo2.c)
add_executable(Threads_3 costes_exo3.c)
add_executable(Threads_4 costes_exo4.c)
add_executable(Threads_2Poppy lawson_exo2.c)
add_executable(Threads_3Poppy lawson_exo3.c)

target_link_libraries(Threads_1 pthread)
target_link_libraries(Threads_2 pthread)
target_link_libraries(Threads_3 pthread)
target_link_libraries(Threads_4 pthread)
target_link_libraries(Threads_2Poppy pthread)
target_link_libraries(Threads_3Poppy pthread)
