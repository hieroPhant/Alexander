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
#include "Node.h"
#include "McCullochPittsLink.h"

namespace alex {

    class McCullochPittsNeuron {
        typedef McCullochPittsNeuron self_type;
        //A Node knows how to pull in signals from input links and
        //push out a signal to output links. See Node.h.
        typedef McCullochPittsLink link_type;
        typedef Node<link_type> node_type;
        node_type node;

    public:
        //The underlying network structure requires a manager object. Benoit 
        //provides the Graph template class for this purpose. This is just a
        //pass-through for easier access to that type.
        int threshold;

        //You need a shared_ptr to a Graph to make a Node. Use:
        //graph_ptr = std::make_shared<graph_type>()
        //As this code implies, Graphs are constructed with no arguments. After
        //you create one, you don't have to worry about it again - it does its thing
        //behind the scenes.
        McCullochPittsNeuron(int new_threshold) 
            : node(), threshold(new_threshold) {}

        bool execute() {
            //Pulls in input signals, tests their sum against threshold, and 
            //sends out the results. This overload is for non-input neurons.
            //Returns true if the neuron fires, false otherwise.
            int total_stimulus = 0;
            node.for_each_input([&total_stimulus](link_type& link) {
                int signal = 0;
                link.pull(signal);
                total_stimulus += signal;
            });

            //delegate sending
            return execute(total_stimulus);
        }

        bool execute(int stimulus) {
            //Tests the given stimulus against threshold and sends out the results.
            //Returns true if the neuron fires, false otherwise.
            if(stimulus >= threshold) {
                //Node::distribute is overloaded. See Node.h 
                //for a version suitable for backpropagation.
                node.for_each_output([](link_type& link) { link.push(1); });
                return true;
            } else {
                node.for_each_output([](link_type& link) { link.push(0); });
                return false;
            }
        }

        void add_input(self_type& other, bool excitatory) {
            //Create a link between two neurons. The second parameter is true for
            //an excitatory link and false for an inhibitory one. You cannot make a link
            //between neurons which are managed by different Graph objects, and this
            //method will raise an error if you try. If something else causes this 
            //method to fail, submit an Issue on GitHub.
            node.link(other.node, excitatory);
        }

        void remove_input(self_type& other) {
            //Remove a link between two neurons. If there was no link to begin with, this
            //method will do nothing without complaint.
            node.unlink(other.node);
        }

        //Benoit nodes can be created and removed from the outputs too, but this makes
        //the interface more complicated so I omitted it here. If you want to see the full
        //interface for nodes, see Benoit/src/DirectedNode.h.
    };

} //namespace alex

#endif
