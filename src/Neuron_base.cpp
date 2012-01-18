//(c) Jack Hall 2011, licensed under GNU GPL v3

#include "Neuron_base.h"

void add_input(const unsigned int nOrigin, double dWeight) {
	connections.add_input(nOrigin, dWeight);
}

void remove_input(const unsigned int nOrigin) {
	connections.remove_input(nOrigin);
}

void clear() {
	connections.clear();
}
	
unsigned int ID() { return connections.ID; }

