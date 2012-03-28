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
#include <cmath>
#include "Genotype.h"
#include "Phenotype.h"

namespace alex {

	class Neuron_sigmoid : public Neurocyte {
	private:
		virtual data_type f(const data_type z) const;
		virtual gradient_type df(const data_type z) const;
		
		Genotype genome;
		Phenotype phenotype;
		
	public:
		//constructors need work
		Neuron_sigmoid() = delete;
		Neuron_sigmoid(forward_index_type& fIndex, backprop_index_type& bIndex);
		Neuron_sigmoid(const Neuron_sigmoid& rhs) = default;
		Neuron_sigmoid(Neuron_sigmoid&& rhs);
		Neuron_sigmoid& operator=(const Neuron_sigmoid& rhs) = default;
		Neuron_sigmoid& operator=(Neuron_sigmoid&& rhs) = delete;
		~Neuron_sigmoid() = default;
		
		virtual void act_on_topology();
		
	}; //class Neuron_sigmoid
	
	Neuron_sigmoid::Neuron_sigmoid(forward_index_type& fIndex, backprop_index_type& bIndex) 
		: Neuron_base("o", fIndex, bIndex, 0.0) {}
	
	Neuron_sigmoid::Neuron_sigmoid(Neuron_sigmoid&& rhs)
		: Neuron_base(std::move(rhs.Neuron_base)) {}
	
	data_type Neuron_sigmoid::f(const data_type z) const 
		{ return 1/(1 + exp(-state)); }
	
	gradient_type Neuron_sigmoid::df(const data_type z) const {
		data_type x = exp(z);
		return x/((x+1)*(x+1));
	}
	
	void Neuron_sigmoid::act_on_topology() {
	
	}
	
} //namespace alex

#endif
