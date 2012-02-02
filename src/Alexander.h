#ifndef Alexander_h
#define Alexander_h

/*
    Alexander: a neural networks library
    Copyright (C) 2011  Jack Hall

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
	typedef float data_type; //weight and signal of forward links
	typedef float gradient_type; //signal of backprop links
	typedef std::pair<float,bool> delta_type; //weight of backprop links
	typedef float info_type;
	typedef std::pair<float,bool> pdf_type;
	
} //namespace alex

#include "Neuron_base.h"
#include "NeuralNet.h"

#endif
