#ifndef McCullochPittsNeuron_h
#define McCullochPittsNeuron_h

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
#include "SignalPropagator.h"
#include "McCullochPittsLink.h"

namespace alex {

    void sum(int& total_stimulus, int stimulus) { total_stimulus += stimulus; }

    class McCullochPittsNeuron {
        typedef SignalPropagator<McCullochPittsLink> propagator_type;
        typedef McCullochPittsNeuron self_type;
        propagator_type propagator;

    public:
        typedef typename propagator_type::graph_type graph_type;

        int threshold;

        McCullochPittsNeuron(std::shared_ptr<graph_type> graph_ptr, int new_threshold) 
            : propagator(graph_ptr), threshold(new_threshold) {}

        bool execute() {
            //this overload is for non-input neurons
            //draw in signals
            int total_stimulus = 0;
            propagator.collect(sum, total_stimulus);

            //delegating sending
            return execute(total_stimulus);
        }

        bool execute(int stimulus) {
            //this overload is for input neurons
            //compare with threshold and push out the result
            if(stimulus >= threshold) {
                propagator.distribute(1);
                return true;
            } else {
                propagator.distribute(0);
                return false;
            }
        }

        void add_input(const self_type& other, bool excitatory) {
            auto otherID = other.propagator.node.ID();
            if( !propagator.node.add_input(otherID, excitatory) ) 
                std::cerr << "Adding link between " << otherID << " and " 
                          << propagator.node.ID() << " failed." << std::endl;
        }

        void remove_input(const self_type& other) {
            auto otherID = other.propagator.node.ID();
            propagator.node.remove_input(otherID);
        }
    };

} //namespace alex

#endif
