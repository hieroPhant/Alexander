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
	Neuron_linear(  Index<Neuron_base::weight_type, Neuron_base::signal_type>& fIndex,
			Index<double,double>& bIndex,
			const Neuron_base::weight_type dBias)
		: Neuron_base("l", fIndex, bIndex, dBias) {}
	Neuron_linear(const Neuron_linear& rhs) = default;
	void fire();
	void backpropagate(const unsigned int steps_back=0);
};

//////////////////////////////////////////////
//////////////////////////////////////////////

void Neuron_linear::fire() { 
	
	Neuron_base::signal_type signal, energy = bias->first;
	auto ip = forward.input_begin();
	auto ipe = forward.input_begin();
	while(ip != ipe) {
		ip >> signal;
		energy += ip->weight->first * signal;
		++ip;
	}
	
	auto op = forward.output_begin();
	auto ope = forward.output_end();
	while(op != ope) {
		op << energy;
		++op;
	}
}

void Neuron_linear::backpropagate(const unsigned int steps_back) { 
	
	double gradient, partial = 0;
	auto ip = backward.input_begin();
	auto ipe = backward.input_end();
	while(ip != ipe) {
		ip >> partial;
		//gather partials into gradient
		++ip;
	}
	
	double derivative; //calculate derivative of activation function
	
	auto op = backward.output_begin();
	auto ope = backward.output_end();
	while(op != ope) {
		//output derivative to next Link (based on weight)
		++op;
	}
}

#endif
