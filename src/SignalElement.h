#ifndef SignalElement_h
#define SignalElement_h

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

	template<typename T>
	void sum_operator(T& total, T new_value) { total += new_value; }

	template<typename T, 
			 T (*ActivationFunction)(const T&), 
			 void (*InputOperator)(T&, T)>
	struct SignalElement_base {
		ben::stdMessageNode<T, 1> node;
		T collect(T bias) {
			for(auto& port : node.inputs) (*InputOperator)(bias, port.pull());
			return bias; //bias is already copied, so no need for a temp variable
		}
		T evaluate(const T& state) const { return (*ActivationFunction)(state); }
		void distribute(const T& signal) {
			for(auto& port : node.outputs) port.push(signal);
		}
	}; //class SignalElement_base


	template<typename T, 
			 T (*ActivationFunction)(const T&),
			 T (*OutputOperator)(const T&, const T&)=nullptr,
			 void (*InputOperator)(T&, T)=sum_operator<T> >
	struct SignalElement : public SignalElement_base<T, ActivationFuction, InputOperator> {
		void distribute(const T& signal) { //overrides SignalElement_base::distribute
			T temp;
			for(auto& port : node.outputs) {
				temp = (*OutputOperator)(signal, port.old_signal()); //needs old_signal access
				port.push(temp);
			}
		}
	}; //class SignalElement


	template<typename T, 
			 T (*ActivationFunction)(const T&),
			 void (*InputOperator)(T&, T)=sum_operator<T> >
	struct SignalElement<T, ActivationFunction, nullptr, InputOperator> 
		: public SignalElement_base<T, ActivationFuction, InputOperator> {
	}; //class SignalElement, no output operator

} //namespace alex

#endif
