#ifndef NeuralNet_h
#define NeuralNet_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

#include "Benoit.h"
#include <list>

class NeuralNet {
private:
	Index<double,double> index;
	std::list< Neuron_base > neurons;
	double width; //neighborhood size for 
	
public:
	void run();
	void train();
}

#endif
