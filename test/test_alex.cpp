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
#include "Benoit.h"
#include "Graph.h"
#include "DirectedNode.h"
#include "SignalPropagator.h"

namespace {

	class SignalPropagators : public ::testing::Test {
	public:
		//note: need to simplify Benoit interface
		typedef ben::Buffer<double, 1> link_type;
		typedef alex::SignalPropagator<link_type> unit_type;
		typedef ben::Graph<typename unit_type::node_type> graph_type;

		std::shared_ptr<graph_type> graph_ptr;
		unit_type in1, in2, out1;
		SignalPropagators() : graph_ptr(std::make_shared<graph_type>()), in1(graph_ptr),
	   						  in2(graph_ptr), out1(graph_ptr) {
			out1.node.add_input(in1.node.ID());
			out1.node.add_input(in2.node.ID());
			out1.node.add_output(in1.node.ID());
			out1.node.add_output(in2.node.ID());
		}
	}; 

	TEST_F(SignalPropagators, All) {
		double x=3, y=5, total=0;
		in1.distribute(x);
		in2.distribute(y);
		total = out1.collect(total);
		EXPECT_EQ(x+y, total);

		out1.distribute(total);
		double new_total = 0;
		new_total = in1.collect(new_total);
		EXPECT_EQ(total, new_total);
	}	

	//define some outputoperator for testing purposes

	class ErrorPropagators : public ::testing::Test {
	public:
		typedef ben::Buffer<double, 1> link_type;
		//typedef alex::ErrorPropagator<link_type, > unit_type;
		//typedef ben::Graph<typename unit_type::node_type> graph_type;

		//std::shared_ptr<graph_type> graph_ptr;
	};
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

