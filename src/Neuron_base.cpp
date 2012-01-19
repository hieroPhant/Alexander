//(c) Jack Hall 2011, licensed under GNU GPL v3

#include "Neuron_base.h"

namespace alex {
	
	//typedef std::pair<double,bool> weight_type;
	//typedef double signal_type;
	
	Neuron_base::Neuron_base() 
		: forward( std::make_pair(0.0, true) ), backward(0.0) {}
	
	Neuron_base::Neuron_base(const Neuron_base::weight_type tBias)
		: forward(tBias), backward(tBias->first) {}
	
	Neuron_base::Neuron_base(const Neuron_base& rhs) 
		: forward(rhs.forward), backward(rhs.backward), state(rhs.state) {}
	
	Neuron_base::Neuron_base(Neuron_base&& rhs) 
		: forward( std::move(rhs.forward) ), 
		  backward( std::move(rhs.backward) ),
		  state( std::move(rhs.state) ) {}
		  
	Neuron_base::Neuron_base& operator=(const Neuron_base& rhs) {
		forward = std::move(rhs.forward);
		backward = std::move(rhs.backward);
		state = std::move(rhs.state);
	}
	
	Neuron_base::~Neuron_base() {}
	
	void Neuron_base::add_input(const unsigned int address, Neuron_base::weight_type tWeight) {
		forward.add_input(address, tWeight);
		backward.add_output(address, tWeight); //different address!
	}
	
	void Neuron_base::remove_input(const unsigned int address) {
		forward.remove_input(address);
		backward.remove_output(address); //different address!
	}
	
	void Neuron_base::clear() {
		forward.clear();
		backward.clear();
		state.clear();
	}
		
} //namespace alex
