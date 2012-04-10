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

namespace alex {
	
	NeuralNet::NeuralNet(NeuralNet&& rhs) 
		: input_layer( std::move(rhs.input_layer) ),
		  hidden_layers( std::move(rhs.hidden_layers) ),
		  output_layer( std::move(rhs.output_layer) ),
		  forward_index( std::move(rhs.forward_index) ),
		  backprop_index( std::move(rhs.backprop_index) ) {}
	
	NeuralNet& NeuralNet::operator=(NeuralNet&& rhs) {
		input_layer = std::move(rhs.input_layer);
		hidden_layers = std::move(rhs.hidden_layers);
		output_layer = std::move(rhs.output_layer);
		forward_index = std::move(rhs.forward_index);
		backprop_index = std::move(rhs.backprop_index);
		return *this;
	}
	
	NeuralNet::~NeuralNet() = default;
	
	void NeuralNet::run() {
		//this method executes the entire network once, or forward one step
		//need to figure out where data comes from, and where to put the results
		
		auto iti = input_layer.begin();
		auto itie = input_layer.end();
		while(iti != itie) { //each input neuron
			iti->feed_signal(); //needs an argument and some data
			++iti;
		}
		
		auto ith = hidden_layers.begin();
		auto ithe = hidden_layers.end();
		vector<Neuron_base>::iterator itl, itle;
		while(ith != ithe) { //each layer
			itl = ith->begin();
			itle = ith->end();
			while(itl != itle) { //each neuron in a layer
				itl->fire();
				++itl;
			}
			++ith;
		}
		
		auto ito = output_layer.begin();
		auto itoe = output_layer.end();
		while(ito != itoe) { //each output neuron
			ito->fire(); //do something with this return value
			++ito;
		}
	}
	
	void NeuralNet::backpropagate() {
		//this method steps the network backward once
		//need to figure out where supervisory data comes from
		
		auto ito = output_layer.rbegin();
		auto itoe = output_layer.rend();
		while(ito != itoe) { //each output neuron
			ito->train(); //needs argument and from supervisory data
			++ito;
		}
		
		auto ith = hidden_layers.rbegin();
		auto ithe = hidden_layers.rend();
		vector<Neuron_base>::iterator itl, itle;
		while(ith != ithe) { //each layer
			itl = ith->rbegin();
			itle = ith->rend();
			while(itl != itle) { //each neuron in a layer
				itl->train();
				++itl;
			}
			++ith;
		}
		
		auto iti = input_layer.rbegin();
		auto itie = input_layer.rend();
		while(iti != itie) { //each input neuron
			iti->take_gradient(); //is this necessary? what is being trained?
			++iti;
		}
	}

} //namespace alex
