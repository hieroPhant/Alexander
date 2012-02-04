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
	
		data_type  state; //FIELD
		data_type  output; //FIELD
	
		virtual data_type f() = 0;
		virtual data_type df() = 0;
	
	public:
		const char neuron_kind; //FIELD
		data_type  learning_rate; //FIELD
		data_type  momentum; //FIELD
		virtual bool operator<(const Neuron_base& rhs) const;

		Neuron_base() = delete;
		explicit Neuron_base(const char chNeuron_kind); 
		Neuron_base(const char chNeuron_kind, 
			    const data_type tBias, 
			    const bool bTrainable);
		Neuron_base(const char chNeuron_kind,
			    forward_index_type&   fIndex, 
			    backprop_index_type&  bIndex, 
			    const data_type tBias
			    const bool bTrainable=true);
		Neuron_base(const Neuron_base& rhs);
		Neuron_base(Neuron_base&& rhs);
		Neuron_base& operator=(const Neuron_base& rhs);
		Neuron_base& operator=(Neuron_base&& rhs) = delete;
		virtual ~Neuron_base();
	
		virtual void fire();
		virtual void backpropagate();
		void update_weights();

		void add_input(	const unsigned int address, const data_type weight, 
				const bool trainable);
		void remove_input(const unsigned int address); 
		void clear();
		unsigned int ID() const { return forward.ID; }
	}; //class Neuron_base

} //namespace alex

#endif

