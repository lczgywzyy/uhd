//
// Copyright 2010 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_UHD_UTILS_PROPS_HPP
#define INCLUDED_UHD_UTILS_PROPS_HPP

#include <uhd/config.hpp>
#include <uhd/wax.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/info.hpp>
#include <stdexcept>
#include <vector>
#include <string>

namespace uhd{

    //typedef for handling named properties
    typedef std::vector<std::string> prop_names_t;
    typedef boost::tuple<wax::obj, std::string> named_prop_t;

    /*!
     * Utility function to separate a named property into its components.
     * \param key a reference to the prop object
     * \param name a reference to the name object
     */
    inline UHD_API named_prop_t extract_named_prop(
        const wax::obj &key,
        const std::string &name = ""
    ){
        if (key.type() == typeid(named_prop_t)){
            return key.as<named_prop_t>();
        }
        return named_prop_t(key, name);
    }

    //! The exception to throw for property errors
    struct UHD_API prop_error : virtual std::exception, virtual boost::exception{};

    //! The property error info (verbose or message)
    typedef boost::error_info<struct tag_prop_info, std::string> prop_info;

    /*!
     * Throw an error when trying to get a write only property.
     * Throw-site information will be included with this error.
     */
    #define UHD_THROW_PROP_WRITE_ONLY() \
        BOOST_THROW_EXCEPTION(uhd::prop_error() << uhd::prop_info("cannot get write-only property"))

    /*!
     * Throw an error when trying to set a read only property.
     * Throw-site information will be included with this error.
     */
    #define UHD_THROW_PROP_READ_ONLY() \
        BOOST_THROW_EXCEPTION(uhd::prop_error() << uhd::prop_info("cannot set read-only property"))

} //namespace uhd

#endif /* INCLUDED_UHD_UTILS_PROPS_HPP */
