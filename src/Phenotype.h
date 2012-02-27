#ifndef Phenotype_h
#define Phenotype_h

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

	struct ChanceFunction {
	
	}; //struct ChanceFunction
	

	class Phenotype {
	private:
		//function objects for parameterized sigmoids
		
	public:
		Phenotype() = delete;
		explicit Phenotype(Genotype& genome);
		Phenotype(const Phenotype& rhs) = delete;
		//Phenotype(Phenotype&& rhs);
		Phenotype& operator=(const Phenotype& rhs) = delete;
		//Phenotype& operator=(Phenotype&& rhs);
		~Phenotype() = default;
		
		bool kill_node(const info_type value);
		bool clone_node(const info_type conditional_xy, 
				const info_type conditional_yx);
		bool create_child(const info_type conditional_xy, 
				  const info_type conditional_yx);
		bool kill_link(const info_type value);
		bool create_link(const info_type value);
		float learning_rate();
		float momentum();
		float weight_decay();
		
	}; //class Phenotype

} //namespace alex

/*
//        The purpose of this function is to convert an unsigned
//        binary number to reflected binary Gray code.

unsigned int binaryToGray(unsigned int num)
{
        return (num>>1) ^ num;
}
 
//        The purpose of this function is to convert a reflected binary
//        Gray code number to a binary number.

unsigned int grayToBinary(unsigned int num)
{
    unsigned int numBits = 8 * sizeof(num);
    unsigned int shift;
    for (shift = 1; shift < numBits; shift *= 2)
    {
        num ^= num >> shift;
    }
    return num;
}
*/

#endif
