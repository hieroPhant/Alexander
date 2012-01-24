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

class Neuron_sigmoid : public Neuron_base {
public:
	Neuron_sigmoid(Index<Neuron_base::weight_type, Neuron_base::signal_type>& fIndex,
		       Index<double,double>& bIndex,
		       const Neuron_base::weight_type dBias)
		: Neuron_base("s", fIndex, bIndex, dBias) {}
	Neuron_sigmoid(const Neuron_sigmoid& rhs) = default;
	void fire();
	void backpropagate(const unsigned int steps_back=0);
};

/////////////////////////////////////
/////////////////////////////////////

void Neuron_sigmoid::fire() {
	
}

void Neuron_sigmoid::backpropagate(const unsigned int steps_back) {
	
}

#endif
