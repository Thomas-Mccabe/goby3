// copyright 2009 t. schneider tes@mit.edu
 // 
// this file is part of the Dynamic Compact Control Language (DCCL),
// the goby-acomms codec. goby-acomms is a collection of libraries 
// for acoustic underwater networking
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

#ifndef DCCLException20100812H
#define DCCLException20100812H

#include "goby/common/exception.h"

namespace goby
{
    namespace acomms
    {
        /// \brief Exception class for libdccl
        class DCCLException : public goby::Exception
        {
          public:
          DCCLException(const std::string& s)
              : Exception(s)
            { }

        };

        // used to signal null value in field codecs
        class DCCLNullValueException : public DCCLException
        {
          public:
          DCCLNullValueException()
              : DCCLException("NULL Value")
            { }    
        };
        
    }
}


#endif

