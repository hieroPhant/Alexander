#ifndef Neuron_linear_h
#define Neuron_linear_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

class Neuron_linear : public Neuron_base {
public:
	Neuron_linear(  Index<Neuron_base::weight_type, Neuron_base::signal_type>& fIndex,
			Index<double,double>& bIndex,
			const Neuron_base::weight_type dBias)
		: Neuron_base("l", fIndex, bIndex, dBias) {}
	Neuron_linear(const Neuron_linear& rhs) = default;
	void fire();
	void backpropagate(const unsigned int steps_back=0);
};

//////////////////////////////////////////////
//////////////////////////////////////////////

void Neuron_linear::fire() { 
	
}

void Neuron_linear::backpropagate(const unsigned int steps_back) { 
	
}

#endif
