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
		: forward_node(0.0), 
		  backprop_node( std::make_pair(0.0, true), forward_node.ID ),
		  neuron_type(chNeuron_type), learning_rate(0.0) {} 
	
	Neuron_base::Neuron_base(const char chNeuron_type, 
				 const data_type tBias,
				 const bool bTrainable)
		: forward_node(tBias),
		  backprop_node( std::make_pair(0.0, bTrainable), forward_node.ID ), 
		  neuron_type(chNeuron_type), learning_rate(0.0) {}
	
	Neuron_base::Neuron_base(const char chNeuron_type,
				 forward_node_index_type&   fIndex,
				 backprop_index_type&  bIndex,
				 const data_type tBias, 
				 const bool bTrainable) 
		: forward_node(fIndex, tBias), 
		  backprop_node(bIndex, std::make_pair(0.0, bTrainable), forward_node.ID), 
		  neuron_type(chNeuron_type), learning_rate(0.0) {}
	
	Neuron_base::Neuron_base(const Neuron_base& rhs) 
		: forward_node(rhs.forward_node), 
		  backprop_node(rhs.backprop_node, forward_node.ID), state(rhs.state), 
		  output(rhs.output), neuron_type(rhs.neuron_type), 
		  learning_rate(rhs.learning_rate) {} //copy constructor
	
	Neuron_base::Neuron_base(Neuron_base&& rhs) 
		: forward_node( std::move(rhs.forward_node) ), 
		  backprop_node( std::move(rhs.backprop_node) ),
		  state( std::move(rhs.state) ), output( std::move(rhs.output) ),
		  learning_rate(rhs.learning_rate) {} //move ctor
		  
	Neuron_base::Neuron_base& operator=(const Neuron_base& rhs) { 
		forward_node = rhs.forward_node;
		backprop_node = rhs.backprop_node;
		state = rhs.state; 
		output = rhs.output;
		learning_rate = rhs.learning_rate;
	} 
	
	Neuron_base::~Neuron_base() {}
	
	bool Neuron_base::operator<(const Neuron_base& rhs) const {
		return ID() < rhs.ID();
	}
	
	void Neuron_base::fire() { //update ben::Link behavior
		signal_type signal; 
		state = forward_node.bias;
		auto ip = forward_node.input_begin();
		auto ipe = forward_node.input_begin();
		while(ip != ipe) {
			ip >> signal;
			state += ip->weight * signal;
			++ip;
		}
		
		output = f(state);
	
		auto op = forward_node.output_begin();
		auto ope = forward_node.output_end();
		while(op != ope) {
			op << output;
			++op;
		}
	}
	
	void Neuron_base::backpropagate() { //update ben::Link behavior
		gradient_type gradient=0, partial=0; 
		
		auto ip = backprop_node.input_begin();
		auto ipe = backprop_node.input_end();
		auto fp = forward_node.output_begin();
		while(ip != ipe) {
			ip >> partial;
			ip->weight->first += partial * output; //output links
			gradient += partial * fp->weight;
			++ip;
			++fp;
		}
	
		gradient_type derivative = df(energy) * gradient; 
		backprop_node.bias->first = -learning_rate*derivative 
					    + momentum*backprop_node.bias->first;
	
		auto op = backprop_node.output_begin();
		auto ope = backprop_node.output_end();
		while(op != ope) {
			op << derivative;
			++op;
		}
	}
	
	void Neuron_base::update_weights() {
		if(backprop_node.bias->second) {
			forward_node.bias += backprop_node.bias->first;
			backprop_node.bias->first = 0.0;	
		}
	
		auto fp = forward_node.input_begin();
		auto fpe = forward_node.input_end();
		auto bp = backprop_node.output_begin();
		while(fp != fpe) {
			if(bp->weight->second) {
				fp->weight += learning_rate * bp->weight->first;
				bp->weight->first = 0.0;
			}
			++fp;
			++bp;
		}
	}
	
	void Neuron_base::add_input(const unsigned int address, 
				    const data_type weight,
				    const bool trainable) {
		forward_node.add_input(address, weight);
		backprop_node.add_output(address, std::make_pair(0.0, trainable)); 
	}
	
	void Neuron_base::remove_input(const unsigned int address) {
		forward_node.remove_input(address);
		backprop_node.remove_output(address); 
	}
	
	void Neuron_base::clear() {
		forward_node.clear();
		backprop_node.clear();
		state.clear();
	}
		
} //namespace alex

