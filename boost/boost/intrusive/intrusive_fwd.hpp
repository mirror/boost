/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga  2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_FWD_HPP
#define BOOST_INTRUSIVE_FWD_HPP

#include <cstddef>
#include <boost/functional/hash_fwd.hpp>
#include <boost/intrusive/tag.hpp>
#include <boost/intrusive/linking_policy.hpp>

//std predeclarations
namespace std{

template<class T>
struct equal_to;

template<class T>
struct less;

}  //namespace std{

namespace boost {
namespace intrusive {

////////////////////////////
//     Node algorithms
////////////////////////////

//Algorithms predeclarations
template<class NodeTraits>
class circular_list_algorithms;

template<class NodeTraits>
class circular_slist_algorithms;

template<class NodeTraits>
class rbtree_algorithms;

////////////////////////////
//       Containers
////////////////////////////

//slist
template < class ValueTraits
         , bool ConstantTimeSize = true
         , class SizeType        = std::size_t>
class slist;

template< class Tag              = tag
        , linking_policy Policy  = safe_link
        , class VoidPointer      = void *
        >
class slist_base_hook;

template< linking_policy Policy  = safe_link
        , class VoidPointer      = void *>
class slist_member_hook;

//list
template< class ValueTraits
        , bool  ConstantTimeSize = true
        , class SizeType         = std::size_t>
class list;

template< class Tag              = tag
        , linking_policy Policy  = safe_link
        , class VoidPointer      = void *
        >
class list_base_hook;

template< linking_policy Policy  = safe_link
        , class VoidPointer      = void *>
class list_member_hook;

//hash/unordered
template< class ValueTraits
        , class Hash             = boost::hash<typename ValueTraits::value_type>
        , class Equal            = std::equal_to<typename ValueTraits::value_type>
        , bool  ConstantTimeSize = true
        , class SizeType         = std::size_t
        >
class hashtable;

template< class ValueTraits
        , class Hash             = boost::hash<typename ValueTraits::value_type>
        , class Equal            = std::equal_to<typename ValueTraits::value_type>
        , bool  ConstantTimeSize = true
        , class SizeType         = std::size_t
        >
class unordered_set;

template< class ValueTraits
        , class Hash             = boost::hash<typename ValueTraits::value_type>
        , class Equal            = std::equal_to<typename ValueTraits::value_type>
        , bool  ConstantTimeSize = true
        , class SizeType         = std::size_t
        >
class unordered_multiset;

template< class Tag              = tag
        , linking_policy Policy  = safe_link
        , class VoidPointer      = void *
        >
class unordered_set_base_hook;

template< linking_policy Policy  = safe_link
        , class VoidPointer      = void *>
class unordered_set_member_hook;


//rbtree/set
template < class ValueTraits
         , class Compare         = std::less<typename ValueTraits::value_type>
         , bool ConstantTimeSize = true
         , class SizeType        = std::size_t
         >
class rbtree;

template < class ValueTraits
         , class Compare         = std::less<typename ValueTraits::value_type>
         , bool ConstantTimeSize = true
         , class SizeType        = std::size_t>
class set;

template < class ValueTraits
         , class Compare         = std::less<typename ValueTraits::value_type>
         , bool ConstantTimeSize = true
         , class SizeType        = std::size_t>
class multiset;

template< class Tag              = tag
        , linking_policy Policy  = safe_link
        , class VoidPointer      = void *
        >
class set_base_hook;

template< linking_policy Policy  = safe_link
        , class VoidPointer      = void *>
class set_member_hook;

}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_FWD_HPP
