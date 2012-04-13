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
//	g++ -std=c++0x -g -I../src -I../Benoit/src -lpugixml test_alex.cpp -o test_alex
//	./test_alex

#include "Alexander.h"
#include <iostream>

int main() {
	
	using namespace std;
	using namespace pugi;
	using namespace alex;
	
	const char file[] = "test_network.xml";
	xml_document doc;
	xml_parse_result result = doc.load_file(file);
	
	if(result) {
		cout << "XML file parsed ok." << endl;
		
		xml_node network = doc.child("network");
		for (xml_node layer = network.child("layer"); layer; layer = layer.next_sibling("layer")) {
			cout << "Layer: " << layer.attribute("number").value() << endl;
			
			for(xml_node neuron = layer.child("neuron"); neuron; neuron = neuron.next_sibling("neuron")) {
				cout << "\tNeuron: id=" << neuron.attribute("id").value();
				cout << ", type=" << neuron.attribute("type").value();
				cout << ", bias=" << neuron.attribute("bias").value() << endl;
				
				for(xml_node link = neuron.child("link"); link; link = link.next_sibling("link")) {
					cout << "\t\tLink: origin id=" << link.attribute("origin-id").value();
					cout << ", weight=" << link.attribute("weight").value();
					cout << ", trainable? " << link.attribute("trainable").value() << endl;
				}
			}
		}
		
	} else {
		cout << "XML parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
    		cout << "Error description: " << result.description() << "\n";
    		cout << "Error offset: " << result.offset << " (error at [..." << (file + result.offset) << "]\n\n";
	}
	
	return 0;
}

