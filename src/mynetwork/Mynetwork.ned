//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

package test_project.mynetwork;

import ned.IUnidirectionalChannel;
import ned.IdealChannel;


simple Node
{
    parameters:
        @display("i=block/routing"); // Set an icon for visualization
    gates:
        input in;
        output out;
}

network MyNetwork
{
    submodules:
        node1: Node {
            @loose(in); // Mark the 'in' gate as unconnected
        }// First node
        node2: Node;
        node3: Node;
    connections:
        node1.out --> {  delay = 50ms; } --> node2.in; // Connect node1 to node2 with a delay
        node2.out --> {  delay = 100ms; } --> node3.in; // Connect node2 to node3 with a delay
        node3.out --> {delay = 150ms; } --> node1.in;
}
