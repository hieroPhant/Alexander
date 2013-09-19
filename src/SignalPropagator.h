#ifndef SignalPropagator_h
#define SignalPropagator_h

/*
    Alexander: a neural networks library
    Copyright (C) 2011-2013  Jack Hall

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

#include <iostream>
#include "Benoit.h"
#include "Port.h"
#include "DirectedNode.h"
#include "Graph.h"

namespace alex {

    //This class abstracts away the more complicated parts of the Benoit interface. If you want to
    //get your hands dirty, ignore this class and set up your message-passing network with Benoit
    //alone. Benoit itself is very modular and configurable, mostly at compile time with templates. 
    //On the other hand, I never got around to writing enough documentation for how the different 
    //parts of Benoit depend on each other. Let me know if you want to try something fancy, and I'll
    //help you out.

	template<typename link_type>
	struct SignalPropagator {
		typedef typename link_type::signal_type signal_type;
        //The type of Benoit node is used for communication. See Benoit/src/DirectedNode.h for the
        //full interface.
		typedef ben::DirectedNode< ben::InPort<link_type>, ben::OutPort<link_type> > node_type;
        //Benoit Graph objects are depend on the type of node chosen.
		typedef ben::Graph<node_type> graph_type;

        //Providing the node as a public member is less safe than usual, but it means this class
        //does not need to reproduce the entire node interface.
		node_type node;

        //A SignalPropagator must be part of a graph. You will likely have two graphs per neural
        //network: one for forward propation and one for backprop and training.
		explicit SignalPropagator(std::shared_ptr<graph_type> graph_ptr)
			: node(graph_ptr) {}

		template<typename function_type>
		void collect(function_type& function, signal_type& total) {
            //This method takes in signals from inputs and puts them together according to 
            //the provided function or functor. I recommend using a functor so you can save 
            //data. If one or more links does not have a signal ready, print an error.
            //The function should take two arguments: a reference for the combined signal as
            //computed so far, and a constant reference or value for the current input signal.
            //This function is called on each input signal.
			using namespace std;
			signal_type signal;
			for(auto& port : node.inputs) {
				if(!port.pull(signal)) {
					cerr << "Link " << port.get_address() << " -> " 
						 << node.ID() << " was not ready." << endl;
				}
				function(total, signal);
			}
		}
		void distribute(const signal_type& signal) {
            //Send the given signal out through each output link. Prints an error if the Link 
            //already contains an unread signal.
			using namespace std;
			for(auto& port : node.outputs) {
				if(!port.push(signal)) {
					cerr << "Link " << node.ID() << " -> "
						 << port.get_address() << " is already full." << endl;
				}
			}
		}
	    template<typename iterator_type>
		void distribute(iterator_type iter, iterator_type end) {
            //Instead of sending out the same signal to all links (like the first version of
            //this method), this version will send out a different signal to each link. Put the 
            //signal bound for each link in some data structure. This method takes a pair of 
            //iterators over the range of signals to be sent. You can use raw pointers if the 
            //memory is stored consecutively. Those familiar with the C++ Standard Library will
            //be familiar with this pattern.
			using namespace std;
			for(auto& port : node.outputs) {
				if(iter == end) {
                    //Got to the end of the signals data structure too soon.
					cerr << "Not enough signals given for the outputs of "
						 << node.ID() << "." << endl;
					return;
				}
				if(!port.push(*iter)) {
                    //Raise an error if any links are already full with unread signal(s).
					cerr << "Link " << node.ID() << " -> "
						 << port.get_address() << " is already full." << endl;
				}
				++iter;
			}
			if(iter != end) 
                //Got to the end of the links data structure too soon.
				cerr << "More signals than outputs for " << node.ID() << "." << endl;
		}
    };

} //namespace alex

#endif

