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
#include <vector>

namespace alex {

	class Neuron_base {
	public:
		typedef double data_type;
		typedef std::pair<data_type, bool> error_type;
		typedef std::vector<data_type>::iterator signal_type;
	
	private:
		ben::Node<data_type, signal_type> forward; //FIELD
		ben::Node<error_type, data_type> backward; //FIELD
		std::vector<data_type> state; //FIELD
		std::vector<data_type> output; //FIELD
		unsigned int layer;
	
	protected:
		virtual data_type f(const data_type energy) = 0;
		virtual data_type df(const data_type energy) = 0;
	
	public:
		const char neuron_type; //FIELD
		data_type learning_rate; //FIELD
		//data_type momentum; //FIELD to be added later
		bool operator<(const Neuron_base& rhs) const;

		Neuron_base() = delete;
		explicit Neuron_base(const char chNeuron_type); 
		Neuron_base(const char chNeuron_type, const data_type tBias);
		Neuron_base(const char chNeuron_type,
			    ben::Index<data_type, signal_type>& fIndex, 
			    ben::Index<error_type, data_type>& bIndex, 
			    const data_type tBias);
		Neuron_base(const Neuron_base& rhs);
		Neuron_base(Neuron_base&& rhs);
		Neuron_base& operator=(const Neuron_base& rhs);
		Neuron_base& operator=(Neuron_base&& rhs) = delete;
		virtual ~Neuron_base();
	
		virtual void fire();
		virtual void backpropagate();
		void update_weights();
	
		void prepare_steps(const unsigned int steps);
		void add_input(	const unsigned int address, const data_type weight, 
				const bool trainable);
		void remove_input(const unsigned int address); 
		void clear();
		unsigned int ID() const { return forward.ID; }
		unsigned int layer() const { return layer; }
		void shift_layer(const unsigned int new_layer);
	}; //class Neuron_base

} //namespace alex

#endif

