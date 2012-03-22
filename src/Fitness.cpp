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
	std::pair< Genotype<N,I,O>*, Genotype<N,I,O>* > Fitness<N,I,O>::generate() {
		vector<info_type> values( population.size(), 0.0 );
		info_type total=0.0;
		auto itv = values.begin();
		auto it = population.begin();
		auto ite = population.end();
		while(it != ite) {
			*itv = it->second->value;
			total += *itv;
			++it; ++itv;
		}
		
		Genotype<N,I,O>* mother( select(value, total) );
		Genotype<N,I,O>* father( select(value, total) );
		while(mother == father) father = select(value,total); //ensure parents differ
		std::pair< Genotype<N,I,O>*, Genotype<N,I,O>* > parents(mother, father);
		return parents;
	}
	
	template<unsigned int N, unsigned int I, unsigned int O>
	Genotype<N,I,O>* Fitness<N,I,O>::select(const vector<info_type>& values, 
						const info_type total) {
		//assumes values are all positive numbers
		float choice = total * std::generate_canonical<float, 15>(generator);
		
		auto it = values.begin();
		auto ite = values.end();
		auto itm = population.begin();
		while(it != ite) {
			choice -= *it;
			if(choice < 0) break;
			++it; ++itm;
		}
		return itm->second; //should be valid if choice is between zero and one
	}
	
	template<unsigned int N, unsigned int I, unsigned int O> 
	bool Fitness<N,I,O>::add(const unsigned int address, Genotype<N,I,O>* new_genome) {
		pair< unsigned int, Genotype<N,I,O>* > element;
		auto result = population.insert( std::make_pair(address, new_genome) );
		return result->second; //whether element was inserted
	}
	
	template<unsigned int N, unsigned int I, unsigned int O> 
	void Fitness<N,I,O>::remove(const unsigned int address) {
		population.erase(address);
	}
	
	template<unsigned int N, unsigned int I, unsigned int O> 
	bool Fitness<N,I,O>::update(const unsigned int address, Genotype<N>* pGenotype) {
		auto it = population.find(address);
		if(it != population.end()) { it->second = pGenotype; return true; }
		else return false; //whether element existed in the first place
	} 
	
} //namespace alex

