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

#include <iostream>
#include "Benoit.h"
#include "Port.h"
#include "DirectedNode.h"
#include "Graph.h"

namespace alex {

	template<typename link_type>
	struct SignalPropagator {
		typedef typename link_type::signal_type signal_type;
		typedef ben::DirectedNode< ben::InPort<link_type>, ben::OutPort<link_type> > node_type;
		typedef ben::Graph<node_type> graph_type;

		node_type node;

		explicit SignalPropagator(std::shared_ptr<graph_type> graph_ptr)
			: node(graph_ptr) {}

		template<typename function_type>
		void collect(function_type& function, signal_type& total) {
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
			using namespace std;
			for(auto& port : node.outputs) {
				if(!port.push(signal)) {
					cerr << "Link " << node.ID() << " -> "
						 << port.get_address() << " is already full." << endl;
				}
			}
		}
	};

	template<typename link_type>
	struct BackPropagator : public SignalPropagator<link_type> {
		typedef typename SignalPropagator<link_type>::signal_type signal_type;
		typedef typename SignalPropagator<link_type>::node_type node_type;
		typedef typename SignalPropagator<link_type>::graph_type graph_type;

		using SignalPropagator<link_type>::node;
		using SignalPropagator<link_type>::SignalPropagator;
		using SignalPropagator<link_type>::collect;

		template<typename iterator_type>
		void distribute(iterator_type iter, iterator_type end) {
			using namespace std;
			for(auto& port : node.outputs) {
				if(iter == end) {
					cerr << "Not enough signals given for the outputs of "
						 << node.ID() << "." << endl;
					return;
				}
				if(!port.push(*iter)) {
					cerr << "Link " << node.ID() << " -> "
						 << port.get_address() << " is already full." << endl;
				}
				++iter;
			}
			if(iter != end) 
				cerr << "More signals than outputs for " << node.ID() << "." << endl;
		}
	};

} //namespace alex

#endif

