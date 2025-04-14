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
import test_project.usingStandardProtocols.CustomRouter;

network TreeTopology
{
    parameters:
//        string schedulerList = default("fifo random lifo rr");
    
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
            @display("p=157,286");
        }

        router2: CustomRouter {
            @display("p=650,271");
        }

        server: StandardHost {
            @display("p=400,65");
        }

        client1: StandardHost {
            @display("p=36,400");
        }

        client2: StandardHost {
            @display("p=156,400");
        }

        client3: StandardHost {
            @display("p=288,400");
        }

        client4: StandardHost {
            @display("p=492,400");
        }

        client5: StandardHost {
            @display("p=632,400");
        }

        client6: StandardHost {
            @display("p=749,400");
        }

    connections:
        // Backbone router to edge routers
        centralRouter.ethg[0] <--> Eth10M <--> router1.ethg[0];
        centralRouter.ethg[1] <--> Eth10M <--> router2.ethg[0];

        // Backbone router to server
        centralRouter.ethg[2] <--> Eth100M <--> server.ethg[0];

        // Edge Router 1 to Clients
        router1.ethg[1] <--> Eth100M <--> client1.ethg[0];
        router1.ethg[2] <--> Eth100M <--> client2.ethg[0];
        router1.ethg[3] <--> Eth100M <--> client3.ethg[0];

        // Edge Router 2 to Clients
        router2.ethg[1] <--> Eth100M <--> client4.ethg[0];
        router2.ethg[2] <--> Eth100M <--> client5.ethg[0];
        router2.ethg[3] <--> Eth100M <--> client6.ethg[0];
}

