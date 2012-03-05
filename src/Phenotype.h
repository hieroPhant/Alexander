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

	class ChanceFunction {
	private:
		vector<float> steepness;
		float vertical_bias, lateral_bias, scale_factor;
    		std::minstd_rand generator;
    		
    		bool result(const float z) {
    			float chance = vertical_bias + scale_factor/(1 + exp(-z));
			float critical_float = 1/(1 + exp(-chance)); //force between 0 and 1
			float random_float = std::generate_canonical<float, 10>(generator);
			return random_float < critical_float;
    		}
		
	public:
		ChanceFunction()
			: steepness(), vertical_bias(-1000000.0), //makes sigmoid result tiny
			  lateral_bias(0.0), scale_factor(0.0),
			  generator(std::random_device) {}
		ChanceFunction(const vector<float>& steep, 
			       const float vbias, 
			       const float lbias, 
			       const float scale)
			: steepness(steep), vertical_bias(vbias), 
			  lateral_bias(lbias), scale_factor(scale),
			  generator(std::random_device) {}
		ChanceFunction(const ChanceFunction& rhs) = delete;
		ChanceFunction& operator=(const ChanceFunction& rhs) = default;
		~ChanceFunction() = default;
		
		bool operator()() const {
			return 1/(1 + exp(-vertical_bias)); //constant value between 0 and 1
		}
		
		bool operator()(const float input) const { 
			if( steepness.size() != 1 ) throw;
			float z = lateral_bias + input*steepness[0];
			return result(z);
		}
		
		bool operator()(const float input1, const float input2) const {
			if( steepness.size() != 2 ) throw;
			float z = lateral_bias + input1*steepness[0] + input2*steepness[1];
			return result(z);
		}
	}; //struct ChanceFunction
	

	class Phenotype {
	private:
		unsigned long binaryToGray(unsigned long num) 
			{ return (num>>1) ^ num; }
		template<unsigned int N> get_integer(bitset<N>& sequence, unsigned int start);
		
		ChanceFunction clone_node_fcn, create_child_fcn, kill_link_fcn, create_link_fcn;
		float learning_rate_val, momentum_val, weight_decay_val; //constant values for now
		
	public:
		Phenotype() = delete;
		template<unsigned int N> explicit Phenotype(Genotype<N>& genome);
		Phenotype(const Phenotype& rhs) = delete;
		//Phenotype(Phenotype&& rhs);
		Phenotype& operator=(const Phenotype& rhs) = delete;
		//Phenotype& operator=(Phenotype&& rhs);
		~Phenotype() = default;
		
		//how to represent these?
		float learning_rate();
		float momentum();
		float weight_decay();
		
	}; //class Phenotype

} //namespace alex

#endif
