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

namespace alex {

	template<unsigned int N>
	class Fitness;

	template<unsigned int N>
	class Genotype {
	private:
		Fitness<N>* fitness;
		
	public:
		const bitset<N> genome;
		const unsigned int ID;
		info_type value;
		
		Genotype() = delete;
		Genotype(const unsigned int nID, 
			 const bitset<N>& bGenome, 
			 Fitness<N>* pFitness);
		Genotype(const unsigned int nID, const Genotype& rhs);
		Genotype(const Genotype& rhs) = delete;
		//Genotype(Genotype&& rhs);
		Genotype& operator=(const Genotype& rhs) = delete;
		//Genotype& operator=(Genotype&& rhs);
		~Genotype();
		
	}; //class Genotype

} //namespace alex

#endif

