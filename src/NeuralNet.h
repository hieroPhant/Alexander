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
#include <string>
#include "Alexander.h"
#include "copy_ptr.h"

namespace alex {

	class NeuralNet {
	/*
		Using pugixml for XML parsing (network topology data is stored in XML)
	*/
	
	protected:
		std::vector<Neuron_input> input_layer;
		std::vector< std::vector< poly<Neuron_base> > > hidden_layers;
		std::vector< poly<Neuron_base> > output_layer;
		
		forward_index_type forward_index;
		backprop_index_type backprop_index;
		
		bool create_neuron(pugi::xml_node neuron, 
				   std::vector< poly<Neuron_base> >& layer);
		
	public:
		NeuralNet() = default;
		explicit NeuralNet(const char* pfilename);
		NeuralNet(const NeuralNet& rhs) = delete;
		NeuralNet(NeuralNet&& rhs);
		NeuralNet& operator=(const NeuralNet& rhs) = delete;
		NeuralNet& operator=(NeuralNet&& rhs);
		virtual ~NeuralNet();
		
		void run();
		void backpropagate();
		
		bool build_network(const char* pfilename); 
		void clear();
	
	}; //class NeuralNet

} //namespace alex

#endif
