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

	SOM_Neuron::SOM_Neuron(Ganglion& parent)
		: Neuron_sigmoid(parent->forward_index, parent->backprop_index, 0.0), 
		  lateral_node(lIndex, ID()), width(1.0) {
		initialize(parent);
	}
	
	SOM_Neuron::SOM_Neuron( Ganglion& parent,
				vector<activity_type>& vLocus)
		: Neuron_sigmoid(parent->forward_index, parent->backprop_index, 0.0), 
		  lateral_node(parent->information_index, ID()), locus(vLocus), width(1.0) {
		initialize(parent);
	}
	
	SOM_Neuron::SOM_Neuron(const SOM_Neuron& rhs) 
		: Neuron_sigmoid(rhs), lateral_node(rhs.lateral_node), locus(rhs.locus), 
		  width(rhs.width) {
		//how to initialize without parent reference?
	}
	
	SOM_Neuron::SOM_Neuron(SOM_Neuron&& rhs) 
		: Neuron_sigmoid(std::move(rhs)), lateral_node(std::move(rhs.lateral_node)), 
		  locus(std::move(rhs.locus)), width(rhs.width) {}
	
	void SOM_Neuron::initialize(Ganglion& parent) {
		parent.connect_cell( ID() );
		//initialize neighborhood and weights here?
	} 
	
	activity_type SOM_Neuron::select() {
		//pull in signals
		//	calculate activity
		//	calculate state
	}
	
	void SOM_Neuron::fire() {
		//calculate output
		//distribute signals
	}
	
	void SOM_Neuron::backpropagate() {
		//pull in errors
		//calculate derivatives
		//distribute errors
	}

} //namespace alex

