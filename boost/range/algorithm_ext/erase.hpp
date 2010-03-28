// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EXT_ERASE_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EXT_ERASE_HPP_INCLUDED

#include <boost/range/config.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/assert.hpp>

namespace boost
{
	template< class Container >
	inline void erase( Container& on, 
		  iterator_range<BOOST_DEDUCED_TYPENAME Container::iterator> to_erase )
	{
		on.erase( boost::begin(to_erase), boost::end(to_erase) );
	}

	template< class Container, class T >
	inline void remove_erase( Container& on, const T& val )
	{
		on.erase(
			std::remove(boost::begin(on), boost::end(on), val),
			boost::end(on));
	}

	template< class Container, class Pred >
	inline void remove_erase_if( Container& on, Pred pred )
	{
		on.erase(
			std::remove_if(boost::begin(on), boost::end(on), pred),
			boost::end(on));
	}
}

#endif // include guard
