// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept_check/has_constraints.hpp>
#  include <boost/mpl/if.hpp>
# endif


namespace boost
{
  namespace concept_checking
  {
    template <class Model>
    struct concept_check_
    {
        ~concept_check_();
        virtual void failed(Model* x)
        {
            x->~Model();
        }
    };
  }
  
# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
  namespace concept_checking
  {
    template <class Model>
    struct constraint_check
    {
        virtual void failed(Model* x)
        {
            x->constraints();
        }
    };
  }

  template <class Model>
  struct concept_check
    : mpl::if_c<
          concept_checking::has_constraints<Model>::value
        , concept_checking::constraint_check<Model>
        , concept_checking::concept_check_<Model>
      >::type
  {};
      
# else
  
  template <class Model>
  struct concept_check
    : concept_checking::concept_check_<Model>
  {
      ~concept_check();
  };
  
# endif

# if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

  //
  // The iterator library sees some really strange errors unless we
  // use partial specialization to extract the model type with
  // msvc-7.1
  // 
  template <class Model>
  struct concept_check<void(*)(Model)>
    : concept_check<Model>
  { };

# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )      \
  enum                                              \
  {                                                 \
      BOOST_PP_CAT(boost_concept_check,__LINE__) =  \
         sizeof(::boost::concept_check<ModelFnPtr>) \
  }
  
# else
  
  template <class Model>
  concept_check<Model>
  concept_check_(void(*)(Model));
  
# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )          \
  enum                                                  \
  {                                                     \
      BOOST_PP_CAT(boost_concept_check,__LINE__) =      \
         sizeof(::boost::concept_check_((ModelFnPtr)0)) \
  }
  
# endif 
}

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
