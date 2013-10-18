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
#include <gtest/gtest.h>
#include "Node.h"

namespace {

    //It would be good to write explicit ArcList tests.

	TEST(Node, All) {
        //Refactor these tests into subroutines!

        //test construction
        alex::Node<double> in1, in2, out1;
        EXPECT_EQ(0, out1.size());

        //test link
        EXPECT_TRUE(out1.link(in1));
        EXPECT_TRUE(out1.linked_to(in1));
        EXPECT_TRUE(out1.link(in2));
        EXPECT_TRUE(out1.linked_to(in2));
        EXPECT_EQ(2, out1.size());
        EXPECT_TRUE(in1.link(out1));
        EXPECT_TRUE(in1.linked_to(out1));

        //test for_each_*
		double x=3, y=5, total=0;
		in1.for_each_output([x](double& z) { z = x; });
		in2.for_each_output([y](double& z) { z = y; });
		out1.for_each_input([&total](double z) { total+= z; });
		EXPECT_EQ(x+y, total);

		out1.for_each_output([total](double& z) { z = total; });
		double new_total = 0;
		in1.for_each_input([&new_total](double z) { new_total += z; });
		EXPECT_EQ(total, new_total);

        //test mirror
        auto out1clone_ptr = new alex::Node<double>();
        out1clone_ptr->mirror(out1);
        //new links
        EXPECT_TRUE(out1clone_ptr->linked_to(in1));
        EXPECT_TRUE(out1clone_ptr->linked_to(in2));
        EXPECT_FALSE(in1.linked_to(*out1clone_ptr));
        //old links
        EXPECT_TRUE(out1.linked_to(in1));
        EXPECT_TRUE(out1.linked_to(in2));

        //test unlink
        out1clone_ptr->unlink(in1);
        EXPECT_FALSE(out1clone_ptr->linked_to(in1));
        EXPECT_TRUE(out1clone_ptr->linked_to(in2));
        EXPECT_TRUE(out1.linked_to(in1)); //in case out1clone BECAME out1

        //test destruction
        EXPECT_TRUE(in2.link(*out1clone_ptr));
        auto out1clone_copy_ptr = new alex::Node<double>(*out1clone_ptr);
        delete out1clone_ptr; out1clone_ptr = nullptr;
        EXPECT_TRUE(in2.linked_to(*out1clone_copy_ptr));

        delete out1clone_copy_ptr; out1clone_copy_ptr = nullptr;
        EXPECT_EQ(0, in2.size());

        //test unlink_all
        out1.unlink_all();
        EXPECT_FALSE(out1.linked_to(in1));
        EXPECT_FALSE(out1.linked_to(in2));
        EXPECT_EQ(0, out1.size());

        //test assignment
        EXPECT_TRUE(out1.link(in1));
        EXPECT_TRUE(out1.link(in2));
        in2 = out1;
        EXPECT_FALSE(in2.linked_to(in2));
        EXPECT_TRUE(in2.linked_to(in1));
        EXPECT_TRUE(in1.linked_to(in2));
        EXPECT_TRUE(in1.linked_to(out1));
        EXPECT_EQ(1, in1.size());
	}	

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

