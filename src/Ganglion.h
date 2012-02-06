#ifndef Ganglion_h
#define Ganglion_h

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

#include <list>
#include <vector>

namespace alex {
	
	class Ganglion {
	public:	
		const unsigned int layer, ID; //these need to be initialized first
		
	private:
		lateral_index_type   lateral_index;
		forward_index_type   forward_index;
		backprop_index_type  backprop_index;
		
		forward_node_type   forward_node;
		backprop_node_type  backprop_node;
		info_node_type 	    information_node;
		
		vector<Input_Neuron> inputs;
		list<SOM_Neuron> neurons;
		Output_Neuron output;
		vector<unsigned int> activated_neurons;
		//neighborhood function needed
		//could depend on: 	sharpness of sigmoid (magnitude of weights)
		//			information transmitted by Ganglion 
		//			maturity of Ganglion (general magnitude of errors)
		//			discrepancy between neighbors
		
		//need functions to describe tendency of SOM_Neurons to divide/die
		
		//to evolve: neighborhood function, birth/death function
		
		void connect_cell(const unsigned int address);
		
	public:		
		Ganglion() = delete;
		Ganglion(forward_index_type& fIndex,
			 backprop_index_type& bIndex,
			 info_index_type& iIndex);
		Ganglion(const Ganglion& rhs) = delete;
		Ganglion& operator=(const Ganglion& rhs) = delete;
		~Ganglion() = default;
		
		friend void SOM_Neuron::initialize(Ganglion& parent);
		
		void add_input(	const unsigned int address, const data_type weight, 
				const bool trainable=true); 
		void remove_input(const unsigned int address); 
		unsigned int ID() const { return forward_node.ID; }
		
		void run(); //find peak of activity and evaluate that neuron+neighbors
		void backpropagate(); //only train activated neurons+neighbors
		
	}; //class Ganglion

} //namespace alex

#endif
