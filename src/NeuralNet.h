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

#include <list>

namespace alex {

	class NeuralNet {
	private:
		ben::Index< Neuron_base::data_type, Neuron_base::signal_type> forward;
		ben::Index<Neuron_base::error_type, Neuron_base::data_type> backward;
		
		std::list<Neuron_base> neurons;
	
	public:
		NeuralNet() = default;
		NeuralNet(const NeuralNet& rhs);
		NeuralNet(NeuralNet&& rhs);
		NeuralNet& operator=(const NeuralNet& rhs);
		NeuralNet& operator=(NeuralNet&& rhs);
		~NeuralNet() = default;
		

		unsigned int add_sigmoid(const Neuron_base::data_type bias, 
					 const bool trainable=true);
		unsigned int add_linear(const Neuron_base::data_type bias, 
					const bool trainable=true);
		unsigned int add_tanh(const Neuron_base::data_type bias, 
				      const bool trainable=true);
		//unsigned int add_gaussian(const Neuron_base::data_type bias, 
		//			  const bool trainable=true);
		
		void connect(const unsigned int origin, 
			     const unsigned int target,
			     const double weight,
			     const bool trainable=true);
		
		void run();
		void train();
	}; //class NeuralNet
	
} //namespace alex

#endif

