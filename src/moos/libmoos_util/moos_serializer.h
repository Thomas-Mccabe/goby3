// copyright 2011 t. schneider tes@mit.edu
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this software.  If not, see <http://www.gnu.org/licenses/>.

#include <string>

#include "MOOSLIB/MOOSMsg.h"

namespace goby
{
    namespace moos
    {
 
        class MOOSSerializer
        {
          public:
            static void serialize(CMOOSMsg& msg, std::string* data)
            {
                // adapted from MOOSCommPkt.cpp
                const unsigned PKT_TMP_BUFFER_SIZE = 40000;
                int serialized_size = PKT_TMP_BUFFER_SIZE;
                data->resize(serialized_size);
                serialized_size = msg.Serialize(reinterpret_cast<unsigned char*>(&(*data)[0]), serialized_size);
                data->resize(serialized_size);
            }
            
            static void parse(CMOOSMsg* msg, std::string data)
            {
                msg->Serialize(reinterpret_cast<unsigned char*>(&data[0]), data.size(), false);
            }
            
        };
    }
}