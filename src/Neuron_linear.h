#ifndef Neuron_linear_h
#define Neuron_linear_h

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

class Neuron_linear : public Neuron_base {
public:
	Neuron_linear() = default;
	Neuron_linear(Index<Neuron_base::data_type, Neuron_base::signal_type>& fIndex,
		      Index<Neuron_base::error_type, Neuron_base::data_type>& bIndex,
		      const Neuron_base::data_type dBias, const bool bTrainable)
		: Neuron_base("l", fIndex, bIndex, dBias, bTrainable) {} 
	Neuron_linear(const Neuron_linear& rhs) = default;
	Neuron_linear& operator=(const Neuron_linear& rhs) = default;
	~Neuron_linear() = default;
	
	Neuron_base::data_type f(const Neuron_base::data_type energy) const
		{ return energy; }
	Neuron_base::data_type df(const Neuron_base::data_type energy) const
		{ return 1.0; }
};

#endif
