// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>
# include <boost/parameter/aux_/parenthesized_type.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept_check/has_constraints.hpp>
#  include <boost/mpl/if.hpp>
# endif

// This implementation works on Comeau and GCC, all the way back to
// 2.95
namespace boost
{
  template <class ModelFnPtr>
  struct concept_check_;
  
    namespace concept_checking
  {
    template <void(*)()> struct instantiate {};
  }
  
  template <class Model>
  struct concept_check
  {
      static void failed() { ((Model*)0)->~Model(); }
  };

# ifdef BOOST_OLD_CONCEPT_SUPPORT

  template <class Model>
  struct constraint_check
  {
      static void failed() { ((Model*)0)->constraints(); }
  };
  
  template <class Model>
  struct concept_check_<void(*)(Model)>
    : mpl::if_c<
          concept_checking::has_constraints<Model>::value
        , constraint_check<Model>
        , concept_check<Model>
      >::type
  {};
  
# else
  
  template <class Model>
  struct concept_check_<void(*)(Model)>
    : concept_check<Model>
  {};
  
# endif

#  define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )     \
  typedef boost::concept_checking::instantiate<     \
      &boost::concept_check_<ModelFnPtr>::failed>   \
      BOOST_PP_CAT(boost_concept_check,__LINE__)

}

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
