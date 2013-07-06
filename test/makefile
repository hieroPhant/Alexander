CC = g++
CFLAGS = -std=c++11 -g -march=native
PFLAGS = -lgtest -lboost_system
SRC = ../src
BEN = ../Benoit
PATHS = -I$(SRC) -I$(BEN) -I$(BEN)/src

test_alex : test_alex.cpp $(SRC)/SignalPropagator.h
	$(CC) $(CFLAGS) $(PATHS) $(PFLAGS) test_alex.cpp -o test_alex

