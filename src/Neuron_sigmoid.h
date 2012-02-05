#ifndef Neuron_sigmoid_h
#define Neuron_sigmoid_h

/*
    Alexander: a neural networks library
    Copyright (C) 2011  Jack Hall

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

#include <cmath>

class Neuron_sigmoid : public Neuron_base {
public:
	Neuron_sigmoid() = default;
	Neuron_sigmoid(forward_index_type& fIndex,
		       backprop_index_type& bIndex,
		       const data_type dBias, const bool bTrainable=true)
		: Neuron_base("s", fIndex, bIndex, dBias, bTrainable) {} 
	Neuron_sigmoid(const Neuron_sigmoid& rhs) = default;
	Neuron_sigmoid& operator=(const Neuron_sigmoid& rhs) = default;
	~Neuron_sigmoid() = default;
	
	Neuron_base::data_type f(const Neuron_base::data_type energy) const
		{ return 1/(1 + exp(-energy)); }
	Neuron_base::data_type df(const Neuron_base::data_type energy) const
		{ auto x = exp(energy);
		  return x/((x+1)*(x+1)); }
};

#endif
