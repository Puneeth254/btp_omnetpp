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

import inet.node.inet.StandardHost;
import inet.node.ethernet.EthernetLink;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;

network SimpleTCPNetwork {
    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xmldoc("config.xml");
        }
        server: StandardHost {
            parameters:
                @display("p=200,200");
        }
        client: StandardHost {
            parameters:
                @display("p=400,200");
        }
    connections:
        client.pppg++ <--> EthernetLink <--> server.pppg++;
}
