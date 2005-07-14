// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARAMETER_MATCH_ARGS_DWA2005714_HPP
# define BOOST_PARAMETER_MATCH_ARGS_DWA2005714_HPP

# include <boost/detail/workaround.hpp>

# if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#  include <boost/parameter/config.hpp>
#  include <boost/parameter/aux_/void.hpp>
#  include <boost/preprocessor/arithmetic/sub.hpp>
#  include <boost/preprocessor/facilities/intercept.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#  define BOOST_PARAMETER_MATCH_ARGS(N)                     \
    BOOST_PP_ENUM_TRAILING_PARAMS(                          \
        BOOST_PP_SUB(BOOST_PARAMETER_MAX_ARITY,N)           \
      , ::boost::parameter::aux::void_ BOOST_PP_INTERCEPT   \
    )

# else

#  define BOOST_PARAMETER_MATCH_ARGS(N)

# endif 

#endif // BOOST_PARAMETER_MATCH_ARGS_DWA2005714_HPP
