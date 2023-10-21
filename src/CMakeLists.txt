add_executable(main main.cpp)
add_library(Game OBJECT ./gameplay/game.cpp)
target_link_libraries(main ncurses)
target_link_libraries(main Game)
