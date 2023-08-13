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
channel channel1 extends ned.DatarateChannel
{
    datarate = 100Mbps;
}
network Network
{
    parameters:
        int host_number = default(10);
    submodules:
        hosts[host_number]: HOST;
        switch: Switch {
            parameters:
                @display("i=,green;p=87,42");
        }
    connections:
        for i=0..host_number-1 {
            hosts[i].port_S <--> channel1 <--> switch.s_port[i];
        }
}
