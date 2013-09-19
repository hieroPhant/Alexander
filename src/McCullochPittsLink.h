#ifndef McCullochPittsLink_h
#define McCullochPittsLink_h

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

namespace alex {
    
    class McCullochPittsLink {
        bool ready; //True if signal has been written but not read.
        int signal; //Output signal directly from neuron.

    public:
        typedef int signal_type; //need this typedef for Benoit 
        int weight; 

        //This typedef holds the signature of the constructor, which is
        //a single bool in this case. Make sure you update this if you
        //change the constructor.
        typedef ben::ConstructionTypes<bool> construction_types; 

        //Initialize a Link by telling it whether to excite or inhibit
        //the neuron it leads to. If you don't want this link to affect
        //that neuron, don't create it.
        McCullochPittsLink(bool excitatory) : ready(false), signal(0) {
            if(excitatory) weight = 1;
            else weight = -1;
        }

        //The following two methods will return false if a link is already full.
        //If this happens, check the order in which you call execute on your 
        //neurons.

        bool pull(int& output) {
            //To be called by SignalPropagator when it takes in signals
            //from inputs. The signal is placed in the given reference.
            //If the link did not have a signal in it yet, returns false
            //and leaves the given reference unchanged.
            if(ready) {
                output = signal*weight; 
                ready = false;
                return true;
            } else return false;
        }

        bool push(int input) {
            //To be called by SignalPropagator when it sends out data via
            //outputs. Input data is copied. If the link already had a signal
            //in it, return false and leave the original unchanged.
            if(!ready) {
                signal = input;
                ready = true;
                return true;
            } else return false;
        }
    };

} //namespace alex

#endif
