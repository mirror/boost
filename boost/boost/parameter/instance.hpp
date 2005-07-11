// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARAMETER_INSTANCE_DWA2005710_HPP
# define BOOST_PARAMETER_INSTANCE_DWA2005710_HPP

namespace boost { namespace parameter { 

template <class Tag> struct keyword;

struct instance
{
    template <class Tag>
    operator keyword<Tag>&() const
    {
        return keyword<Tag>::get();
    }
};

}} // namespace boost::parameter

#endif // BOOST_PARAMETER_INSTANCE_DWA2005710_HPP
