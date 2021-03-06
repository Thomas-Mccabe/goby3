// Copyright 2009-2020:
//   GobySoft, LLC (2013-)
//   Massachusetts Institute of Technology (2007-2014)
//   Community contributors (see AUTHORS file)
// File authors:
//   Toby Schneider <toby@gobysoft.org>
//
//
// This file is part of the Goby Underwater Autonomy Project Libraries
// ("The Goby Libraries").
//
// The Goby Libraries are free software: you can redistribute them and/or modify
// them under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 2.1 of the License, or
// (at your option) any later version.
//
// The Goby Libraries are distributed in the hope that they will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Goby.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TIME_IO_20190530H
#define TIME_IO_20190530H

#include "goby/time/convert.h"
#include "goby/time/steady_clock.h"
#include "goby/time/system_clock.h"

namespace goby
{
namespace time
{
inline std::ostream& operator<<(std::ostream& out, const goby::time::SystemClock::time_point& time)
{
    return (out << goby::time::convert<boost::posix_time::ptime>(time));
}
inline std::ostream& operator<<(std::ostream& out, const goby::time::SteadyClock::time_point& time)
{
    return (out << std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch())
                       .count()
                << " us");
}

inline std::ostream& operator<<(std::ostream& out,
                                const goby::time::SystemClock::duration& duration)
{
    return (out << std::chrono::duration_cast<std::chrono::microseconds>(duration).count()
                << " us");
}

} // namespace time
} // namespace goby

using goby::time::operator<<;

#endif
