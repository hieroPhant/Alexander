#ifndef Neuron_base_h
#define Neuron_base_h
//(c) Jack Hall 2011, licensed under GNU GPL v3

#include <iostream>
#include <deque>
#include "Benoit.h"
namespace alex {

	class Neuron_base {
	public:
		typedef std::pair<double,bool> weight_type;
		typedef double signal_type;

		Neuron_base(); 
		Neuron_base(const signal_type tBias);
		Neuron_base(const Neuron_base& rhs);
		Neuron_base(Neuron_base&& rhs);
		Neuron_base& operator=(const Neuron_base& rhs);
		Neuron_base& operator=(Neuron_base&& rhs)=delete;
		virtual ~Neuron_base();
	
		virtual void fire() = 0;
		virtual void backpropagate(const unsigned int nStepsBack) = 0;
	
		void add_input(const unsigned int address, const weight_type tWeight);
		void remove_input(const unsigned int address); 
		void clear();
		unsigned int ID() const { return forward.ID; }
		
	protected:
		Node<weight_type, signal_type> forward; //FIELD
		Node<double, signal_type> backward; //FIELD
		std::deque<signal_type> state; //FIELD
	}; //class Neuron_base

} //namespace alex

#endif

