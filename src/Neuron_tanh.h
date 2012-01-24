#ifndef Neuron_tanh_h
#define Neuron_tanh_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

class Neuron_tanh : public Neuron_base {
public:
	Neuron_tanh(  Index<Neuron_base::weight_type, Neuron_base::signal_type>& fIndex,
			Index<double,double>& bIndex,
			const Neuron_base::weight_type dBias)
		: Neuron_base("l", fIndex, bIndex, dBias) {}
	Neuron_tanh(const Neuron_tanh& rhs) = default;
	void fire();
	void backpropagate(const unsigned int steps_back=0);
};

//////////////////////////////////////////////
//////////////////////////////////////////////

void Neuron_tanh::fire() { 
	
}

void Neuron_tanh::backpropagate(const unsigned int steps_back) { 
	
}

#endif
