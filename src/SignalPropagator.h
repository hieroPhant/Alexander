#ifndef SignalPropagator_h
#define SignalPropagator_h

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

#include "Benoit.h"

namespace alex {

	template<typename T>
	void sum_operator(T& total, T new_value) { total += new_value; }

	template<typename T, 
			 void (*InputOperator)(T&, T)>
	struct SignalPropagator_base {

		ben::stdMessageNode<T, 1> node;

		T collect(T bias) {
			for(auto& port : node.inputs) (*InputOperator)(bias, port.pull());
			return bias; //bias is already copied, so no need for a temp variable
		}

		void distribute(const T& signal) {
			for(auto& port : node.outputs) port.push(signal);
		}
	}; //class SignalPropagator_base


	template<typename T, 
			 T (*OutputOperator)(const T&, const T&)=nullptr,
			 void (*InputOperator)(T&, T)=sum_operator<T> >
	struct SignalPropagator : public SignalPropagator_base<T, ActivationFuction, InputOperator> {
		void distribute(const T& signal) { //overrides SignalPropagator_base::distribute
			T temp;
			for(auto& port : node.outputs) {
				temp = (*OutputOperator)(signal, port.old_signal()); //needs old_signal access
				port.push(temp);
			}
		}
	}; //class SignalPropagator


	template<typename T, 
			 void (*InputOperator)(T&, T)=sum_operator<T> >
	struct SignalPropagator<T, nullptr, InputOperator> 
		: public SignalPropagator_base<T, ActivationFuction, InputOperator> {
	}; //class SignalPropagator, no output operator

} //namespace alex

#endif
