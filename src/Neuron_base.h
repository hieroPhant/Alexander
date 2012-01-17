#ifndef Neuron_base_h
#define Neuron_base_h

/*
	(c) Jack Hall 2011, licensed under GNU GPL v3
	Neuron_base is a single-Node interface class. It provides an interface for the 
	fundamental independent element in a neural network: a Neuron. However, in the 
	interest of keeping Alexander's interface and data structure separate from the 
	implementation of neural computations, Neuron_base stores no data and performs
	no computation. 
*/

#include <iostream>
#include <deque>
#include "Benoit.h"

class Neuron_base {
/*
	
*/

private:
	Neuron_base(); 	
	Neuron_base& operator=(const Neuron_base& rhs);
	
protected:
	Node<double,double> connections;
	
public:
	bool trainable;	
	
	Neuron_base(const bool bTrainable=true)
	: connections(), trainable(bTrainable) {}
	Neuron_base(const Neuron_base& rhs) 
	: connections(rhs.connections, trainable(rhs.trainable) {}
	virtual ~Neuron_base();
	virtual Node& fire() = 0;
	virtual Node& backPropagate(const unsigned int nStepsBack) = 0;
	void remove_input(Connection_base* pOldIn);
	void remove_output(Connection_base* pOldOut);	//unique to Neuron_base
};

#endif

