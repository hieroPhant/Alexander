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

#include <random>

namespace alex {

	template<unsigned int N>
	class ChanceFunction {
	private:
		vector<float> steepness;
		float vertical_bias, lateral_bias, scale_factor;
    		std::minstd_rand generator;
		
	public:
		ChanceFunction() = delete;
		ChanceFunction(const vector<float>& steep, 
			       const float vbias, 
			       const float lbias, 
			       const float scale)
			: steepness(steep), vertical_bias(vbias), 
			  lateral_bias(lbias), scale_factor(scale),
			  generator(std::random_device) {}
		ChanceFunction(const ChanceFunction& rhs) = delete;
		ChanceFunction& operator=(const ChanceFunction& rhs) = delete;
		~ChanceFunction() = default;
		
		bool operator()(const vector<float>& inputs) const { //slow memory allocation
			if( steepness.size() != inputs.size() ) throw;
			
			float z = lateral_bias;
			
			auto it = steepness.begin();
			auto ite = steepness.end();
			auto itt = inputs.begin();
			while(it != ite) {
				z += (*it) * (*itt);
				++it; ++itt;
			}
			
			float chance = vertical_bias + scale_factor/(1 + exp(-z));
			float critical_float = 1/(1 + exp(-chance)); //to normalize between 0 and 1
			float random_float = std::generate_canonical<float, 10>(generator);
			return random_float < critical_float;
		}
	}; //struct ChanceFunction
	

	template<unsigned int N>
	class Phenotype {
	private:
		
		
	public:
		ChanceFunction kill_node, clone_node, create_child, kill_link, create_link;
	
		Phenotype() = delete;
		explicit Phenotype(Genotype<N>& genome);
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
		
		//how to represent these?
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
