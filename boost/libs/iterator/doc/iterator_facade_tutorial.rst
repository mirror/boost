.. Copyright David Abrahams 2004. Use, modification and distribution is
.. subject to the Boost Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

Introduction
------------

In this section we'll walk through the implementation of a few
iterators using ``iterator_facade``, based around the simple
example of a linked list of polymorphic objects.

The Problem
-----------

Say we've written a polymorphic linked list node as follows::

  # include <iostream>

  struct node_base
  {
      node_base() : m_next(0) {}

      virtual ~node_base() { delete m_next; }

      node_base* next() const { return m_next; }

      // print to the stream
      virtual void print(std::ostream& s) const = 0;
      
      // double the value
      virtual void twice() = 0;

      void append(node_base* p)
      {
          if (m_next)
              m_next->append(p);
          else
              m_next = p;
      }

   private:
      node_base* m_next;
  };

Lists can hold objects of different types by linking together
specializations of the following template::

  template <class T>
  struct node : node_base
  {
      node(T x)
        : m_value(x)
      {}

      void print(std::ostream& s) const { s << this->m_value; }
      void twice() { m_value += m_value; }

   private:
      T m_value;
  };

And we can print any node using the following streaming operator::

  inline std::ostream& operator<<(std::ostream& s, node_base const& n)
  {
      n.print(s);
      return s;
  }


.. sidebar:: Note

   This is in progress; check the ../example directory for code.