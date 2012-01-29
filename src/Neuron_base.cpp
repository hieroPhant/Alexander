/*
    Alexander: a neural networks library
    Copyright (C) 2011-2012  Jack Hall

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
    
    e-mail: jackwhall7@gmail.com
*/

#include "Neuron_base.h"
#include "Neuron_tanh.h"
#include "Neuron_sigmoid.h"
#include "Neuron_linear.h"
//#include "Neuron_gaussian.h"

namespace alex {
	
	//typedef double data_type;
	//typedef std::pair<data_type, bool> weight_type;
	//typedef std::deque<data_type>::iterator signal_type;
	
	Neuron_base::Neuron_base(const char chNeuron_type) 
		: forward(0.0), backward( std::make_pair(0.0, true), forward.ID ),
		  neuron_type(chNeuron_type), learning_rate(0.0) {} 
	
	Neuron_base::Neuron_base(const char chNeuron_type, 
				 const Neuron_base::data_type tBias,
				 const bool bTrainable=true)
		: forward(tBias), backward( std::make_pair(0.0, bTrainable), forward.ID ), 
		  neuron_type(chNeuron_type), learning_rate(0.0) {}
	
	Neuron_base::Neuron_base(const char chNeuron_type,
				 Index<Neuron_base::data_type, Neuron_base::signal_type>& fIndex,
				 Index<Neuron_base::error_type, Neuron_base::data_type>& bIndex,
				 const Neuron_base::data_type tBias, const bool bTrainable=true) 
		: forward(fIndex, tBias), 
		  backward(bIndex, std::make_pair(0.0, bTrainable), forward.ID), 
		  neuron_type(chNeuron_type), learning_rate(0.0) {}
	
	Neuron_base::Neuron_base(const Neuron_base& rhs) 
		: forward(rhs.forward), backward(rhs.backward, forward.ID), state(rhs.state), 
		  output(rhs.output), neuron_type(rhs.neuron_type), 
		  learning_rate(rhs.learning_rate) {} //copy constructor
	
	Neuron_base::Neuron_base(Neuron_base&& rhs) 
		: forward( std::move(rhs.forward) ), backward( std::move(rhs.backward) ),
		  state( std::move(rhs.state) ), output( std::move(rhs.output) ),
		  learning_rate(rhs.learning_rate) {} //move ctor
		  
	Neuron_base::Neuron_base& operator=(const Neuron_base& rhs) { 
		forward = rhs.forward;
		backward = rhs.backward;
		state = rhs.state; 
		output = rhs.output;
		learning_rate = rhs.learning_rate;
	} 
	
	Neuron_base::~Neuron_base() {}
	
	bool Neuron_base::operator<(const Neuron_base& rhs) const {
		if(layer == rhs.layer) return ID() < rhs.ID();
		else return layer < rhs.layer;
	}
	
	void Neuron_base::fire() {
		signal_type signal; 
		data_type energy = forward.bias;
		auto ip = forward.input_begin();
		auto ipe = forward.input_begin();
		while(ip != ipe) {
			ip >> signal;
			energy += ip->weight * (*signal);
			++ip;
		}
		
		if( state.capacity() == state.size() ) 
			std::cerr << "Overran neuron buffer" << std::endl;
		state.push_back(energy);
		output.push_back( f(energy) );
	
		auto op = forward.output_begin();
		auto ope = forward.output_end();
		while(op != ope) {
			op << output.begin();
			++op;
		}
	}
	
	void Neuron_base::backpropagate() {
		data_type gradient, partial = 0; 
		data_type past_output = output.back(), past_energy = state.back();
		output.pop_back();
		state.pop_back();
		
		auto ip = backward.input_begin();
		auto ipe = backward.input_end();
		auto fp = forward.output_begin();
		while(ip != ipe) {
			ip >> partial;
			ip->weight->first += partial * past_output; //past gradients
			gradient += partial * fp->weight;
			++ip;
			++fp;
		}
	
		double derivative = df( past_energy ) * gradient; 
		backward.bias->first += derivative;
	
		auto op = backward.output_begin();
		auto ope = backward.output_end();
		while(op != ope) {
			op << derivative;
			++op;
		}
	}
	
	void Neuron_base::update_weights() {
		if(backward.bias->second) {
			forward.bias += learning_rate * backward.bias->first;
			backward.bias->first = 0.0;	
		}
	
		auto fp = forward.input_begin();
		auto fpe = forward.input_end();
		auto bp = backward.output_begin();
		while(fp != fpe) {
			if(bp->weight->second) {
				fp->weight += learning_rate * bp->weight->first;
				bp->weight->first = 0.0;
			}
			++fp;
			++bp;
		}
	}
	
	void Neuron_base::prepare_steps(const unsigned int steps) {
		state.reserve(steps);
		output.reserve(steps);
	}
	
	void Neuron_base::add_input(const unsigned int address, 
				    const Neuron_base::weight_type weight,
				    const bool trainable) {
		forward.add_input(address, weight);
		backward.add_output(address, std::make_pair(0.0, trainable)); 
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
	
	void Neuron_base::shift_layer(const unsigned int new_layer) {
		layer = new_layer; //need to shift layers of outputs
	}
		
} //namespace alex

