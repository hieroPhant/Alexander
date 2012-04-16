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

#include "DataFile.h"

namespace alex {

	DataFile::DataFile() 
		: input_columns(0), output_columns(0) {}

	DataFile::DataFile(const char* filename,
			   const unsigned int inputs,
			   const unsigned int outputs) 
		: current_input(inputs, 0.0), 
		  current_output(outputs, 0.0)  {
		
		outputs_known = open(filename, inputs, outputs);
	}
	
	DataFile::~DataFile() {
		if( file.is_open() )
			file.close();
	}

	bool DataFile::open(const char* filename, 
			    unsigned int inputs, 
			    unsigned int outputs) {
		//returns true if outputs are known
		file.open(filename, std::fstream::in | std::fstream::out);
		if( !file.is_open() ) {
			std::cout << "Problem opening datafile." << std::endl;
		} 
		
		current_input.resize(inputs);
		current_output.resize(outputs);
		
		//need to count number of columns and read the first line
		/*
		string line, number;	
		if ( !getline(file, line) ) break;

    		istringstream ss( line );
    		vector <string> record;
		
		auto it = current_input.begin()
		auto ite = current_input.end()
		while(it != ite) {
			if( !getline(ss, number, "\t") ) break;
			ss >> *it;
			++it;
		}
		
		next_line();
		*/
	}
	
	bool DataFile::next_line() {
	
	}
	
	data_type DataFile::get_num() {
		
	}
	
} //namespace alex

