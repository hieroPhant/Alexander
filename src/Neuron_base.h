#ifndef Neuron_base_h
#define Neuron_base_h

/*
    Alexander: a neural networks library
    Copyright (C) 2011  Jack Hall

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <deque>

namespace alex {

	class Neuron_base {
	public:
		typedef std::pair<double,bool> weight_type;
		typedef double signal_type;
		const char neuron_type; //FIELD

		Neuron_base() = delete;
		explicit Neuron_base(const char chNeuron_type); 
		Neuron_base(const char chNeuron_type, const weight_type tBias);
		Neuron_base(const char chNeuron_type,
			    Index<weight_type, signal_type>& fIndex, 
			    Index<double,double>& bIndex, 
			    const weight_type tBias);
		Neuron_base(const Neuron_base& rhs);
		Neuron_base(Neuron_base&& rhs);
		Neuron_base& operator=(const Neuron_base& rhs);
		Neuron_base& operator=(Neuron_base&& rhs) = delete;
		virtual ~Neuron_base();
	
		virtual void fire() = 0;
		virtual void backpropagate(const unsigned int steps_back=0) = 0;
	
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

