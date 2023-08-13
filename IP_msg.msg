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
// TODO generated message class
//
message IP_msg extends cPacket{
    int version=0;
    int length=20;
    int tos=0;
    int size=20;
    int Id=0;
    int flags=1;
    int offset=0;
    int ttl=2;
    int protocol=0;
    int checksum=0;
	string ip_src;
	string ip_dest;
}
