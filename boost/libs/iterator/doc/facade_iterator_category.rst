* if ``C`` is convertible to ``std::input_iterator_tag`` or
  ``C`` is convertible to ``std::output_iterator_tag``,
  ``iterator_category`` is the same as ``C``.  

* Otherwise, if ``C`` is not convertible to
  ``incrementable_traversal_tag``, the program is ill-formed 

* Otherwise:

  - ``iterator_category`` is convertible to the iterator
    category tag or tags given by the following algorithm, and
    not to any more-derived iterator category tag or tags::

      if (R is a reference type
          && C is convertible to forward_traversal_tag)
      {
          if (C is convertible to random_access_traversal_tag)
              random_access_iterator_tag
          else if (C is convertible to bidirectional_traversal_tag)
              bidirectional_iterator_tag
          else
              forward_iterator_tag
      }
      else
      {
          if (C is convertible to single_pass_traversal_tag
              && R is convertible to V)
              input_iterator_tag
          else
              C
      }

  - ``iterator_traversal<X>::type`` is convertible to the most
    derived traversal tag type to which ``C`` is also
    convertible, and not to any more-derived traversal tag type.

.. Copyright David Abrahams 2004. Use, modification and distribution is
.. subject to the Boost Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
