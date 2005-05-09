// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARAMETER_INDEX_RESULT_DWA200558_HPP
# define BOOST_PARAMETER_INDEX_RESULT_DWA200558_HPP

# include <boost/mpl/apply.hpp>
# include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { 

// A metafunction that, given an argument pack, returns the type
template <class Parameters, class Keyword, class Default = aux::void_>
struct index_result
  : mpl::apply_wrap2<typename Parameters::index_result,Keyword,Default>
{};

}} // namespace boost::parameter

#endif // BOOST_PARAMETER_INDEX_RESULT_DWA200558_HPP
