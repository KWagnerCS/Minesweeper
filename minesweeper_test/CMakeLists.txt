cmake_minimum_required(VERSION 3.23)
project(minesweeper_test)

set(CMAKE_CXX_STANDARD 14)

#change to C:/Libraries-C++ on laptop
#change to D:/Libraries on desktop
set(SFML_DIR "C:/Libraries-C++/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)


add_executable(minesweeper minesweeper.cpp minesweeper.h Toolbox.cpp Toolbox.h Tile.cpp Tile.h Button.cpp Button.h GameState.cpp GameState.h)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)