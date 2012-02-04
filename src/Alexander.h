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

#include "Benoit.h"

namespace alex {
	//forward connections
	typedef float 					data_type; 
	typedef ben::Node<data_type, data_type> 	forward_node_type;
	typedef ben::Index<data_type, data_type> 	forward_index_type;
	
	//backpropagation connections
	typedef data_type 				gradient_type; 
	typedef std::pair<data_type,bool> 		delta_type; 
	typedef ben::Node<delta_type, gradient_type> 	backprop_node_type;
	typedef ben::Index<delta_type, gradient_type> 	backprop_index_type;
	
	//information-theoretic connections
	typedef float 					info_type;
	typedef std::pair<float,bool> 			pdf_type; //this isn't right yet
	typedef ben::Node<pdf_type, info_type> 		info_node_type;
	typedef ben::Index<pdf_type, info_type> 	info_index_type;
	
	//self-organizing map lateral connections
	typedef float 					activity_type;
	typedef std::pair<activity_type, Neuron*> 	link_type;
	typedef ben::Node<link_type, activity_type> 	lateral_node_type;
	typedef ben::Index<link_type, activity_type> 	lateral_index_type;
	
} //namespace alex

#include "Neuron_base.h"
#include "Neuron_sigmoid.h"
#include "SOM_Neuron.h"
#include "Input_Neuron.h"
#include "Output_Neuron.h"
#include "Ganglion.h"

#endif
