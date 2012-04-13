CC = g++
CFLAGS = -std=c++0x -fPIC -g -I../Benoit/src -lpugixml
OBJECTS = Neuron_base.o Neuron_input.o Neuron_linear.o Neuron_sigmoid.o NeuralNet.o

libAlexander.so: $(OBJECTS)
	gcc -shared -Wl,-soname,libAlexander.so.1 -o libAlexander.so.1.0 $(OBJECTS); \
	ln -s libAlexander.so.1.0 libAlexander.so.1; \
	ln -s libAlexander.so.1 libAlexander.so

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
	rm libAlexander.so libAlexander.so.1 libAlexander.so.1.0

#$ gcc -fPIC -c *.c
#$ gcc -shared -Wl,-soname,libfoo.so.1 -o libfoo.so.1.0 *.o
#$ ln -s libfoo.so.1.0 libfoo.so.1
#$ ln -s libfoo.so.1 libfoo.so
#$ LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH ; export LD_LIBRARY_PATH
