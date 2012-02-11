#ifndef Neuron_base_h
#define Neuron_base_h

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

#include <iostream>

namespace alex {

	class Neuron_base {
	protected:
		forward_node_type   forward_node; //FIELD
		backprop_node_type  backprop_node; //FIELD
		information_node_type info_node; //FIELD
	
	public:
		Neuron_base() = default;
		Neuron_base(forward_index_type&   fIndex, 
			    backprop_index_type&  bIndex, 
			    information_index_type& iIndex,
			    const data_type bias=0.0,
			    const bool trainable=true);
		Neuron_base(const Neuron_base& rhs);
		Neuron_base(Neuron_base&& rhs);
		Neuron_base& operator=(const Neuron_base& rhs);
		Neuron_base& operator=(Neuron_base&& rhs) = delete;
		virtual ~Neuron_base() = default;
	
		data_type collect_signals();
		void distribute_signals(const data_type output);
		gradient_type collect_errors();
		void distribute_errors(const gradient_type gradient);
		
		void update_weights();

		void add_input(	const unsigned int address, const data_type weight, 
				const bool trainable=true);
		void remove_input(const unsigned int address); 
		void connect_info(const unsigned int address);
		void clear();
		unsigned int ID() const { return forward.ID; }
	}; //class Neuron_base

} //namespace alex

#endif

