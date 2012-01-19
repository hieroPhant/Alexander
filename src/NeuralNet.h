#ifndef NeuralNet_h
#define NeuralNet_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

#include <list>
#include <map> //used temporarily for copying

namespace alex {

	class NeuralNet {
	private:
		Index<double,double> index;
		std::list< Neuron_base > neurons;
	
	public:
		NeuralNet() = default;
		NeuralNet(const NeuralNet& rhs);
		NeuralNet(NeuralNet&& rhs);
		NeuralNet& operator=(const NeuralNet& rhs);
		NeuralNet& operator=(NeuralNet&& rhs);
		~NeuralNet() = default;
		
		void run();
		void train();
	}; //class NeuralNet
	
} //namespace alex

#endif

