/* boost random/detail/uniform_int_float.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP
#define BOOST_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP

#include <boost/config.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/uniform_01.hpp>


namespace boost {
namespace random {
namespace detail {

template<class UniformRandomNumberGenerator, class IntType = unsigned long>
class uniform_int_float
{
public:
    typedef UniformRandomNumberGenerator base_type;
    typedef IntType result_type;

    uniform_int_float(base_type rng, IntType min_arg = 0, IntType max_arg = 0xffffffff)
      : _rng(rng), _min(min_arg), _max(max_arg) {}

    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _min; }
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _max; }
    base_type& base() { return _rng; }
    const base_type& base() const { return _rng; }

    result_type operator()()
    {
        typedef typename base_type::result_type base_result;
        base_result range = static_cast<base_result>(_max-_min)+1;
        uniform_01<typename base_type::result_type> dist;
        return static_cast<IntType>(dist(_rng) * range) + _min;
    }

private:
    base_type _rng;
    result_type _min, _max;
};


} // namespace detail
} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP
