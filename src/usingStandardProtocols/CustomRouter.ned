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

import inet.node.base.NetworkLayerNodeBase;
import inet.networklayer.ipv4.Ipv4NetworkLayer;

module CustomRouter extends NetworkLayerNodeBase {
    parameters:
        
//        @statistic[packetDrop](title="Packets Dropped"; source=signal(packetDrop); record=count);
//        @statistic[throughput](title="Throughput"; source=signal(throughput); record=vector);
//        @statistic[queueLength](title="Queue Length"; source=queueLength; record=vector);
        
        
        numEthInterfaces = default(4);
        *.routingTableModule = default("^.ipv4.routingTable");
//        hasIpv4 = true;
        forwarding = true;
//        *.forwarding = true;  // Apply forwarding to all submodules

//	submodules:
	    
}

