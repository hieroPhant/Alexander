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
	Genotype::Genotype(const unsigned int nID, 
			   Fitness<N,I,O>* pFitness) 
		: ID(nID), fitness(pFitness), value(0.0) {
		fitness->add(ID, this);
		//create randomized chromosomes
	} //constructor
	
	template<unsigned int N, unsigned int I, unsigned int O>
	Genotype::Genotype(const unsigned int nID, const Genotype& mother, const Genotype& father) 
		: ID(nID), decision_chromosome(), 
		  fitness(mother.fitness), value(0.0) {
		//breed new chromosomes from parents, use hardcoded mutation and crossover rates
		//may want to take a std::pair of pointers as arguments
		fitness->add(ID, this);
	} //constructor
	
	template<unsigned int N, unsigned int I, unsigned int O>
	Genotype::~Genotype() {
		fitness->remove(ID);
	} //destructor

} //namespace alex
