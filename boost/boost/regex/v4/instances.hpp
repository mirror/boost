/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         instances.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Defines those template instances that are placed in the
  *                library rather than in the users object files.
  */

//
// note no include guard, we may include this multiple times:
//
#ifndef BOOST_REGEX_NO_EXTERNAL_TEMPLATES

namespace boost{

//
// this header can be included multiple times, each time with
// a different character type, BOOST_REGEX_CHAR_T must be defined
// first:
//
#ifndef BOOST_REGEX_CHAR_T
#  error "BOOST_REGEX_CHAR_T not defined"
#endif

//
// what follows is compiler specific:
//

#if  defined(__BORLANDC__) && (__BORLANDC__ < 0x600)

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#  ifndef BOOST_REGEX_INSTANTIATE
#     pragma option push -Jgx
#  endif

template class BOOST_REGEX_DECL basic_regex< BOOST_REGEX_CHAR_T >;

#  ifndef BOOST_REGEX_INSTANTIATE
#     pragma option pop
#  endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#elif defined(BOOST_MSVC) || defined(__ICL)

#  ifndef BOOST_REGEX_INSTANTIATE
#     ifdef __GNUC__
#        define template __extension__ extern template
#     else
#        define template extern template
#     endif
#  endif

#  ifdef BOOST_MSVC
#     pragma warning(push)
#     pragma warning(disable : 4251 4231 4660)
#  endif

template class BOOST_REGEX_DECL basic_regex< BOOST_REGEX_CHAR_T >;
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
template class BOOST_REGEX_DECL match_results< const BOOST_REGEX_CHAR_T* >;
#endif
#ifndef BOOST_NO_STD_ALLOCATOR
template class BOOST_REGEX_DECL ::boost::re_detail::perl_matcher<BOOST_REGEX_CHAR_T const *, match_results< const BOOST_REGEX_CHAR_T* >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >;
#endif
#if !(defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB <= 1))\
   && !(defined(BOOST_INTEL_CXX_VERSION) && (BOOST_INTEL_CXX_VERSION <= 800))\
   && !(defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
template class BOOST_REGEX_DECL match_results< std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator >;
#endif
#ifndef BOOST_NO_STD_ALLOCATOR
template class BOOST_REGEX_DECL ::boost::re_detail::perl_matcher< std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator, match_results< std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >;
#endif
#endif


#  ifdef BOOST_MSVC
#     pragma warning(pop)
#  endif

#  ifdef template
#     undef template
#  endif

#elif (defined(__GNUC__) && (__GNUC__ >= 3))

#  ifndef BOOST_REGEX_INSTANTIATE
#     define template __extension__ extern template
#  endif

template BOOST_REGEX_DECL basic_regex<BOOST_REGEX_CHAR_T>& 
   basic_regex<BOOST_REGEX_CHAR_T>::do_assign(
      const BOOST_REGEX_CHAR_T* p1, 
      const BOOST_REGEX_CHAR_T* p2, 
      flag_type f);
template BOOST_REGEX_DECL basic_regex<BOOST_REGEX_CHAR_T>::locale_type BOOST_REGEX_CALL 
   basic_regex<BOOST_REGEX_CHAR_T>::imbue(locale_type l);

template BOOST_REGEX_DECL void BOOST_REGEX_CALL 
   match_results<const BOOST_REGEX_CHAR_T*>::maybe_assign(
      const match_results<const BOOST_REGEX_CHAR_T*>& m);


template BOOST_REGEX_DECL void ::boost::re_detail::perl_matcher<BOOST_REGEX_CHAR_T const *, match_results< const BOOST_REGEX_CHAR_T* >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >::construct_init(
      BOOST_REGEX_CHAR_T const * first, BOOST_REGEX_CHAR_T const * end, 
      match_results<BOOST_REGEX_CHAR_T const *>& what, 
      const basic_regex<BOOST_REGEX_CHAR_T>& e,
      match_flag_type f);
template BOOST_REGEX_DECL bool ::boost::re_detail::perl_matcher<BOOST_REGEX_CHAR_T const *, match_results< const BOOST_REGEX_CHAR_T* >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >::match();
template BOOST_REGEX_DECL bool ::boost::re_detail::perl_matcher<BOOST_REGEX_CHAR_T const *, match_results< const BOOST_REGEX_CHAR_T* >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >::find();

#if defined(__GLIBCPP__) || defined(__GLIBCXX__)
// std:basic_string<>::const_iterator instances as well:
template BOOST_REGEX_DECL void BOOST_REGEX_CALL 
   match_results<std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator>::maybe_assign(
      const match_results<std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator>& m);

template BOOST_REGEX_DECL void ::boost::re_detail::perl_matcher<std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator, match_results< std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >::construct_init(
      std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator first, std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator end, 
      match_results<std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator>& what, 
      const basic_regex<BOOST_REGEX_CHAR_T>& e,
      match_flag_type f);
template BOOST_REGEX_DECL bool ::boost::re_detail::perl_matcher<std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator, match_results< std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >::match();
template BOOST_REGEX_DECL bool ::boost::re_detail::perl_matcher<std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator, match_results< std::basic_string<BOOST_REGEX_CHAR_T>::const_iterator >::allocator_type, boost::regex_traits<BOOST_REGEX_CHAR_T > >::find();
#endif

#  ifdef template
#     undef template
#  endif


#endif

} // namespace boost

#endif // BOOST_REGEX_NO_EXTERNAL_TEMPLATES





