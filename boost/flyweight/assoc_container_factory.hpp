/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_ASSOC_CONTAINER_FACTORY_HPP
#define BOOST_FLYWEIGHT_ASSOC_CONTAINER_FACTORY_HPP

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/assoc_container_factory_fwd.hpp>
#include <boost/flyweight/factory_tag.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

/* Factory class using a given associative container.
 */

namespace boost{

namespace flyweights{

template<typename Container>
class assoc_container_factory_class:public factory_marker
{
public:
  typedef typename Container::iterator   handle_type;
  typedef typename Container::value_type entry_type;
  
  handle_type insert(const entry_type& x)
  {
    return cont.insert(x).first;
  }

  void erase(handle_type h)
  {
    cont.erase(h);
  }

  static const entry_type& entry(handle_type h){return *h;}

private:  
  Container cont;

public:
  typedef assoc_container_factory_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,assoc_container_factory_class,(Container))
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/* This is preferred to deriving from factory_marker since checking for
 * derivation forces the instantiation of the specifier, which is not
 * needed when the specifier is a placeholder expression.
 */

template<typename Container>
struct is_factory<assoc_container_factory_class<Container> >:
  boost::mpl::true_{};
#endif

/* assoc_container_factory_class specifier */

template<
  typename ContainerSpecifier
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF
>
struct assoc_container_factory:factory_marker
{
  template<typename Entry,typename Key>
  struct apply
  {
    typedef assoc_container_factory_class<
      typename mpl::apply2<ContainerSpecifier,Entry,Key>::type
    > type;
  };
};

}  /* namespace flyweights */

} /* namespace boost */

#endif
