// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/lib/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
// Revisions:
// 27 Apr 2008 (added forward declaration of boost::swap overload) Niels Dekker
// 
#ifndef BOOST_OPTIONAL_OPTIONAL_FWD_FLC_19NOV2002_HPP
#define BOOST_OPTIONAL_OPTIONAL_FWD_FLC_19NOV2002_HPP

namespace boost {

template<class T> class optional ;

template<class T> void swap ( optional<T>& , optional<T>& ) ;

} // namespace boost

#endif

