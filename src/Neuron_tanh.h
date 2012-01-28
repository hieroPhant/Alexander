#ifndef Neuron_tanh_h
#define Neuron_tanh_h

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

class Neuron_tanh : public Neuron_base {
public:
	Neuron_tanh() = default;
	Neuron_tanh(Index<Neuron_base::data_type, Neuron_base::signal_type>& fIndex,
		    Index<Neuron_base::error_type, Neuron_base::data_type>& bIndex,
		    const Neuron_base::data_type dBias, const bool bTrainable)
		: Neuron_base("s", fIndex, bIndex, dBias, bTrainable) {} 
	Neuron_tanh(const Neuron_tanh& rhs) = default;
	Neuron_tanh& operator=(const Neuron_tanh& rhs) = default;
	~Neuron_tanh() = default;
	
	Neuron_base::data_type f(const Neuron_base::data_type energy) const
		{ return tanh(energy); }
	Neuron_base::data_type df(const Neuron_base::data_type energy) const
		{ auto x = cosh(energy);
		  return 1/(x*x); }
};

#endif
