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

//to test Alexander, run the following from the test directory:
//	g++ -std=c++0x -g -I../src -I../Benoit/src -lpugixml -lAlexander test_alex.cpp -o test_alex
//	./test_alex

#include "Alexander.h"
#include <iostream>

int main() {
	
	using namespace std;
	using namespace pugi;
	using namespace alex;
	
	const char file[] = "test_network.xml";
	
	NeuralNet network(file);
	
	return 0;
}

