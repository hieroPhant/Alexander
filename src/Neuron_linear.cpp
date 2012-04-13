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

#include "Neuron_linear.h"

namespace alex {

	Neuron_linear::Neuron_linear(pugi::xml_node neuron, 
				     forward_index_type& fIndex,
				     backprop_index_type& bIndex) 
		: Neuron_base(neuron, fIndex, bIndex) {}

	Neuron_linear::Neuron_linear(forward_index_type& fIndex, backprop_index_type& bIndex) 
		: Neuron_base(fIndex, bIndex, 0.0) {}
	
	Neuron_linear::Neuron_linear(Neuron_linear&& rhs)
		: Neuron_base( std::move(rhs) ) {}
	
	data_type Neuron_linear::f(const data_type z) const 
		{ return z; }
	
	data_type Neuron_linear::df(const data_type z) const 
		{ return 1.0; }
		
} //namespace alex

