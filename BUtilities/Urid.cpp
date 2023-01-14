/* Urid.cpp
 * Copyright (C) 2021 - 2023  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "Urid.hpp"
#include <cstdint>
#include <mutex>
#include <string>

namespace BUtilities 
{

std::map<std::string, uint32_t> Urid::map_ = makeMap ();
uint32_t Urid::count_ = 1;
std::mutex Urid::mx_;

uint32_t Urid::add (const std::string& uri)
{
    mx_.lock();
    if (uri != "") map_[uri] = count_;
    else map_[std::string (BUTILITIES_URID_ANONYMOUS_URI) + "_" + std::to_string (count_)] = count_;
    mx_.unlock();
    return count_++;
}

std::string Urid::uri (const uint32_t urid)
{
    mx_.lock();
    std::string uristr = "";
    for (std::map<std::string, uint32_t>::const_iterator it = map_.begin(); it != map_.end(); ++it) 
    {
        if (it->second == urid)
        {
            uristr = it->first;
            break;
        }
    }
    mx_.unlock();
    return uristr;
}

uint32_t Urid::urid (const std::string& uri)
{
    mx_.lock();
    std::map<std::string, uint32_t>::const_iterator it = map_.find (uri);
    if (it != map_.end ()) 
    {
        const uint32_t id = it->second;
        mx_.unlock();
        return id;
    }
    mx_.unlock();
    return add (uri);
}

std::map<std::string, uint32_t> Urid::makeMap ()
{
    std::map<std::string, uint32_t> m;
    m[BUTILITIES_URID_UNKNOWN_URI] = BUTILITIES_URID_UNKNOWN_URID;
    return m;
}

}