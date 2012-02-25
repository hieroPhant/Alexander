#ifndef Neurocyte_linear_h
#define Neurocyte_linear_h

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

namespace alex {

	class Neurocyte_linear : public Neuron_base {
	private:
		virtual data_type f(const data_type z) const;
		virtual gradient_type df(const data_type z) const;
		
	public:
		//constructors need work
		Neurocyte_linear() = delete;
		Neurocyte_linear(forward_index_type& fIndex, backprop_index_type& bIndex);
		Neurocyte_linear(const Neurocyte_linear& rhs) = default;
		Neurocyte_linear(Neurocyte_linear&& rhs);
		Neurocyte_linear& operator=(const Neurocyte_linear& rhs) = default;
		Neurocyte_linear& operator=(Neurocyte_linear&& rhs) = delete;
		~Neurocyte_linear() = default;
		
		virtual void act_on_topology() {}
	}; //class Neurocyte_linear
	
	Neurocyte_linear::Neurocyte_linear(forward_index_type& fIndex, backprop_index_type& bIndex) 
		: Neuron_base("o", fIndex, bIndex, 0.0) {}
	
	Neurocyte_linear::Neurocyte_linear(Neurocyte_linear&& rhs)
		: Neuron_base(std::move(rhs.Neuron_base)) {}
	
	data_type Neurocyte_linear::f(const data_type z) const 
		{ return z; }
	
	gradient_type Neurocyte_linear::df(const data_type z) const 
		{ return 1.0; }
	
} //namespace alex

#endif
