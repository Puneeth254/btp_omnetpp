package test_project.usingStandardProtocols;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.Eth10M;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;
import inet.node.ethernet.EthernetLink;
import test_project.usingStandardProtocols.CustomRouter;


network SimpleNetwork
{
    @display("bgb=626,462");
    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=229,54");
        }
        router1: CustomRouter {
            parameters:
                @display("p=369,189");
        }
        router2: CustomRouter {

            @display("p=190,189");
        }
        standardRouter: Router {

            @display("p=276,264");
        }
        server1: StandardHost {
            parameters:
                @display("p=72,93");
        }
        server2: StandardHost {

            @display("p=56,274");
        }
        client1: StandardHost {
            parameters:
                @display("p=518,274");
        }
        client2: StandardHost {
            parameters:
                @display("p=518,103");
        }
        client3: StandardHost {

            @display("p=276,371");
        }
    connections:
        client1.ethg[0] <--> Eth100M <--> router1.ethg[0];
        client2.ethg[0] <--> Eth100M <--> router1.ethg[1];
        client3.ethg[0] <--> Eth100M <--> standardRouter.ethg[0];
        server1.ethg[0] <--> Eth10M <--> router2.ethg[0];
        server2.ethg[0] <--> Eth10M <--> router2.ethg[1];
        router1.ethg[3] <--> Eth10M <--> router2.ethg[2];
        router1.ethg[2] <--> Eth100M <--> standardRouter.ethg[1];
        router2.ethg[3] <--> Eth100M <--> standardRouter.ethg[2];
}
