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

//
// TODO auto-generated type
//
module HOST
{
    parameters:
        int num_of_submodules = 3;
        @display("i=block/routing");
    gates:
        inout port_S;
    submodules:
        app: App {
            @display("p=47,47");
        }
        ip: IP {
            @display("p=170,114");
        }
        eth: Ethernet {
            @display("p=312,179");
        }
    connections:
        app.A_IP <--> ip.IP_A;
        ip.IP_E <--> eth.E_IP;
        eth.host_port <--> port_S;
}
