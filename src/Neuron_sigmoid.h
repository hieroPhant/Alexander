#ifndef Neuron_sigmoid_h
#define Neuron_sigmoid_h

class Neuron_linear : public Neuron_base {
private:
	Node<double,double> neighbors; //need a way to automatically connect to all others

public:
	Neuron_linear(  Index<double,double>& cIndex,
			const double dBias=0.0)
		: Neuron_base(cIndex, dBias) {}
	Neuron_linear(const Neuron_linear& rhs);
	void fire();
	void backpropagate(const unsigned int nStepsBack=0);
};

/////////////////////////////////////
/////////////////////////////////////
void fire() {
	
}

void backpropagate(const unsigned int nStepsBack) {
	
}

#endif
