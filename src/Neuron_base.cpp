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

#include "Neuron_base.h"
#include "Neuron_tanh.h"
#include "Neuron_sigmoid.h"
#include "Neuron_linear.h"
#include "Neuron_gaussian.h"

namespace alex {
	
	//typedef std::pair<double,bool> weight_type;
	//typedef double signal_type;
	
	Neuron_base::Neuron_base(const char chNeuron_type) 
		: forward( std::make_pair(0.0, true) ), backward(0.0, forward.ID),
			neuron_type(chNeuron_type) {}
	
	Neuron_base::Neuron_base(const char chNeuron_type, const Neuron_base::weight_type tBias)
		: forward(tBias), backward(tBias->first, forward.ID), neuron_type(chNeuron_type) {}
	
	Neuron_base::Neuron_base(const char chNeuron_type,
				 Index<Neuron_base::weight_type, Neuron_base::signal_type>& fIndex,
				 Index<double,double>& bIndex,
				 const Neuron_base::weight_type tBias) 
		: forward(fIndex, tBias), backward(bIndex, tBias->first, forward.ID), 
			neuron_type(chNeuron_type) {}
	
	Neuron_base::Neuron_base(const Neuron_base& rhs) 
		: forward(rhs.forward), backward(rhs.backward, forward.ID), 
			state(rhs.state), neuron_type(rhs.neuron_type) {} 
	
	Neuron_base::Neuron_base(Neuron_base&& rhs) 
		: forward( std::move(rhs.forward) ), 
		  backward( std::move(rhs.backward) ),
		  state( std::move(rhs.state) ) {}
		  
	Neuron_base::Neuron_base& operator=(const Neuron_base& rhs) { 
		forward = rhs.forward;
		backward = rhs.backward;
		state = rhs.state; 
	}
	
	Neuron_base::~Neuron_base() {}
	
	void Neuron_base::add_input(const unsigned int address, 
				    Neuron_base::weight_type tWeight) {
		forward.add_input(address, tWeight);
		backward.add_output(address, tWeight); 
	}
	
	void Neuron_base::remove_input(const unsigned int address) {
		forward.remove_input(address);
		backward.remove_output(address); 
	}
	
	void Neuron_base::clear() {
		forward.clear();
		backward.clear();
		state.clear();
	}
		
} //namespace alex
