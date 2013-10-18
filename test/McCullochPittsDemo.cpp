/*
    Alexander: a neural networks library
    Copyright (C) 2011-2013  Jack Hall

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
#include "Alexander.h"

//To compile, use:
//    make test_xor
//in this directory. To run, use:
//    ./test_xor
//If the makefile doesn't work right off the bat, modify it as necessary for your system.
//If you run Windows, do yourself a favor and look up Cygwin. Otherwise, good luck.

struct XORNetwork {
    //A network meant to demonstrate Alexander and Benoit. Acts like
    //an XOR function. Because all values are discrete, no gradients 
    //are computed and there is no backpropagation. 
    
    typedef alex::McCullochPittsNeuron neuron_type;

    //Two input neurons, two hidden neurons, and an output neuron.
    //You can think of each hidden neuron as representing a logical
    //function, the combination of which is the output. I them up
    //to act as an AND and an OR, but there are several equivalent 
    //ways to get an XOR. 
    neuron_type inputA, inputB, hiddenOR, hiddenAND, output;

    //Sets up the network, including the Graph.
    XORNetwork()  
        : inputA(1), inputB(1),
          hiddenOR(1), hiddenAND(2), 
          output(1) {
        //The hidden neurons are identical aside from their thresholds.
        hiddenOR.add_input(inputA, true);
        hiddenOR.add_input(inputB, true);
        hiddenAND.add_input(inputA, true);
        hiddenAND.add_input(inputB, true);
        //XOR(A,B) = OR(A,B) && ~AND(A,B)
        output.add_input(hiddenOR, true);
        output.add_input(hiddenAND, false);
    }

    bool execute(bool A, bool B) {
        //Have each neuron execute in the proper order, and return the
        //answer.
        //The order in which the input neurons are executed doesn't matter.
        if(A) inputA.execute(1);
        else  inputA.execute(0);

        if(B) inputB.execute(1);
        else  inputB.execute(0);

        //The order in which the hidden neurons are executed doesn't matter.
        hiddenOR.execute();
        hiddenAND.execute();

        return output.execute();
    }
};

int main() {
    using namespace std;

    //Create the network.
    XORNetwork net;

    //Display a test.
    cout << "A XOR B -> C" << endl << endl;
    cout << "A  B  C" << endl;
    cout << "0  0  " << net.execute(false, false) << endl;
    cout << "0  1  " << net.execute(false, true) << endl;
    cout << "1  0  " << net.execute(true, false) << endl;
    cout << "1  1  " << net.execute(true, true) << endl;
}

