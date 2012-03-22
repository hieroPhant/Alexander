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

	template<unsigned int N,I,O>
	Phenotype::Phenotype(Genotype<N,I,O>& genome) {
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
		//extract data for links, functions, input_decisions, output_coefficients
		
		/////////////////////
		//old version, with chance functions
		
		//parse ChanceFunctions
		//vector<float> dummy; //using constant-value chance functions for now
		//clone_node_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it; //set vertical bias
		//create_child_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it;
		//kill_link_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it;
		//create_link_fcn = ChanceFunction(dummy, *it, 0.0, 0.0); ++it;
		
		//parse learning_rate, momentum, and weight_decay
		//learning_rate_val = 1/( 1 + exp(-(*it)) ); ++it;
		//momentum_val = 1/( 1 + exp(-(*it)) ); ++it;
		//weight_decay_val = 1/( 1 + exp(-(*it)) ); 
	} //constructor

	template<unsigned int N>
	float Phenotype::get_real(std::bitset<N>& sequence, unsigned int start) const {
		/*
		Extracts a floating point number from a bit sequence. The number is encoded
		with a sign and two integers, as shown below. This coding is compact and keeps
		numbers from getting unreasonably small or large. It should improve the 
		evolutionary fitness surface over normal floating point numbers. 
		*/
		if(sequence[start]) sign = 1.0;
		else sign = -1.0;
		a = get_integer(sequence, start+1); 
		b = get_integer(sequence, start+9); //8-bit integers
		return sign*a/(1.0 + b); 
	} //get_real

	template<unsigned int N> 
	unsigned long Phenotype::get_integer(std::bitset<N>& sequence, unsigned int start) const {
		/*
		Translates an 8-bit portion of a bit sequence to an integer. The integers are
		coded in the genome with Gray's coding, which hopefully improves the fitness
		surface by smoothing it out. 
		*/
		std::bitset<8> integer = get_subset<N,8>(sequence, start);
		return gray_to_binary( integer.to_ulong() );
	} //get_integer
	
	template<unsigned int N, unsigned int M>
	std::bitset<M> Phenotype::get_subset(std::bitset<M>& sequence, unsigned int start) const {
		/*
		Extracts a contiguous subset from a bit sequence. May segfault if sequence
		isn't long enough (there is no bounds checking). 
		*/
		std::bitset<M> subset;
		unsigned int i=start, j=0;
		for(i, j; i<(start+M); ++i, ++j) subset[j] = sequence[i];
		return subset;
	} //get_subset
	
	unsigned long gray_to_binary(unsigned long num) const {
		/*
		Translates a binary number in Gray's code to the same number in base 2. Got
		this from the internet, so I hope it works. 
		*/
		unsigned int numBits = 8 * sizeof(num);
		unsigned int shift;
	    	for (shift = 1; shift < numBits; shift *= 2) {
			num ^= num >> shift;
	    	}
	    	return num;
	} //gray_to_binary
	
	void Phenotype::run(const float value; const float dvalue; const float persistence) {
		//run decision boundaries on inputs
		//evaluate boolean network (update state)
		//calculate and store current output values
	} //run
	
	bool Phenotype::flip_coin(const float probability) {
		//generate random bit from given probability
		random_bit = std::bernoulli_distribution(probability);
		return random_bit(generator);
	} //flip_coin
	
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

