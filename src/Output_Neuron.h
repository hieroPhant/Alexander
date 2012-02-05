#ifndef Output_Neuron_h
#define Output_Neuron_h

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

	class Output_Neuron : public Neuron_base {
	private:
		data_type f();
		data_type df();
		
	public:
		Output_Neuron() = delete;
		Output_Neuron(forward_index_type& fIndex, backprop_index_type& bIndex);
		Output_Neuron(const Output_Neuron& rhs) = default;
		Output_Neuron(Output_Neuron&& rhs);
		Output_Neuron& operator=(const Output_Neuron& rhs) = default;
		Output_Neuron& operator=(Output_Neuron&& rhs) = delete;
		~Output_Neuron() = default;
		
		data_type take_signal()
			{ collect_signals(); 	return state; }
		void feed_gradient(const gradient_type gradient) 
			{ distribute_gradients(gradient); }
	}; //class Output_Neuron
	
	Output_Neuron::Output_Neuron(forward_index_type& fIndex, backprop_index_type& bIndex) 
		: Neuron_base("o", fIndex, bIndex, 0.0) {}
	
	Output_Neuron::Output_Neuron(Output_Neuron&& rhs)
		: Neuron_base(std::move(rhs.Neuron_base)) {}
	
} //namespace alex

#endif
