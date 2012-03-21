#ifndef Genotype_h
#define Genotype_h

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

#include <array>
#include <bitset> //hold a maximum of 32 bits

namespace alex {

	template<unsigned int N, unsigned int I, unsigned int O>
	class Fitness;

	//N is # of attractors, sqrt of # of nodes
	//I is # of inputs to gene network
	//O is # of outputs from gene network
	template<unsigned int N=5, unsigned int I=3, unsigned int O=7> 
	class Genotype {
	private:
		Fitness<N>* fitness;
		//17 bit numbers, K=2 connectivity
		std::bitset<N*N*2*2 + (I+O+1)*17*N> decision_chromosome;
		std::array< std::bitset<N*N + N>, N*N > link_chromosome;
		//mutation and crossover rates? probably just hardcode these for now
		
		std::minstd_rand generator;
		
	public:
		const unsigned int ID;
		info_type value;
		
		Genotype() = delete;
		Genotype(const unsigned int nID,  
			 Fitness<N,I,O>* pFitness);
		Genotype(const unsigned int nID, const Genotype& mother, const Genotype& father);
		Genotype(const Genotype& rhs) = delete;
		Genotype(Genotype&& rhs); //need this because Fitness decides breeding
		Genotype& operator=(const Genotype& rhs) = delete;
		//Genotype& operator=(Genotype&& rhs);
		~Genotype();
		
		friend class Phenotype; //only Phenotype constructor actually needs access
		
	}; //class Genotype

} //namespace alex

#endif

