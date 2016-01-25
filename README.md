# 2048_console
game 2048 console application

Build command:
g++ -std=c++11 -o game.o game.cpp

To run the unit test:

g++ -std=c++11 -isystem ./googletest/include/ ../GameBoard_unittest.cpp  libgtest.a -o ../test_2048 -pthread
