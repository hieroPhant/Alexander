#ifndef McCullochPittsNeuron_h
#define McCullochPittsNeuron_h

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
#include "SignalPropagator.h"
#include "McCullochPittsLink.h"

namespace alex {

    //This function will work as an input operator. For more information on such 
    //functions/functors, see SignalPropagator::collect.
    void sum(int& total_stimulus, int stimulus) { total_stimulus += stimulus; }

    class McCullochPittsNeuron {
        typedef McCullochPittsNeuron self_type;
        //A SignalPropagator knows how to pull in signals from input links and
        //push out a signal to output links. See SignalPropagator.h.
        typedef SignalPropagator<McCullochPittsLink> propagator_type;
        propagator_type propagator;

    public:
        //The underlying network structure requires a manager object. Benoit 
        //provides the Graph template class for this purpose. This is just a
        //pass-through for easier access to that type.
        typedef typename propagator_type::graph_type graph_type;

        int threshold;

        //You need a shared_ptr to a Graph to make a SignalPropagator. Use:
        //graph_ptr = std::make_shared<graph_type>()
        //As this code implies, Graphs are constructed with no arguments. After
        //you create one, you don't have to worry about it again - it does its thing
        //behind the scenes.
        McCullochPittsNeuron(std::shared_ptr<graph_type> graph_ptr, int new_threshold) 
            : propagator(graph_ptr), threshold(new_threshold) {}

        bool execute() {
            //Pulls in input signals, tests their sum against threshold, and 
            //sends out the results. This overload is for non-input neurons.
            //Returns true if the neuron fires, false otherwise.
            int total_stimulus = 0;
            propagator.collect(sum, total_stimulus);

            //delegate sending
            return execute(total_stimulus);
        }

        bool execute(int stimulus) {
            //Tests the given stimulus against threshold and sends out the results.
            //Returns true if the neuron fires, false otherwise.
            if(stimulus >= threshold) {
                //SignalPropagator::distribute is overloaded. See SignalPropagator.h 
                //for a version suitable for backpropagation.
                propagator.distribute(1);
                return true;
            } else {
                propagator.distribute(0);
                return false;
            }
        }

        void add_input(const self_type& other, bool excitatory) {
            //Create a link between two neurons. The second parameter is true for
            //an excitatory link and false for an inhibitory one. You cannot make a link
            //between neurons which are managed by different Graph objects, and this
            //method will raise an error if you try. If something else causes this 
            //method to fail, submit an Issue on GitHub.
            auto otherID = other.propagator.node.ID();
            if( !propagator.node.add_input(otherID, excitatory) ) 
                std::cerr << "Adding link between " << otherID << " and " 
                          << propagator.node.ID() << " failed." << std::endl;
        }

        void remove_input(const self_type& other) {
            //Remove a link between two neurons. If there was no link to begin with, this
            //method will do nothing without complaint.
            auto otherID = other.propagator.node.ID();
            propagator.node.remove_input(otherID);
        }

        //Benoit nodes can be created and removed from the outputs too, but this makes
        //the interface more complicated so I omitted it here. If you want to see the full
        //interface for nodes, see Benoit/src/DirectedNode.h.
    };

} //namespace alex

#endif
