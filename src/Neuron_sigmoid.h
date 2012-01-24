#ifndef Neuron_sigmoid_h
#define Neuron_sigmoid_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

class Neuron_sigmoid : public Neuron_base {
public:
	Neuron_sigmoid(Index<Neuron_base::weight_type, Neuron_base::signal_type>& fIndex,
		       Index<double,double>& bIndex,
		       const Neuron_base::weight_type dBias)
		: Neuron_base("s", fIndex, bIndex, dBias) {}
	Neuron_sigmoid(const Neuron_sigmoid& rhs) = default;
	void fire();
	void backpropagate(const unsigned int steps_back=0);
};

/////////////////////////////////////
/////////////////////////////////////

void Neuron_sigmoid::fire() {
	
}

void Neuron_sigmoid::backpropagate(const unsigned int steps_back) {
	
}

#endif
