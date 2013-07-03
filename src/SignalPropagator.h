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


	template<typename T, void (*F)(T&, T)>
	struct InputFunctor {
		void operator()(T& total, T value) { (*F)(total, value); }
	};


	template<typename LINK, typename INPUTOPERATOR = InputFunctor<typename LINK::signal_type, 
																  sum_operator<typename LINK::signal_type> > >
	struct SignalPropagator {
		typedef typename LINK::signal_type signal_type;
		ben::stdMessageNode<signal_type> node;

		signal_type collect(signal_type bias) {
			for(auto& port : node.inputs) INPUTOPERATOR(bias, port.pull());
			return bias; //bias is already copied, so no need for a temp variable
		}

		void distribute(const signal_type& signal) {
			for(auto& port : node.outputs) port.push(signal);
		}
	}; //class SignalPropagator


	template<typename LINK, typename OUTPUTOPERATOR,
			 typename INPUTOPERATOR = InputFunctor<typename LINK::signal_type, 
												   sum_operator<typename LINK::signal_type> > >
	struct ErrorPropagator : public SignalPropagator<LINK, INPUTOPERATOR> {
		typedef SignalPropagator<LINK, INPUTOPERATOR> base_type;
		typedef typename base_type::signal_type signal_type;

		void distribute(const signal_type& signal) { //overrides SignalPropagator::distribute
			signal_type temp;
			for(auto& port : base_type::node.outputs) {
				temp = OUTPUTOPERATOR(signal, port.old_signal()); //needs old_signal access
				port.push(temp);
			}
		}
	}; //class ErrorPropagator

} //namespace alex

#endif
