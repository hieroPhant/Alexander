CC = g++
CFLAGS = -std=c++11 -g -march=native
BASE = ..
SRC = $(BASE)/src
BEN = $(BASE)/Benoit
PATHS = -I$(BASE) -I$(SRC) -I$(BEN) -I$(BEN)/src

test_alex : test_alex.cpp $(SRC)/Node.h
	$(CC) $(CFLAGS) $(PATHS) -lgtest test_alex.cpp -o test_alex

test_xor : McCullochPittsDemo.cpp $(SRC)/SignalPropagator.h $(SRC)/McCullochPittsLink.h $(SRC)/McCullochPittsNeuron.h
	$(CC) $(CFLAGS) $(PATHS) McCullochPittsDemo.cpp -o test_xor

