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
	Phenotype::Phenotype(Genotype<N>& genome) {
		//parse bitset into vector of floats
		float numerator, denominator, sign = 1.0;
		vector<float> floats(N/9, 0.0);
		auto it = floats.begin();
		
		for(unsigned int i=0; i<N; i+=9) {
			//get sign
			if(genome.genome[i]) sign = 1.0;
			else sign = -1.0;
			
			//get integer components
			numerator = get_integer(genome.genome, i)
			denominator = get_integer(genome.genome, i+8)
			
			*it = sign*numerator/(1.0 + denominator);
			++it;
		}
		
		it = floats.begin();
		
		//parse ChanceFunctions
		vector<float> dummy; //using constant-value chance functions for now
		clone_node_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it; //set vertical bias
		create_child_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it;
		kill_link_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it;
		create_link_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it;
		
		//parse learning_rate, momentum, and weight_decay
		learning_rate_val = 1/( 1 + exp(-(*it)) ); ++it;
		momentum_val = 1/( 1 + exp(-(*it)) ); ++it;
		weight_decay_val = 1/( 1 + exp(-(*it)) ); 
	} //constructor

	template<unsigned int N> 
	unsigned long Phenotype::get_integer(bitset<N>& sequence, unsigned int start) {
		bitset<8> integer;
		unsigned int i, j;
		for(i=start, j=0; i<(start+8); ++i, ++j) integer[j] = sequence[i];
		return binaryToGray( integer.to_ulong() );
	} //get_integer
	
} //namespace alex




////////////////////////////////////////////////////
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

