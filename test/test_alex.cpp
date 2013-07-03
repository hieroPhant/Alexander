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

//to test Alexander, run the following from the test directory:
//	g++ -std=c++0x -g -I../src -I../Benoit/src -lpugixml -lAlexander test_alex.cpp -o test_alex
//	./test_alex

#include <iostream>
#include "gtest/gtest.h"
#include "SignalPropagator.h"

namespace {

	class SignalPropagators : public ::testing::Test {
	}; 

	TEST_F(SignalPropagators, All) {
		EXPECT_TRUE(true);
	}	
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

