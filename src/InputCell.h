#ifndef Input_Neuron_h
#define Input_Neuron_h

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

	class Input_Neuron : public Neuron_base {
	private:
		data_type f();
		data_type df();
		
	public:
		Input_Neuron() = delete;
		Input_Neuron(forward_index_type& fIndex, backprop_index_type& bIndex);
		Input_Neuron(const Input_Neuron& rhs) = default;
		Input_Neuron(Input_Neuron&& rhs);
		Input_Neuron& operator=(const Input_Neuron& rhs) = default;
		Input_Neuron& operator=(Input_Neuron&& rhs) = delete;
		~Input_Neuron() = default;
		
		gradient_type take_gradient()
			{ return collect_errors(); }
		void feed_signal(const data_type signal)
			{ output = signal;	distribute_signals(); }
	}; //class Input_Neuron
	
	Input_Neuron::Input_Neuron(forward_index_type&   fIndex, backprop_index_type&  bIndex) 
		: Neuron_base("i", fIndex, bIndex) {}
	
	Input_Neuron::Input_Neuron(Input_Neuron&& rhs)
		: Neuron_base(std::move(rhs.Neuron_base)) {}
	
} //namespace alex

#endif
