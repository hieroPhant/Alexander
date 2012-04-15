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
	
	NeuralNet::NeuralNet(const char* pfilename) {
		using namespace std;
		
		switch( build_network(pfilename) ) {
			case 0: cout << "Network parse succeeded." << endl; 	break;
			case 1: break;
			case 2: cout << "Misplaced input neuron." << endl; 	break;
			case 3: cout << "Bad hidden neuron." << endl; 		break;
			case 4: cout << "Bad output neuron." << endl; 		break;
			case 5: cout << "Bad hidden link." << endl;		break;
			case 6: cout << "Bad output link." << endl;		break;
			default: cout << "Unknown error parsing network" << endl;
		}
	}
	
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
	
	NeuralNet::~NeuralNet() {
		clear();
	}
	
	void NeuralNet::run() {
		//this method executes the entire network once, or forward one step
		//need to figure out where data comes from, 
		//and where to put the results
		
		auto iti = input_layer.begin();
		auto itie = input_layer.end();
		while(iti != itie) { //each input neuron
			//iti->feed_signal(); //needs an argument and some data
			++iti;
		}
		
		auto ith = hidden_layers.begin();
		auto ithe = hidden_layers.end();
		std::vector< Neuron_base* >::iterator itl, itle;
		while(ith != ithe) { //each layer
			itl = ith->begin();
			itle = ith->end();
			while(itl != itle) { //each neuron in a layer
				(*itl)->fire(); 
				++itl;
			}
			++ith;
		}
		
		auto ito = output_layer.begin();
		auto itoe = output_layer.end();
		while(ito != itoe) { //each output neuron
			(*ito)->fire(); //do something with this return value
			++ito;
		}
	}
	
	void NeuralNet::backpropagate() {
		//this method steps the network backward once
		//need to figure out where supervisory data comes from
		
		auto ito = output_layer.rbegin();
		auto itoe = output_layer.rend();
		while(ito != itoe) { //each output neuron
			(*ito)->train(); //needs argument and from supervisory data
			++ito;
		}
		
		auto ith = hidden_layers.rbegin();
		auto ithe = hidden_layers.rend();
		std::vector< Neuron_base* >::reverse_iterator itl, itle;
		while(ith != ithe) { //each layer
			itl = ith->rbegin();
			itle = ith->rend();
			while(itl != itle) { //each neuron in a layer
				(*itl)->train();
				++itl;
			}
			++ith;
		}
		
		auto iti = input_layer.rbegin();
		auto itie = input_layer.rend();
		while(iti != itie) { //each input neuron
			iti->take_gradient(); //is this necessary?
			++iti;
		}
	}
	
	int NeuralNet::build_network(const char* pfilename) {
		using namespace pugi;
		using namespace std;
		
		//parse xml document
		xml_document doc;
		xml_parse_result result = doc.load_file(pfilename);
		if(!result) {
			cout << "XML parsed with errors, attr value: [" 
			     << doc.child("node").attribute("attr").value() 
			     << "]" << endl;
    			cout << "Error description: " << result.description() << endl;
    			cout << "Error offset: " << result.offset 
    			     << " (error at [..." << (pfilename + result.offset) 
    			     << "]" << endl << endl;
    			return 1;
		}
		
		//make sure network is empty to start
		clear();
		
		///////////////////// first pass for basic checks
		//initial parse, counting objects
		xml_node network = doc.child("network");
		unsigned int layers = 0;
		//vector<unsigned int> neurons_in_layers;
		for(xml_node layer = network.child("layer");
		    layer;
		    layer = layer.next_sibling("layer")) {
		    	
		    	//neurons_in_layers.push_back(0);
		    	for(xml_node neuron = layer.child("neuron");
		    	    neuron;
		    	    neuron = neuron.next_sibling("neuron")) {
		    	    
		    	    	//++neurons_in_layers[layers];
		    	    	string type = neuron.attribute("type").value();
		    	    	if( (layers==0) != (type=="input") ) return 2;
		    	}
		    	
		    	++layers;
		}
		
		////////////////////// second pass to create neurons
		//build input layer
		xml_node layer = network.child("layer");
		unsigned int ID;
		for(xml_node neuron = layer.child("neuron"); 
		    neuron; 
		    neuron = neuron.next_sibling("neuron")) 
			input_layer.push_back( Neuron_input(neuron, 
							    forward_index, 
							    backprop_index) ); 
		
		//hidden layers
		hidden_layers.resize(layers - 2); //number of layers excluding i/o
		auto itl = hidden_layers.begin();
		auto itle = hidden_layers.end();
		while(itl != itle) {
			layer = layer.next_sibling("layer");
			
			for(xml_node neuron = layer.child("neuron"); 
			    neuron; 
			    neuron = neuron.next_sibling("neuron"))
				if( !create_neuron(neuron, *itl) ) return 3;
			
			++itl;
		}
		
		//output layer
		layer = layer.next_sibling("layer");
		for(xml_node neuron = layer.child("neuron"); 
		    neuron; 
		    neuron = neuron.next_sibling("neuron")) 
			if( !create_neuron(neuron, output_layer) ) return 4;
		
		//////////////////// third pass to create links
		//inputs to hidden layers
		layer = network.child("layer");
		layer = layer.next_sibling("layer"); //starting at first hidden layer
		xml_node neuron;
		
		vector< Neuron_base* >::iterator itn, itne;
		itl = hidden_layers.begin();
		itle = hidden_layers.end();
		while(itl != itle) {
		    	
		    	neuron = layer.child("neuron");
		    	
		    	itn = itl->begin();
		    	itne = itl->end();
			while(itn != itne) {

				for(xml_node link = neuron.child("link");
				    link;
				    link = link.next_sibling("link"))
					if( !(*itn)->add_input(link) ) return 5;
				
				neuron = neuron.next_sibling("neuron");
				++itn;
			}
			
			layer = layer.next_sibling("layer");
			++itl;
		}
		
		//inputs to output layer
		neuron = layer.child("neuron");
		
		itn = output_layer.begin();
		itne = output_layer.end();
		while(itn != itne) {
			
			for(xml_node link = neuron.child("link");
			    link;
			    link = link.next_sibling("link"))
				if( !(*itn)->add_input(link) ) return 6;
			
			neuron = neuron.next_sibling("neuron");
			++itn;
		}
		
		return 0;
	}
	
	bool NeuralNet::create_neuron(pugi::xml_node neuron, 
				      std::vector< Neuron_base* >& layer) {
		using namespace pugi;
		
		std::string type = neuron.attribute("type").value();
		Neuron_base* ptr;
		if(type == "linear")
			ptr = new Neuron_linear(neuron, forward_index, backprop_index);
		else if(type == "sigmoid")
			ptr = new Neuron_sigmoid(neuron, forward_index, backprop_index);
		else return false;
		
		layer.push_back(ptr);
		
		return true;
	}
	
	void NeuralNet::clear() {
	
		std::vector< Neuron_base* >::iterator itn, itne;
		auto itl = hidden_layers.begin();
		auto itle = hidden_layers.end();
		while(itl != itle) {
			
			itn = itl->begin();
			itne = itl->end();
			while(itn != itne) {
				delete *itn;
				*itn = NULL;
				++itn;
			}
			++itl;
		}
		
		itn = output_layer.begin();
		itne = output_layer.end();
		while(itn != itne) {
			delete *itn;
			*itn = NULL;
			++itn;
		}
		
		input_layer.clear();
	}

} //namespace alex

