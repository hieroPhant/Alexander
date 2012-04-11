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

//g++ -std=c++0x -fPIC -I../Benoit/src -oNeuron_base.o Neuron_base.cpp

#include "Neuron_base.h"

namespace alex {
	
	Neuron_base::Neuron_base(forward_index_type& fIndex,
				 backprop_index_type& bIndex,
				 const data_type bias, 
				 const bool trainable) 
		: forward_node(fIndex, bias), 
		  backprop_node(bIndex, std::make_pair(0.0, trainable), forward_node.ID) {}
	
	Neuron_base::Neuron_base(const Neuron_base& rhs) 
		: forward_node(rhs.forward_node), 
		  backprop_node(rhs.backprop_node, forward_node.ID),
		  state(rhs.state), 
		  output(rhs.output),
		  learning_rate(rhs.learning_rate),
		  momentum(rhs.momentum) {} //copy constructor
	
	Neuron_base::Neuron_base(Neuron_base&& rhs) 
		: forward_node( std::move(rhs.forward_node) ), 
		  backprop_node( std::move(rhs.backprop_node) ),
		  state(rhs.state), 
		  output(rhs.output),
		  learning_rate(rhs.learning_rate),
		  momentum(rhs.momentum) {} //move ctor
		  
	Neuron_base& Neuron_base::operator=(const Neuron_base& rhs) { 
		forward_node = rhs.forward_node;
		backprop_node = rhs.backprop_node;
		state = rhs.state;
		output = rhs.output;
		learning_rate = rhs.learning_rate;
		momentum = rhs.momentum;
		return *this;
	} 
	
	Neuron_base::~Neuron_base() = default;
	
	void Neuron_base::collect_signals() {
		//computes the dot product between weights and incoming signals,
		//storing the result in 'state'
	
		data_type signal; 
		state = forward_node.bias; 
		auto ip = forward_node.input_begin();
		auto ipe = forward_node.input_begin();
		while(ip != ipe) {
			ip >> signal;
			state += ip->weight * signal;
			++ip;
		}
	}
	
	void Neuron_base::distribute_signals() {
		//sends contents of 'output' to all output links
		auto op = forward_node.output_begin();
		auto ope = forward_node.output_end();
		while(op != ope) {
			op << output;
			++op;
		}
	}
	
	data_type Neuron_base::collect_errors() {
		//collects and sums the backpropagating gradients
		data_type gradient=0.0, partial; 
		auto ip = backprop_node.input_begin();
		auto ipe = backprop_node.input_end();
		while(ip != ipe) {
			ip >> partial;
			gradient += partial; //multiplied by weight at gradient source
			++ip;
		}
		return gradient;
	}
	
	void Neuron_base::distribute_errors(const data_type gradient) {
		//calculates gradient for both weights and signals,
		//transmitting the latter backward
		auto op = backprop_node.output_begin(); 
		auto ope = backprop_node.output_end();
		auto fp = forward_node.input_begin();
		data_type old_output;
		while(op != ope) {
			fp >> old_output; //depends on Link saving old values
			if(op->weight.second) {
				//when to multiply by momentum?
				op->weight.first *= momentum;
				op->weight.first -= learning_rate * gradient * old_output;
			}
			op << gradient * fp->weight;
			++op;
		}
	}
	
	data_type Neuron_base::fire() {
		collect_signals();
		output = f(state);
		distribute_signals();
		return output;
	}
	
	void Neuron_base::train() {
		train( collect_errors() );
	}
	
	void Neuron_base::train(data_type gradient) {
		gradient *= df(state);
		
		//update bias delta
		backprop_node.bias.first *= momentum;
		backprop_node.bias.first += -learning_rate * gradient;
		
		distribute_errors(gradient);
	}
	
	void Neuron_base::set_rates(const data_type rate, const data_type factor) {
		learning_rate = rate;
		momentum = factor;
	}
	
	void Neuron_base::update_weights() {
		if(backprop_node.bias.second) {
			forward_node.bias += backprop_node.bias.first;
			backprop_node.bias.first = 0.0;	
		}
		
		auto fp = forward_node.input_begin();
		auto fpe = forward_node.input_end();
		auto bp = backprop_node.output_begin();
		while(fp != fpe) {
			if(bp->weight.second) {
				fp->weight += bp->weight.first;
			}
			++fp;
			++bp;
		}
	}
	
	void Neuron_base::add_input(const ID_type address, 
				    const data_type weight,
				    const bool trainable) {
		forward_node.add_input(address, weight);
		backprop_node.add_output(address, std::make_pair(0.0, trainable)); 
	}
	
	void Neuron_base::remove_input(const ID_type address) {
		forward_node.remove_input(address);
		backprop_node.remove_output(address); 
	}
	
	void Neuron_base::clear() {
		forward_node.clear();
		backprop_node.clear();
	}
		
} //namespace alex

