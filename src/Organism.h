#ifndef Organism_h
#define Organism_h

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
	
	class Organism {
	public:
		typedef ben::Index<data_type, data_type> forward_type;
		typedef ben::Index<delta_type, gradient_type> backprop_type;
		typedef ben::Index<pdf_type, info_type> information_type;
	
	private:
		//Indicies
		forward_type forward;
		backward_type backprop; //reverse of forward
		information_type information; //full set of possible connections
		
		//cells
		std::list<Neuron_base> inputs;
		std::list<Ganglion> cells;
		std::list<Neuron_base> outputs;
	
	public:
		Organism() = default;
		Organism(const Organism& rhs);
		Organism(Organism&& rhs);
		Organism& operator=(const Organism& rhs);
		Organism& operator=(Organism&& rhs);
		~Organism() = default;
		
		unsigned int add_ganglion(const unsigned int layer);
		unsigned int add_input();
		unsigned int add_output();
		//unsigned int add_sigmoid(const data_type bias, 
		//			 const bool trainable=true);
		//unsigned int add_linear(const data_type bias, 
		//			const bool trainable=true);
		//unsigned int add_tanh(const data_type bias, 
		//		      const bool trainable=true);
		//unsigned int add_gaussian(const Neuron_base::data_type bias, 
		//			  const bool trainable=true);
		
		void connect(const unsigned int origin, 
			     const unsigned int target,
			     const double weight,
			     const bool trainable=true);
		
		void run();
		void train();
	}; //class Organism
	
} //namespace alex

#endif

