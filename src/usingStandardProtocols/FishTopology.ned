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

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.Eth10M;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;
import inet.node.ethernet.EthernetLink;
import ned.IdealChannel;
import test_project.usingStandardProtocols.CustomRouter;
import inet.node.ospfv2.OspfRouter;

network FishTopology
{
    @display("bgb=800,600");

    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=172,66");
        }

        centralRouter: CustomRouter {
            @display("p=400,172");
        }

        router1: CustomRouter {
            @display("p=251,284");
        }

        router2: CustomRouter {
            @display("p=556,284");
        }

		router3: CustomRouter {
            @display("p=377,411;b=45,46");
        }
        
        server1: StandardHost {
            @display("p=297,69");
        }

        client1: StandardHost {
            @display("p=296,490");
        }

        client2: StandardHost {
            @display("p=486,489");
        }
        
        server2: StandardHost {
            @display("p=500,69;b=48,40");
        }
    connections:
        // Backbone router to edge routers
        centralRouter.ethg[0] <--> Eth100M <--> router1.ethg[0];
        centralRouter.ethg[1] <--> Eth100M <--> router2.ethg[0];

        // Backbone router to server
        centralRouter.ethg[2] <--> Eth100M <--> server1.ethg[0];

        router1.ethg[1] <--> Eth10M <--> router3.ethg[0];

        // Edge Router 2 to Clients
        router2.ethg[1] <--> Eth10M <--> router3.ethg[1];
        client1.ethg[0] <--> Eth100M <--> router3.ethg[2];
        client2.ethg[0] <--> Eth100M <--> router3.ethg[3];
        centralRouter.ethg[3] <--> Eth100M <--> server2.ethg[0];
}

