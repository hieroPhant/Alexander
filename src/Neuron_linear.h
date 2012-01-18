#ifndef Neuron_linear_h
#define Neuron_linear_h

class Neuron_linear : public Neuron_base {
public:
	Neuron_linear(  Index<double,double>& cIndex,
			const double dBias=0.0)
		: Neuron_base(cIndex, dBias) {}
	Neuron_linear(const Neuron_linear& rhs);
	void fire();
	void backpropagate(const unsigned int nStepsBack=0);
};

//////////////////////////////////////////////
//////////////////////////////////////////////

void Neuron_linear::fire() { //not finished (step sequence)
	using namespace std;
	msSignal.initializeStep(mtBias);	//initialize each current sample in Signal with the bias
	deque<Connection_base*>::iterator it = mqConnIn.begin();
	deque<Connection_base*>::iterator ite = mqConnIn.end();
	while(it!=ite) {
		//operator here
		//mark signal as received
		++it;
	}
	
	//call activation function on Signal and put the result in Output
	
	it = mqConnOut.begin();
	ite = mqConnOut.end();
	while(it!=ite) {
		//send iterator
		//mark outputs as sent
		++it;
	}
	return *this;
}

template<typename T>
void Neuron_linear::backpropagate(const unsigned int nStepsBack) { //not finished (step sequence)
	using namespace std;
	msBuffer.initializeStep(0.0);		//set all current samples in Buffer to zero
	deque<Connection_base*>::iterator it = mqConnOut.begin();
	deque<Connection_base*>::iterator ite = mqConnOut.end();
	while(it!=ite) {
		//call the output Neuron's operator derivative
		//mark error as received
		++it;
	}
	
	//call derivative of activation function and put the result in Error
	
	it = mqConnIn.begin();
	ite = mqConnIn.end();
	while(it!=ite) {
		(*it)->mbErrorFlag = true;	//mark errors as sent
		++it;
	}
	return *this;
}

#endif
