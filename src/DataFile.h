#ifndef DataFile_h
#define DataFile_h

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

#include <iostream>
#include <fstream>
#include <string>

namespace alex {

	class DataFile {
	private:
		std::fstream file; 
		std::vector<data_type> current_input, current_output;
		bool outputs_known;
		
		data_type get_num();
		
	public:
		DataFile();
		DataFile(const char* filename, 
			 unsigned int inputs, 
			 unsigned int outputs);
		~DataFile();
		
		bool open(const char* filename,
			  unsigned int inputs, 
			  unsigned int outputs);
		void close() { if( file.is_open() ) file.close(); }
		
		const vector<data_type>& read_input() { return current_input; }
		const vector<data_type>& read_output() { return current_output; }
		bool next_line();
	
	}; //class DataFile

} //namespace alex

#endif
