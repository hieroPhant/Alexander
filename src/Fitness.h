#ifndef Fitness_h
#define Fitness_h

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

#include <map>

namespace alex {

	template<unsigned int N>
	class Fitness {
	private:
		map<unsigned int, Genotype<N>*> population;
		
	public:
		Fitness() = default;
		Fitness(const Fitness& rhs) = delete;
		//Fitness(Fitness&& rhs);
		Fitness& operator=(const Fitness& rhs) = delete;
		//Fitness& operator=(Fitness&& rhs);
		~Fitness() = default;
		
		unsigned int genome_length() { return N; }
		unsigned population_size() { return population.size(); }
		
		bitset<N> generate();
		bitset<N> generate(const unsigned int parent);
		void remove(const unsigned int address);
		void update(const unsigned int address, Genotype<N>* pGenotype);
		
	}; //class Fitness

} //namespace alex

#endif
