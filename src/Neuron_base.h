#ifndef Neuron_base_h
#define Neuron_base_h

/*
	(c) Jack Hall 2011, licensed under GNU GPL v3
*/

#include <iostream>
#include <deque>
#include "Benoit.h"

class Neuron_base {
protected:
	Node<double,double> connections;
	std::deque<double> state;
	
public:
	bool trainable;	//may need a way to set individual Links as trainable
	
	Neuron_base(); 
	Neuron_base(const double dBias);
	Neuron_base(Index<double,double>& cIndex, const double dBias=0);
	Neuron_base(const Neuron_base& rhs)=delete;
	Neuron_base(Neuron_base&& rhs);
	Neuron_base& operator=(const Neuron_base& rhs)=delete;
	Neuron_base& operator=(Neuron_base&& rhs);
	virtual ~Neuron_base();
	
	virtual void fire() = 0;
	virtual void backpropagate(const unsigned int nStepsBack) = 0;
	
	void add_input(const unsigned int address, double dWeight) 
		{ connections.add_input(nOrigin, dWeight); }
	void remove_input(const unsigned int address) { connections.remove_input(nOrigin); }
	void clear() { connections.clear(); }
	unsigned int get_ID() { return connections.ID; }
};

#endif

