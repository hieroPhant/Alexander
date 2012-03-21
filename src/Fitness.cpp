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

namespace alex {
	
	template<unsigned int N, unsigned int I, unsigned int O> 
	Genotype<N,I,O> generate() {
		//decide which two Genotypes to breed
		//think about returning std::pair of pointers rather than new Genotype
	}
	
	template<unsigned int N, unsigned int I, unsigned int O> 
	void add(const unsigned int address, Genotype<N>* new_genome) {
		//check for existing element
		//add new
	}
	
	template<unsigned int N, unsigned int I, unsigned int O> 
	void remove(const unsigned int address) {
		//find and remove element
	}
	
	template<unsigned int N, unsigned int I, unsigned int O> 
	void update(const unsigned int address, Genotype<N>* pGenotype) {
		//change element->second
	} 
	
} //namespace alex
