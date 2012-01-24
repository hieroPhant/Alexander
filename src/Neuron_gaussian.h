#ifndef Neuron_gaussian_h
#define Neuron_gaussian_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

class Neuron_gaussian : public Neuron_base {
public:
	Neuron_gaussian(  Index<Neuron_base::weight_type, Neuron_base::signal_type>& fIndex,
			Index<double,double>& bIndex,
			const Neuron_base::weight_type dBias)
		: Neuron_base("l", fIndex, bIndex, dBias) {}
	Neuron_gaussian(const Neuron_gaussian& rhs) = default;
	void fire();
	void backpropagate(const unsigned int steps_back=0);
};

//////////////////////////////////////////////
//////////////////////////////////////////////

void Neuron_gaussian::fire() { 
	
}

void Neuron_gaussian::backpropagate(const unsigned int steps_back) { 
	
}

#endif
