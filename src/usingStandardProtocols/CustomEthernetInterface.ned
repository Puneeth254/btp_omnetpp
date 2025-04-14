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

import inet.linklayer.ethernet.EthernetInterface;
import inet.queueing.scheduler.PacketScheduler;
import test_project.usingStandardProtocols.CustomQueue;
//
//module CustomEthernetInterface extends EthernetInterface
//{
//    parameters:
//
//    submodules:
//        scheduler: PacketScheduler {
//            parameters:
//                @display("p=391,357");
//        }
//
//    connections allowunconnected:
//        queue.out --> scheduler.in++;
//        scheduler.out --> mac.upperLayerIn;
//}
//

import inet.linklayer.contract.IEtherMac;
import inet.linklayer.contract.IEthernetInterface;
import inet.networklayer.common.NetworkInterface;
import inet.queueing.contract.IPacketQueue;
import inet.queueing.contract.ITrafficConditioner;

module CustomEthernetInterface extends NetworkInterface like IEthernetInterface
{
    parameters:
        string interfaceTableModule;
        string protocol = default("ethernetmac");
        string address @mutable = default("auto");   // MAC address as hex string (12 hex digits), or
                                                     // "auto". "auto" values will be replaced by
                                                     // a generated MAC address in init stage 0.
        bool duplexMode = default(true);      // selects full-duplex (true) or half-duplex (false) operation
        bool csmacdSupport = default(!duplexMode);  // by default CSMA/CD is turned off, so only point-to-point duplex links are supported.
        double bitrate @unit(bps) = default(0 bps);
        string fcsMode @enum("declared","computed") = default("declared");
        *.interfaceTableModule = default(absPath(this.interfaceTableModule));
        *.fcsMode = this.fcsMode;
        *.duplexMode = this.duplexMode;
    gates:
        input upperLayerIn;
        output upperLayerOut;
        input cutthroughIn @loose;
        output cutthroughOut @loose;
        inout phys @labels(EthernetSignal);
    submodules:
        egressTC: <default("")> like ITrafficConditioner {
            parameters:
                @display("p=300,100");
        }
        ingressTC: <default("")> like ITrafficConditioner {
            parameters:
                @display("i=block/uparrow;p=700,100");
        }
        queue: <default("EthernetQueue")> like IPacketQueue {
            parameters:
                packetCapacity = default(1000);
                @display("p=300,250");
        }
        mac: <default(csmacdSupport ? "EthernetCsmaMac" : "EthernetMac")> like IEtherMac {
            parameters:
                @display("p=500,300");
        }
        scheduler: PacketScheduler {
            @display("p=386,372");
        }
    connections:
        upperLayerIn --> { @display("m=n"); } --> egressTC.in;
        egressTC.out --> queue.in;
        queue.out --> scheduler.in++;
        scheduler.out --> mac.upperLayerIn;

        mac.phys <--> { @display("m=s"); } <--> phys;

        mac.upperLayerOut --> ingressTC.in;
        ingressTC.out --> { @display("m=n"); } --> upperLayerOut;
}
