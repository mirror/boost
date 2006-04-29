// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept_check/has_constraints.hpp>
#  include <boost/mpl/if.hpp>
# endif


namespace boost
{  
  template <class Model>
  struct concept_check
  {
      virtual void failed(Model* x)
      {
          x->~Model();
      }
      
      int test;
  };

# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
  template <class Model>
  struct constraint_check
  {
      virtual void failed(Model* x)
      {
          x->constraints();
      }
      
      int test;
  };
  
  template <class Model>
  typename mpl::if_c<
      concept_checking::has_constraints<Model>::value
    , constraint_check<Model>
    , concept_check<Model>
  >::type concept_check_(void(*)(Model));
  
# else
  
  template <class Model>
  concept_check<Model> concept_check_(void(*)(Model));
  
# endif
  
  // Usage, in class or function context:
  //
  //     BOOST_CONCEPT_ASSERT((UnaryFunctionConcept<F,bool,int>));
#  define BOOST_CONCEPT_ASSERT( ModelInParens )                         \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =                   \
         sizeof(boost::concept_check_((void(*) ModelInParens)0).test)   \
  }
}

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
