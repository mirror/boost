// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef NODE_ITERATOR2_DWA2004110_HPP
# define NODE_ITERATOR2_DWA2004110_HPP

# include "node.hpp"
# include <boost/iterator/iterator_facade.hpp>

# ifndef BOOST_NO_SFINAE
#  include <boost/type_traits/is_convertible.hpp>
#  include <boost/utility/enable_if.hpp>
# endif

namespace impl
{
  template <class Value>
  class node_iterator
    : public boost::iterator_facade<
          node_iterator<Value>
        , Value
        , boost::forward_traversal_tag
      >
  {
   private:
      enum enabler {};
      
   public:
      node_iterator()
        : m_node(0)
      {}

      explicit node_iterator(Value* p)
        : m_node(p)
      {}

      template <class OtherValue>
      node_iterator(
          node_iterator<OtherValue> const& other
# ifndef BOOST_NO_SFINAE
        , typename boost::enable_if<boost::is_convertible<OtherValue*,Value*>,enabler*>::type = 0
# endif 
      )
        : m_node(other.m_node)
      {
      }
        

      friend class boost::iterator_core_access;
# if !BOOST_WORKAROUND(__GNUC__, == 2)
   private: // GCC2 can't even grant that friendship to template member functions
# endif 
      template <class OtherValue>
      bool equal(node_iterator<OtherValue> const& other) const
      { return this->m_node == other.m_node; }
    
   public:
      void increment()
      { m_node = m_node->next(); }

      Value& dereference() const
      { return *m_node; }

# ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
   public:
# else 
      template <class> friend class node_iterator;
# endif 
      Value* m_node;
  };
}

typedef impl::node_iterator<node_base> node_iterator;
typedef impl::node_iterator<node_base const> node_const_iterator;

#endif // NODE_ITERATOR2_DWA2004110_HPP
