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

package test_project.usingStandardProtocols;

import inet.queueing.queue.PacketQueue;
import inet.queueing.scheduler.PacketScheduler;
import inet.queueing.contract.IPacketQueue;

module CustomQueue extends PacketQueue
{
    parameters:
        @class(CustomQueue);
//        packetCapacity = default(100);
//        dropperClass = "RandomPacketDropper";
//        comparatorClass = default("shortestPacketComparator");
        string scheduler = default("fifo");
//	gates:
//        input in @loose;
//        output out @loose;

        @display("bgb=387,266");
    submodules:
        //	    queueDropper: PacketQueue{
        //	        parameters:
        ////	            dropperClass = "^.dropperClass";
        ////	            comparatorClass = "^.comparatorClass";
        ////	            packetCapacity = "^.packetCapacity";
        //	    }
//        scheduler: PacketScheduler {
//            parameters:
//                @display("p=171,82");
//        }

    connections allowunconnected:
//        in --> scheduler.in++;
//        scheduler.out --> out;
}
