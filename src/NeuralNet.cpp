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

#include "NeuralNet.h"
#include <map>

namespace alex {

	NeuralNet::NeuralNet(const NeuralNet& rhs) { 
		//copy all neurons and connections
		using namespace std;
		map<unsigned int, unsigned int> address_hash; //old : new
		
		auto it = rhs.neurons.begin();
		auto ite = rhs.neurons.end();
		while(it != ite) {
			switch(it->neuron_type) {
				case "l": add_linear(it->bias); break;
				case "s": add_sigmoid(it->bias); break;
				//case "t": add_tanh(it->bias); break;
				//case "g": add_gaussian(it->bias); break;
				default: cerr << "neuron_type not recognized" << endl; break;
			}
			address_hash.insert( make_pair( it->ID()->first, neurons.back().ID() ));
			++it;
		}
		
		unsigned int current_address;
		auto it = rhs.neurons.begin();
		auto ite = rhs.neurons.end();
		auto ip = it->input_begin();
		auto ipe = it->input_end();
		while(true) {
			current_address = address_hash[it->ID();
			while(ip != ipe) {
				//copying only input prevents Link duplicates
				connect(address_hash[ip->origin], current_address, ip->weight);
				++ip;
			}
			++it;
			if(it == ite) break;
			ip = it->input_begin();
			ipe = it->input_end();
		}
	}
	
	NeuralNet::NeuralNet(NeuralNet&& rhs) 
		: index(std::move(rhs.index)), neurons(std::move(rhs.neurons)) {}
	
	NeuralNet& NeuralNet::operator=(const NeuralNet& rhs) {
		if(this != &rhs) {
			//copy all neurons and connections
			NeuralNet temp(rhs);
			*this = std::move(temp);
		}
	}
	
	NeuralNet& NeuralNet::operator=(NeuralNet&& rhs) {
		if(this != &rhs) {
			index = std::move(rhs.index);
			neurons = std::move(rhs.neurons);
		}
	}	
		
	unsigned int NeuralNet::add_sigmoid(const Neuron_base::data_type bias, 
					    const bool trainable=true) {
		neurons.push_back( Neuron_sigmoid(forward, backward, bias, trainable) );
		return neurons.back().ID();
	}
	
	unsigned int NeuralNet::add_linear(const Neuron_base::data_type bias, 
					   const bool trainable=true) {
		neurons.push_back( Neuron_linear(forward, backward, bias, trainable) );
		return neurons.back().ID();
	}
	
	unsigned int NeuralNet::add_tanh(const Neuron_base::data_type bias, 
					 const bool trainable=true) {
		neurons.push_back( Neuron_tanh(forward, backward, bias, trainable) );
		return neurons.back().ID();
	}
	
	//unsigned int NeuralNet::add_gaussian(const Neuron_base::data_type bias, 
	//				     const bool trainable=true) {
	//	neurons.push_back( Neuron_gaussian(forward, backward, bias, trainable) );
	//	return neurons.back().ID();
	//}
	
	void NeuralNet::connect(const unsigned int origin, 
				const unsigned int target,
				const double weight,
				const bool trainable=true) {
		auto it = neurons.begin();
		auto ite = neurons.end();
		auto itt = it;
		unsigned int origin_layer = 0;
		while(it != ite) {
			if(it->ID() == origin) origin_layer = it->layer();
			else if(it->ID() == target) {
				it->add_input(origin, weight, trainable);
				itt = it;
			}
			
			if(done && origin_layer != 0) break;
			++it;
		}
		itt->shift_layer(origin_layer+1);
		neurons.sort();
		return;
	}
		
	void NeuralNet::run() {
		auto it = neurons.begin();
		auto ite = neurons.end();
		while(it != ite) {
			it->fire();
			++it;
		}
	}
	
	void NeuralNet::train() {
		auto it = neurons.rbegin();
		auto ite = neurons.rend();
		while(it != ite) {
			it->backpropagate();
			++it;
		}
	}
	
} //namespace alex
