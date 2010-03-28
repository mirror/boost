// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EXT_FOR_EACH_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EXT_FOR_EACH_HPP_INCLUDED

#include <boost/range/config.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/assert.hpp>

namespace boost
{
	namespace range_detail
	{
		template<class InputIterator1, class InputIterator2, class Fn2>
		inline Fn2 for_each_impl(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 Fn2 fn)
		{
			for (; first1 != last1 && first2 != last2; ++first1, ++first2)
			{
				fn(*first1, *first2);
			}
			return fn;
		}
	}

	template<class SinglePassRange1, class SinglePassRange2, class Fn2>
	inline Fn2 for_each(const SinglePassRange1& rng1, const SinglePassRange2& rng2, Fn2 fn)
	{
		return range_detail::for_each_impl(boost::begin(rng1), boost::end(rng1),
			boost::begin(rng2), boost::end(rng2), fn);
	}

	template<class SinglePassRange1, class SinglePassRange2, class Fn2>
	inline Fn2 for_each(const SinglePassRange1& rng1, SinglePassRange2& rng2, Fn2 fn)
	{
		return range_detail::for_each_impl(boost::begin(rng1), boost::end(rng1),
			boost::begin(rng2), boost::end(rng2), fn);
	}

	template<class SinglePassRange1, class SinglePassRange2, class Fn2>
	inline Fn2 for_each(SinglePassRange1& rng1, const SinglePassRange2& rng2, Fn2 fn)
	{
		return range_detail::for_each_impl(boost::begin(rng1), boost::end(rng1),
			boost::begin(rng2), boost::end(rng2), fn);
	}

	template<class SinglePassRange1, class SinglePassRange2, class Fn2>
	inline Fn2 for_each(SinglePassRange1& rng1, SinglePassRange2& rng2, Fn2 fn)
	{
		return range_detail::for_each_impl(boost::begin(rng1), boost::end(rng1),
			boost::begin(rng2), boost::end(rng2), fn);
	}
}

#endif // include guard
