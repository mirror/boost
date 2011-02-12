/* boost random/generate_canonical.hpp header file
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_GENERATE_CANONICAL_HPP
#define BOOST_RANDOM_GENERATE_CANONICAL_HPP

#include <cassert>
#include <algorithm>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/limits.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>

namespace boost {
namespace random {

namespace detail {

template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical_impl(URNG& g, boost::mpl::true_ /*is_integral*/)
{
    using std::pow;
    typedef typename URNG::result_type base_result;
    std::size_t digits = std::numeric_limits<RealType>::digits;
    RealType R = RealType(g.max()) - RealType(g.min()) + 1;
    RealType mult = R;
    RealType limit = pow(RealType(2), RealType((std::min)(bits, digits)));
    RealType S = RealType(detail::subtract<base_result>()(g(), (g.min)()));
    while(mult < limit) {
        RealType inc = RealType(detail::subtract<base_result>()(g(), (g.min)()));
        S += inc * mult;
        mult *= R;
    }
    return S / mult;
}

template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical_impl(URNG& g, boost::mpl::false_ /*is_integral*/)
{
    using std::pow;
    using std::floor;
    assert((g.min)() == 0);
    assert((g.max)() == 1);
    typedef typename URNG::result_type base_result;
    std::size_t digits = std::numeric_limits<RealType>::digits;
    std::size_t engine_bits = g.precision();
    std::size_t b = (std::min)(bits, digits);
    std::size_t k = (b  + engine_bits - 1) / engine_bits;
    RealType R = pow(RealType(2), RealType(engine_bits));
    RealType mult = R;
    RealType limit = pow(RealType(2), RealType(b));
    RealType S = g() - (g.min)();
    while(mult < limit) {
        RealType inc(floor((RealType(g()) - RealType((g.min)())) * R));
        S += inc * mult;
        mult *= R;
    }
    return S / mult;
}

}

/**
 * Returns a value uniformly distributed in the range [0, 1)
 * with at least @c bits random bits.
 */
template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical(URNG& g)
{
    RealType result = detail::generate_canonical_impl<RealType, bits>(
        g, boost::is_integral<typename URNG::result_type>());
    assert(result >= 0);
    assert(result <= 1);
    if(result == 1) {
        result -= std::numeric_limits<RealType>::epsilon() / 2;
        assert(result != 1);
    }
    return result;
}

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_GENERATE_CANONICAL_HPP
