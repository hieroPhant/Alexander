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

#include "Alexander.h"

namespace alex {
	

	Neuron_base::Neuron_base(forward_node_index_type& fIndex,
				 backprop_index_type& bIndex,
				 information_index_type& iIndex,
				 const data_type bias, 
				 const bool trainable) 
		: forward_node(fIndex, bias), 
		  backprop_node(bIndex, std::make_pair(0.0, trainable), forward_node.ID), 
		  info_node(iIndex, forward_node.ID) {}
	
	Neuron_base::Neuron_base(const Neuron_base& rhs) 
		: forward_node(rhs.forward_node), 
		  backprop_node(rhs.backprop_node, forward_node.ID), 
		  info_node(rhs.info_node, forward_node.ID) {} //copy constructor
	
	Neuron_base::Neuron_base(Neuron_base&& rhs) 
		: forward_node( std::move(rhs.forward_node) ), 
		  backprop_node( std::move(rhs.backprop_node) ),
		  info_node( std::move(rhs.info_node) ) {} //move ctor
		  
	Neuron_base::Neuron_base& operator=(const Neuron_base& rhs) { 
		forward_node = rhs.forward_node;
		backprop_node = rhs.backprop_node;
		info_node = rhs.info_node;
	} 
	
	data_type Neuron_base::collect_signals() {
		data_type signal, state=forward_node.bias; 
		auto ip = forward_node.input_begin();
		auto ipe = forward_node.input_begin();
		while(ip != ipe) {
			ip >> signal;
			state += ip->weight * signal;
			++ip;
		}
		return state;
	}
	
	void Neuron_base::distribute_signals(const data_type output) {
		auto op = forward_node.output_begin();
		auto ope = forward_node.output_end();
		while(op != ope) {
			op << output;
			++op;
		}
	}
	
	gradient_type Neuron_base::collect_errors() {
		gradient_type gradient=0, partial; 
		auto ip = backprop_node.input_begin();
		auto ipe = backprop_node.input_end();
		while(ip != ipe) {
			ip >> partial;
			gradient += partial; //multiplied by weight at gradient source
			++ip;
		}
		return gradient;
	}
	
	void Neuron_base::distribute_errors(const gradient_type gradient) {
		auto op = backprop_node.output_begin(); 
		auto ope = backprop_node.output_end();
		auto fp = forward_node.input_begin();
		data_type old_output;
		while(op != ope) {
			fp >> old_output; //depends on Link saving old values
			op->weight->first = -learning_rate * gradient * old_output
					    + momentum * op->weight->first;
			op << gradient * fp->weight;
			++op;
		}
	}
	
	info_type Neuron_base::collect_value() {
		auto ip = info_node.input_begin();
		auto ipe = info_node.input_end();
		info_type link_value, neuron_value = 0;
		while(ip != ipe) {
			op >> link_value;
			neuron_value += link_value;
			++ip;
		}
		return neuron_value;
	}
	
	void Neuron_base::distribute_value() {
		auto op = info_node.output_begin();
		auto ope = info_node.output.end();
		while(op != ope) {
			if(op->weight->second) {
				//calculate value from mutual information
			}
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
	
	void Neuron_base::connect_info(const unsigned int address) {
		info_node.add_input(address, 0.0);
	}
	
	void Neuron_base::clear() {
		forward_node.clear();
		backprop_node.clear();
		info_node.clear();
	}
		
} //namespace alex

