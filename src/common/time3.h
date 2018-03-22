// Copyright 2009-2018 Toby Schneider (http://gobysoft.org/index.wt/people/toby)
//                     GobySoft, LLC (2013-)
//                     Massachusetts Institute of Technology (2007-2014)
//                     Community contributors (see AUTHORS file)
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

#ifndef Time3_20180322H
#define Time3_20180322H

#include <limits>
#include <type_traits>
#include <chrono>
#include <sstream>

#include <boost/date_time.hpp>

#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/cmath.hpp>

namespace goby
{
    ///\name Time
    //@{

    namespace common
    {
        extern int goby_time_warp_factor;
    }

    namespace time
    {
        /// \brief microsecond unit
        using MicroTimeUnit = decltype(boost::units::si::micro*boost::units::si::seconds);
        /// \brief quantity of microseconds (using int64)
        using MicroTime = boost::units::quantity<MicroTimeUnit, std::int64_t>;
        /// \brief quantity of seconds (using double)
        using SITime = boost::units::quantity<boost::units::si::time>;

        /// \brief return the current time since 1970-01-01 00:00 UTC ("UNIX Time")
        template<typename TimeType>
            inline TimeType now()
        {
            // remove units from chrono time
            std::int64_t microsecs_since_epoch =
                std::chrono::system_clock::now().time_since_epoch() /
                std::chrono::microseconds(1);

            // warp time by factor
            microsecs_since_epoch *= common::goby_time_warp_factor;

            // convert to boost::units type
            return TimeType(microsecs_since_epoch*
                            boost::units::si::micro*boost::units::si::seconds);
        }

        /// \brief return the current time as the number of microseconds since 1970-01-01 00:00 UTC (same as now<goby::time::MicroTime>())
        inline MicroTime now()
        { return now<MicroTime>(); }

        /// \brief Convert from boost::posix_time::ptime to boost::units::quantity<...> of time
        template<typename Quantity>
            Quantity from_ptime(boost::posix_time::ptime t_in)
        {
            using namespace boost::posix_time;
            using namespace boost::gregorian;
        
            if (t_in == not_a_date_time)
            {
                return Quantity::from_value(-1);
            }
            else
            {
                const int MICROSEC_IN_SEC = 1000000;
                
                date_duration date_diff = t_in.date() - date(1970,1,1);
                time_duration time_diff = t_in.time_of_day();
                
                return Quantity(
                    MicroTime::from_value(
                        static_cast<std::int64_t>(date_diff.days())*24*3600*MICROSEC_IN_SEC + 
                        static_cast<std::int64_t>(time_diff.total_seconds())*MICROSEC_IN_SEC +
                        static_cast<std::int64_t>(time_diff.fractional_seconds()) /
                        (time_duration::ticks_per_second() / MICROSEC_IN_SEC))
                    );
            }
        }

        /// \brief Convert from boost::posix_time::ptime to boost::units::quantity<...> of time
        template<typename Quantity>
            boost::posix_time::ptime to_ptime(Quantity t_in)
        {
            std::int64_t t_in_value = MicroTime(t_in)/MicroTimeUnit();
            
            using namespace boost::posix_time;
            using namespace boost::gregorian;
    
            if (t_in_value == -1)
                return boost::posix_time::ptime(not_a_date_time);
            else
            {
                const int MICROSEC_IN_SEC = 1000000;
                ptime time_t_epoch(date(1970,1,1));
                std::int64_t m = t_in_value / MICROSEC_IN_SEC / 60;
                std::int64_t s = (t_in_value / MICROSEC_IN_SEC) - m*60;
                std::int64_t micro_s = (t_in_value - (s + m*60) * MICROSEC_IN_SEC);
                return time_t_epoch + minutes(m) + seconds(s) + microseconds(micro_s);
            }
        }

        
        /// \brief Returns current UTC date-time as a human-readable string
        inline std::string str()
        {
            std::stringstream ss;
            ss << to_ptime(goby::time::now());
            return ss.str();
        }

        /// \brief Returns current UTC date-time as an ISO string suitable for file names (no spaces or special characters, e.g. 20180322T215258)
        inline std::string file_str()
        {
            auto now = boost::units::round(goby::time::now<goby::time::SITime>());
            return boost::posix_time::to_iso_string(to_ptime(now));
        }
    }
    

       
    //@}
    
}

#endif
