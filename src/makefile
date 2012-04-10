CC = g++
CFLAGS = -std=c++0x -fPIC -g -I../Benoit/src
OBJECTS = Neuron_base.o Neuron_input.o Neuron_linear.o Neuron_sigmoid.o NeuralNet.o

Alexander.so: $(OBJECTS)
	ld -shared -o Alexander.so $(OBJECTS)

Neuron_base.o : Neuron_base.cpp Neuron_base.h
	$(CC) $(CFLAGS) -c Neuron_base.cpp

Neuron_input.o : Neuron_input.cpp Neuron_input.h Neuron_base.h
	$(CC) $(CFLAGS) -c Neuron_input.cpp

Neuron_linear.o : Neuron_linear.cpp Neuron_linear.h Neuron_base.h
	$(CC) $(CFLAGS) -c Neuron_linear.cpp

Neuron_sigmoid.o : Neuron_sigmoid.cpp Neuron_sigmoid.h Neuron_base.h
	$(CC) $(CFLAGS) -c Neuron_sigmoid.cpp

NeuralNet.o : NeuralNet.cpp NeuralNet.h Neuron_base.h Neuron_input.h
	$(CC) $(CFLAGS) -c NeuralNet.cpp

clean :
	rm $(OBJECTS); \
	rm Alexander.so

