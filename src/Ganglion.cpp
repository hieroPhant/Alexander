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
	Ganglion::Ganglion(forward_index_type& fIndex,
			   backprop_index_type& bIndex,
			   info_index_type& iIndex)
		: forward_node(fIndex), 
		  backprop_node(bIndex, std::make_pair<0.0, true>, forward_node.ID),
		  information_node(iIndex, forward_node.ID), 
		  forward_index(), backprop_index(), information_index(), 
		  output(forward_index, backprop_index) {
		  //add first SOM_Neuron
	}
	
	void Ganglion::add_input(const unsigned int address, const data_type weight, 
				 const bool trainable=true) {
				 
	}
	
	void Ganglion::remove_input(const unsigned int address) {
	
	}
	
	void Ganglion::run() {
	
	}
	
	void Ganglion::backpropagate() {
	
	}
} //namespace alex

