
//  (C) Copyright John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//
// defines alignment_of:

#ifndef ALIGNMENT_TYPE_TRAITS_HPP
#define ALIGNMENT_TYPE_TRAITS_HPP

#include <cstdlib>
#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#include <boost/type_traits/ice.hpp>
#endif

namespace boost{
//
// get the alignment of some arbitrary type:
namespace detail{

template <class T>
struct alignment_of_hack
{
   char c;
   T t;
   alignment_of_hack();
};

template <unsigned A, unsigned S>
struct alignment_logic
{
   BOOST_DECL_MC(std::size_t, value, A < S ? A : S);
};

} // namespace detail

template <class T>
struct alignment_of
{
   BOOST_DECL_MC(std::size_t, value,
      (::boost::detail::alignment_logic<
         sizeof(detail::alignment_of_hack<T>) - sizeof(T),
         sizeof(T)
      >::value));
};

//
// references have to be treated specially, assume
// that a reference is just a special pointer:
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct alignment_of<T&>
{
public:
   BOOST_DECL_MC(std::size_t, value, alignment_of<T*>::value);
};
#endif
//
// void has to be treated specially:
template <>
struct alignment_of<void>
{ BOOST_DECL_MC(std::size_t, value, 0); };
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <>
struct alignment_of<const void>
{ BOOST_DECL_MC(std::size_t, value, 0); };
template <>
struct alignment_of<volatile void>
{ BOOST_DECL_MC(std::size_t, value, 0); };
template <>
struct alignment_of<const volatile void>
{ BOOST_DECL_MC(std::size_t, value, 0); };
#endif

} // namespace boost

#endif // ALIGNMENT_TYPE_TRAITS_HPP

 
