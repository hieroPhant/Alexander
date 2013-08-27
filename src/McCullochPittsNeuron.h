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

namespace alex {

    void sum(int stimulus, int& total_stimulus) { total_stimulus += stimulus; }

    class McCullochPittsNeuron {
        typedef SignalPropagator<McCullochPittsLink> propagator_type;
        typedef typename propagator_type::graph_type graph_type;
        propagator_type propagator;

    public:
        int bias, threshold;

        McCullochPittsNeuron(std::shared_ptr<graph_type> graph_ptr) 
            : propagator(graph_ptr), bias(0.0), threshold(1) {}

        void execute() {
            //draw in signals
            int total_stimulus = bias;
            propagator.collect(sum, total_stimulus);
            if(total_stimulus > threshold) {
                propagator.distribute(1);
            } else {
                propagator.distribute(0);
            }
        }
    };

} //namespace alex

#endif
