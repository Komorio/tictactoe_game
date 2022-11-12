CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
PROJECT(tictactoe)
SET(CMAKE_CXX_STANDARD 17)
ADD_EXECUTABLE(main.exe main.cpp game/game.cpp screen/screen.cpp object/object.cpp vector2/vector2.cpp)
