#ifndef NeuralNet_h
#define NeuralNet_h

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

#include <vector>
#include <list>
#include "Alexander.h"

namespace alex {

	class NeuralNet {
	/*
		Using pugixml for XML parsing (network topology data is stored in XML)
	*/
	
	protected:
		std::vector<Neuron_input> input_layer;
		std::list< std::vector<Neuron_base> > hidden_layers;
		std::vector<Neuron_base> output_layer;
		
		forward_index_type forward_index;
		backprop_index_type backprop_index;
		
	public:
		NeuralNet() = default;
		NeuralNet(const NeuralNet& rhs) = delete;
		NeuralNet(NeuralNet&& rhs);
		NeuralNet& operator=(const NeuralNet& rhs) = delete;
		NeuralNet& operator=(NeuralNet&& rhs);
		virtual ~NeuralNet();
		
		void run();
		void backpropagate();
		
		bool build_network(); //argument for filename here, call pugixml
	
	}; //class NeuralNet

} //namespace alex

#endif
