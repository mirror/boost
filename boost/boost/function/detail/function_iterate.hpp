#if !defined(BOOST_PP_IS_ITERATING)
# error Boost.Function - do not include this file!
#endif

#define BOOST_FUNCTION_NUM_ARGS BOOST_PP_ITERATION()
#include <boost/function/detail/maybe_include.hpp>
#undef BOOST_FUNCTION_NUM_ARGS

