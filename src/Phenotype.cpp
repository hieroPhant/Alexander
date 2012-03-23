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
		//extract boolean functions (4 bits each)	
		auto itf = functions.begin();
		auto itfe = functions.end();
		int i = 0, j;
		while(itf != itfe) {
			for(j=3; j>=0; --j, ++i) (*itf)[j] = genome.decision_chromosome[i];
			++itf;
		}
		
		//extract input decision boundaries
		auto iti = input_decisions.begin();
		auto itie = input_decisions.end();
		array<float, 4>::iterator it, ite; //for inner arrays
		while(iti != itie) {
			it = iti->begin();
			ite = iti->end();
			while(it != ite) {
				*it = get_real(genome.decision_chromosome, i);
				++it; i+=17;
			}
			++iti;
		}
		
		//extract output weights
		auto ito = output_weights.begin();
		auto itoe = output_weights.end();
		array<float, 5>::iterator iter, itere; //for inner arrays
		while(ito != itoe) {
			iter = ito->begin();
			itere = ito->end();
			while(iter != itere) {
				*iter = get_real(genome.decision_chromosome, i);
				++iter; i+=17;
			}
			++ito;
		}
		
		//extract gene connectivity
		auto itl = genome.link_chromosome.begin();
		auto itc = links.begin();
		auto itce = links.end();
		while(itc != itce) {
			j = 0;
			for(i=itl->size()-1; i>=0; --i) {
				if( (*itl)[i] ) {
					(*itc)[j] = i;
					++j;
				}
				if(j == 2) break;
			}
			++itc; ++itl;
		}
		
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
		std::array< std::array<float, 4>, 5 >& w = input_decisions; //shorthand
		int i;
		for(i=4; i>=0; --i) 
			state[i] = ( w[i][0]*value + w[i][1]*dvalue 
				    +w[i][2]*persistence + w[i][3] ) > 0;
		
		//evaluate boolean network (update state)
		bitset<25> new_state;
		for(i=24; i>=0; --i) 
			new_state[i] = gene_fcn( i, state[ links[i][0] ], state[ links[i][1] ] );
		
		for(i=24, i>=0; --i) state[i+5] = new_state[i];

		//calculate and store current output values
		std::array< std::array<float, 5>, 7 >& v = output_weights; //shorthand
		std::array<float, 7> outputs;
		for(i=6; i>=0; --i) {
			//calculate values from v and states
			outputs[i] = 0.0;
			for(int j=4; j>=0; --j) outputs[i] += v[i][j] * state[25+j];
		}
		//run each element of output through a sigmoid
		learning_rate_val = sigmoid(outputs[0]);
		momentum_val 	  = sigmoid(outputs[1]);
		weight_decay_val  = sigmoid(outputs[2]);
		forget_factor_val = sigmoid(outputs[3]);
		kill_link_prob	  = sigmoid(outputs[4]);
		make_link_prob 	  = sigmoid(outputs[5]);
		make_node_prob	  = sigmoid(outputs[6]);
	} //run
	
	float Phenotype::sigmoid(const float x) const {
		return 1/(1 + exp(-x));
	}
	
	bool Phenotype::gene_fcn(const unsigned int gene_index, const bool a, const bool b) const {
		if(a) {
			if(b) return functions[gene_index][3];
			else  return functions[gene_index][2];
		} else {
			if(b) return functions[gene_index][1];
			else  return functions[gene_index][0];
		}
	}
	
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

