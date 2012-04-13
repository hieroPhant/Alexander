#ifndef Neuron_sigmoid_h
#define Neuron_sigmoid_h

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
#include "Neuron_base.h"
#include <cmath>

namespace alex {

	class Neuron_sigmoid : public Neuron_base {
	private:
		virtual data_type f(const data_type z) const;
		virtual data_type df(const data_type z) const;
		
	public:
		//constructors need work
		Neuron_sigmoid() = delete;
		Neuron_sigmoid( pugi::xml_node neuron,
				forward_index_type& fIndex,
				backprop_index_type& bIndex);
		Neuron_sigmoid(forward_index_type& fIndex, backprop_index_type& bIndex);
		Neuron_sigmoid(const Neuron_sigmoid& rhs) = default; //delete this
		Neuron_sigmoid(Neuron_sigmoid&& rhs);
		Neuron_sigmoid& operator=(const Neuron_sigmoid& rhs) = default; //delete this
		Neuron_sigmoid& operator=(Neuron_sigmoid&& rhs) = default;
		~Neuron_sigmoid() = default;
	}; //class Neuron_sigmoid
	
} //namespace alex

#endif
