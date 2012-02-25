#ifndef Neurocyte_sigmoid_h
#define Neurocyte_sigmoid_h

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
#include <cmath>

namespace alex {

	class Neurocyte_sigmoid : public Neuron_base {
	private:
		virtual data_type f(const data_type z) const;
		virtual gradient_type df(const data_type z) const;
		
		Phenotype phenotype;
		Genotype genome;
		
	public:
		//constructors need work
		Neurocyte_sigmoid() = delete;
		Neurocyte_sigmoid(forward_index_type& fIndex, backprop_index_type& bIndex);
		Neurocyte_sigmoid(const Neurocyte_sigmoid& rhs) = default;
		Neurocyte_sigmoid(Neurocyte_sigmoid&& rhs);
		Neurocyte_sigmoid& operator=(const Neurocyte_sigmoid& rhs) = default;
		Neurocyte_sigmoid& operator=(Neurocyte_sigmoid&& rhs) = delete;
		~Neurocyte_sigmoid() = default;
		
		virtual void act_on_topology();
		
	}; //class Neurocyte_sigmoid
	
	Neurocyte_sigmoid::Neurocyte_sigmoid(forward_index_type& fIndex, backprop_index_type& bIndex) 
		: Neuron_base("o", fIndex, bIndex, 0.0) {}
	
	Neurocyte_sigmoid::Neurocyte_sigmoid(Neurocyte_sigmoid&& rhs)
		: Neuron_base(std::move(rhs.Neuron_base)) {}
	
	data_type Neurocyte_sigmoid::f(const data_type z) const 
		{ return 1/(1 + exp(-state)); }
	
	gradient_type Neurocyte_sigmoid::df(const data_type z) const {
		data_type x = exp(z);
		return x/((x+1)*(x+1));
	}
	
	void Neurocyte_sigmoid::act_on_topology() {
	
	}
	
} //namespace alex

#endif
