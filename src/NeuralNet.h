#ifndef NeuralNet_h
#define NeuralNet_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

#include <list>

namespace alex {

	class NeuralNet {
	private:
		Index< std::pair<double,bool>, double> forward_index;
		Index<double,double> backward_index;
		std::map<unsigned int, unsigned int>
		std::list<Neuron_base> neurons;
	
	public:
		NeuralNet() = default;
		NeuralNet(const NeuralNet& rhs);
		NeuralNet(NeuralNet&& rhs);
		NeuralNet& operator=(const NeuralNet& rhs);
		NeuralNet& operator=(NeuralNet&& rhs);
		~NeuralNet() = default;
		
		unsigned int add_sigmoid(const double bias, const bool trainable=true);
		unsigned int add_linear(const double bias, const bool trainable=true);
		
		void connect(const unsigned int origin, 
			     const unsigned int target,
			     const double weight,
			     const bool trainable=true);
		void connect(const unsigned int origin,
			     const unsigned int target,
			     const std::pair<double, bool> weight)
		
		void run();
		void train();
	}; //class NeuralNet
	
} //namespace alex

#endif

