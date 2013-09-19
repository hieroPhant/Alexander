#ifndef McCullochPittsLink_h
#define McCullochPittsLink_h

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

namespace alex {
    
    class McCullochPittsLink {
        bool ready;
        int signal;

    public:
        typedef int signal_type;
        int weight; 
        typedef ben::ConstructionTypes<bool> construction_types;

        McCullochPittsLink(bool excitatory) : ready(false), signal(0) {
            if(excitatory) weight = 1;
            else weight = -1;
        }

        bool pull(int& output) {
            if(ready) {
                output = signal*weight; 
                ready = false;
                return true;
            } else return false;
        }

        bool push(int input) {
            if(!ready) {
                signal = input;
                ready = true;
                return true;
            } else return false;
        }
    };

} //namespace alex

#endif
