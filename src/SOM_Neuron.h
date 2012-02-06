#ifndef SOM_Neuron_h
#define SOM_Neuron_h

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
	
	class Ganglion; 
	
	class SOM_Neuron : public Neuron_sigmoid {
	private:
		lateral_node_type  lateral_node;
		
		activity_type width;
		vector<activity_type> locus; //get Benito's advice on SOMs
		
		void initialize(Ganglion& parent);
		
	public:
		SOM_Neuron() = delete;
		explicit SOM_Neuron(const Ganglion& parent);
		SOM_Neuron(const Ganglion& parent,
			   vector<activity_type>& vLocus);
		SOM_Neuron(const SOM_Neuron& rhs);
		SOM_Neuron(SOM_Neuron&& rhs);
		SOM_Neuron& operator=(const SOM_Neuron& rhs);
		SOM_Neuron& operator=(SOM_Neuron&& rhs) = delete;
		~SOM_Neuron() = default;
		
		void get_neighbors(vector<unsigned int>& neighbors) const;
		activity_type select();
		void fire();
		void backpropagate();
		
	}; //class SOM_Neuron

} //namespace alex

#endif
