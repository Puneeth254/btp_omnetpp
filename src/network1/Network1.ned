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

package test_project.network1;

import ned.IdealChannel;


simple Destination
{
    gates:
        input in;
}

simple Source
{
    gates:
        output out;
}

simple Switch
{
    parameters:
        int maxPackets = default(5);

    gates:
        input in[2];
        output out[3];
}

network Network1
{
    @display("bgb=680,297");
    submodules:
        source1: Source {
            @display("p=28,39");
        }
        source2: Source {
            @display("p=28,215");
        }
        switch: Switch {
            @display("p=192,140");
        }
        dest1: Destination {
            @display("p=424,28");
        }
        dest2: Destination {
            @display("p=463,140");
        }
        dest3: Destination {

            @display("p=424,243");
        }
    connections:
        source1.out --> switch.in[1];
        switch.out[0] --> dest1.in;
        switch.out[1] --> dest2.in;
        switch.out[2] --> dest3.in;
        source2.out --> IdealChannel --> switch.in[0];
}
