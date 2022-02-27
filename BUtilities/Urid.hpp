/* Urid.hpp
 * Copyright (C) 2021  Sven Jähnichen
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
#ifndef BUTILITIES_URID_HPP_
#define BUTILITIES_URID_HPP_

#include <cstdint>
#include <string>
#include <map>
#include <mutex>

#ifndef URID_URI
#define URID_URI "https://github.com/sjaehn/BWidgets/BUtilities/Urid.hpp"
#endif

#ifndef URID_UNKNOWN_URI
#define URID_UNKNOWN_URI URID_URI "#Unknown"
#endif

#ifndef URID_UNKNOWN_URID
#define URID_UNKNOWN_URID 0
#endif

#ifndef URID_ANONYMOUS_URI
#define URID_ANONYMOUS_URI URID_URI "#Anonymous"
#endif

namespace BUtilities 
{

/**
 *  @brief  Map class to store and convert URIs.
 *
 *  TODO: Not fully implemented yet!
 */
class Urid
{
protected:
    static std::map<std::string, uint32_t> map_;
    static uint32_t count_;
    static std::mutex mx_;
    
public:

    /**
     *  @brief  Adds an URI (if not exists before).
     *  @param uri  URI.
     */
    static uint32_t add (const std::string& uri);

    /**
     *  @brief  Converts an URI to an URID.
     *  @param uri  URI.
     *  @return  URID.
     *
     *  Adds the URI if not exists before.
     *  If no URI is provided (uri = ""), then URID_ANONYMOUS_URI + "_" and 
     *  the next free URID number is used.
     */
    static uint32_t urid (const std::string& uri);

    /**
     *  @brief  Converts an URID to an URI.
     *  @param urid  URID.
     *  @return  URI, or an empty string if the URID didn't exist before.
     */
    static std::string uri (const uint32_t urid);

private:

    /**
     *  @brief  Creates an URID map to start with.
     *  @return  Default URID map.
     */
    static std::map<std::string, uint32_t> makeMap (); 

};

}

#endif /* BUTILITIES_URID_HPP_ */