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
#include "Alexander.h"

struct XORNetwork {
    typedef alex::McCullochPittsNeuron neuron_type;
    std::shared_ptr<typename neuron_type::graph_type> graph_ptr;

    neuron_type inputA, inputB, hiddenOR, hiddenAND, output;

    XORNetwork() : 
        : graph_ptr(new neuron_type::graph_type), 
          inputA(graph_ptr, 1), inputB(graph_ptr, 1),
          hiddenOR(graph_ptr, 1), hiddenAND(graph_ptr, 2) 
          output(graph_ptr, 1) {
        hiddenOR.add_input(inputA, true);
        hiddenOR.add_input(inputB, true);
        hiddenAND.add_input(inputA, true);
        hiddenAND.add_input(inputB, true);
        output.add_input(hiddenOR, true);
        output.add_input(hiddenAND, false);
    }

    bool execute(bool A, bool B) {
        if(A) inputA.execute(1);
        else  inputA.execute(0);

        if(B) inputB.execute(1);
        else  inputB.execute(0);

        hiddenOR.execute();
        hiddenAND.execute();
        return output.execute();
    }
};

int main() {
    using namespace std;

    XORNetwork net;
    cout << "A XOR B -> C" << endl << endl;
    cout << "A  B  C" << endl;
    cout << "0  0  " << net.execute(false, false) << endl;
    cout << "0  1  " << net.execute(false, true) << endl;
    cout << "1  0  " << net.execute(true, false) << endl;
    cout << "1  1  " << net.execute(true, true) << endl;
}

