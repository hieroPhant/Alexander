#ifndef Alexander_h
#define Alexander_h

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

#include <utility>
#include <pugixml.hpp>
#include "Benoit.h"

namespace alex {

	typedef unsigned int				ID_type;

	//forward connections
	typedef float 					data_type; 
	typedef ben::Node<data_type, data_type> 	forward_node_type;
	typedef ben::Index<data_type, data_type> 	forward_index_type;
	
	//backpropagation connections
	typedef std::pair<data_type,bool> 		delta_type; 
	typedef ben::Node<delta_type, data_type> 	backprop_node_type;
	typedef ben::Index<delta_type, data_type> 	backprop_index_type;
	
} //namespace alex

#ifndef Neuron_base_h
#include "Neuron_base.h"
#include "Neuron_input.h"
#include "Neuron_linear.h"
#include "Neuron_sigmoid.h"
#include "NeuralNet.h"
#endif

#endif

