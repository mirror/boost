

::

    facade_iterator_category(C, V, R) =
        if (C is convertible to input_iterator_tag or output_iterator_tag) then
            return C
        else if (C is convertible to incrementable_traversal_tag) then
            if (R is a reference type
                and C is convertible to forward_traversal_tag) then
                if (C is convertible to random_access_traversal_tag)
                    return a type convertible to random_access_iterator_tag
                else if (C is convertible to bidirectional_traversal_tag)
                    return a type convertible to bidirectional_iterator_tag
                else
                    return a type convertible to forward_iterator_tag
            else if (C is convertible to single_pass_traversal_tag
                     and R is convertible to V)
                return a type convertible to input_iterator_tag
            else
                return C

.. Copyright David Abrahams 2004. Use, modification and distribution is
.. subject to the Boost Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
