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
#include "Alexander.h"

namespace alex {

	class Neuron_base {
	/*
		The Neuron_base class is responsible for managing the various 
		ben::Node objects used by a neuron to communicate with other 
		neurons. The forward_node network transmits signals forward as
		the network evaluates, the backprop_node transmits gradients
		backward, and the info_node transmits information-theoretic value.
		Neuron_base includes public methods for managing links and protected
		utility methods for use by child classes. 
		
		This class handles the forward input function (dot product), but 
		not the activation function. Most every neuron will need to store 
		its forward output value for training, so this is included as a member. 
		Weight deltas are stored as the weights of the backward network, so 
		Neuron_base has enough data to provide a utility to update weights. 
		
		Note: Neuron_base will need to get the learning_rate, etc. from the
		Phenotype class, but the latter is a member of the Neurocyte class...
		
		Note: Is the Value pointer necessary anymore, since I have decided to 
		compute mutual information incrementally based on boolean frequency? 
	*/
	protected:
		forward_node_type   forward_node; //FIELD
		backprop_node_type  backprop_node; //FIELD
		
		data_type state, output; //FIELD
		data_type learning_rate, momentum; //FIELD
		
		//Node-related utility methods
		virtual void collect_signals();
		void distribute_signals();
		data_type collect_errors();
		virtual void distribute_errors(const data_type gradient);
		
		virtual data_type f(const data_type z) = 0;
		virtual data_type df(const data_type z) = 0;
		
	public:
		Neuron_base() = default;
		Neuron_base(forward_index_type&   fIndex, 
			    backprop_index_type&  bIndex,
			    const data_type bias=0.0,
			    const bool trainable=true);
		Neuron_base(const Neuron_base& rhs);
		Neuron_base(Neuron_base&& rhs);
		Neuron_base& operator=(const Neuron_base& rhs);
		Neuron_base& operator=(Neuron_base&& rhs) = delete;
		virtual ~Neuron_base();
		
		void fire();
		void train();
		
		void update_weights();

		void add_input(	const ID_type address, const data_type weight, 
				const bool trainable=true);
		void remove_input(const ID_type address); 
		
		void clear();
		ID_type ID() const { return forward_node.ID; }
	}; //class Neuron_base

} //namespace alex

#endif

