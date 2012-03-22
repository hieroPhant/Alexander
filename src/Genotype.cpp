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
		: ID(nID), fitness(pFitness), value(0.0), generator(nID),
		  link_chromosome(), decision_chromosome() {
		  
		fitness->add(ID, this);
		std::bernoulli_distribution random_bit(0.5);
		for(int i=decision_chromosome.size()-1; i>=0; --i) {
			decision_chromosome[i] = random_bit(generator);
		}
		
		int x, y;
		std::uniform_int_distribution<> random_int(0, link_chromosome[0].size() - 1);
		for(i=link_chromosome.size()-1; i>=0; --i) {
			x = random_int(generator);
			y = random_int(generator);
			while(x == y) y = random_int(generator);
			
			link_chromosome[i][x] = true;
			link_chromosome[i][y] = true;
		}
	} //constructor
	
	template<unsigned int N, unsigned int I, unsigned int O>
	Genotype::Genotype(const unsigned int nID, const std::pair<Genotype*, Genotype*> parents) 
		: ID(nID), decision_chromosome(), link_chromosome(),
		  fitness(parents->first->fitness), value(0.0), generator(nID) {
		
		float mutation_rate = .2, crossover_rate = .5;
		
		//breed new chromosomes from parents, use hardcoded mutation and crossover rates
		fitness->add(ID, this);
		
		//what does crossover rate mean?
		//generate 2 random numbers for decision_chromosome crossover
		
		//decide whether to mutate
		std::bernoulli_distribution random_bit(mutation_rate);
		std::uniform_int_distribution<> random_int(0, decision_chromosome.size() - 1);
		if( random_bit(generator) ) ~decision_chromosome[random_int(generator)];
		
		//generate 2 random numbers for link_chromosome crossover
		
		//decide whether to mutate
		random_int = std::uniform_int_distribution<>(0, link_chromosome.size() - 1);
		int i = random_int(generator); //which bitset
		random_int = std::uniform_int_distribution<>(0, link_chromosome[0].size() - 1);
		int j = random_int(generator); //which false bit to flip
		random_bit2 = std::bernoulli_distribution(0.5);
		bool first = random_bit2(generator); //which true bit to flip
		int ii = link_chromosome[0].size() - 1;
		if( random_bit(generator) ) {
			for(ii; ii>=0; --ii) {
				if( link_chromosome[i][ii] ) {
					if(first) { link_chromosome[i][ii] = false; break; }
					else first = true;
				} //if
			} //for
			
			while(link_chromosome[i][j]) { //make sure bit is false to start with
				j = random_int(generator);
			} //while
			link_chromosome[i][j] = true;
		} //if
		
	} //constructor
	
	template<unsigned int N, unsigned int I, unsigned int O>
	Genotype::~Genotype() {
		fitness->remove(ID);
	} //destructor

} //namespace alex

