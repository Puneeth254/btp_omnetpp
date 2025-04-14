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

import inet.networklayer.contract.INetworkLayer;
import inet.networklayer.ipv4.IIpv4;
import test_project.usingStandardProtocols.CustomNetworkLayer;
import inet.networklayer.contract.IArp;
import inet.networklayer.arp.ipv4.Arp;
import inet.networklayer.ipv4.Ipv4RoutingTable;
import inet.networklayer.ipv4.Ipv4NatTable;
import inet.networklayer.common.InterfaceTable;
import inet.common.MessageDispatcher;
import inet.networklayer.configurator.contract.IIpv4NodeConfigurator;

module CustomIpLayer like INetworkLayer {
    parameters:
        string interfaceTableModule;
        *.interfaceTableModule = default(absPath(this.interfaceTableModule));
        *.routingTableModule = default(absPath(".routingTable"));
        
    
    gates:
        input ifIn @labels(INetworkHeader);
        output ifOut @labels(INetworkHeader);
        input transportIn @labels(Ipv4ControlInfo/down);
        output transportOut @labels(Ipv4ControlInfo/up);
        
    submodules:
        configurator: <default("Ipv4NodeConfigurator")> like IIpv4NodeConfigurator if typename != "" {
            parameters:
                @display("p=100,100;is=s");
        }
        ip: CustomNetworkLayer {
            parameters:
                @display("p=700,400;q=queue");
        }
        routingTable: Ipv4RoutingTable {
            parameters:
                @display("p=100,200;is=s");
        }
//        natTable: Ipv4NatTable {
//            parameters:
//                @display("p=100,300;is=s");
//        }
        arp: Arp {
            parameters:
                @display("p=400,400;q=pendingQueue");
                routingTableModule = default("^.routingTable");
                interfaceTableModule = default("^.interfaceTable");
        }
        mp: MessageDispatcher {
            parameters:
                @display("p=550,300;b=600,5");
        }
        lp: MessageDispatcher {
            parameters:
                @display("p=550,500;b=600,5");
        }
        up: MessageDispatcher {
            parameters:
                @display("p=550,100;b=600,5");
        }

    connections allowunconnected:
        transportIn --> { @display("m=n"); } --> up.in++;
        transportOut <-- { @display("m=n"); } <-- up.out++;

//        up.out++ --> igmp.routerIn;
//        up.in++ <-- igmp.routerOut;

        up.out++ --> mp.in++;
        up.in++ <-- mp.out++;

//        up.out++ --> icmp.transportIn;
//        up.in++ <-- icmp.transportOut;

//        igmp.ipOut --> mp.in++;
//        igmp.ipIn <-- mp.out++;

//        icmp.ipOut --> mp.in++;
//        icmp.ipIn <-- mp.out++;

        mp.out++ --> ip.transportIn;
        mp.in++ <-- ip.transportOut;

        arp.ifOut --> lp.in++;
        arp.ifIn <-- lp.out++;

        ip.queueOut --> lp.in++;
        ip.queueIn <-- lp.out++;

        lp.out++ --> { @display("m=s"); } --> ifOut;
        lp.in++ <-- { @display("m=s"); } <-- ifIn;
}