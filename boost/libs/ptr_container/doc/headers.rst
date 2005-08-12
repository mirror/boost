++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++

.. |Boost| image:: cboost.gif

===============
Library headers
===============

======================================================= =============================================================
             **Header**                                    **Includes**

``<boost/ptr_container/clone_allocator.hpp>``            classes heap_clone_allocator_  and view_clone_allocator_
                                                         and functions ``new_clone()`` and ``delete_clone()``

``<boost/ptr_container/ptr_deque.hpp>``                  class `ptr_deque <ptr_deque.html>`_ (and ``std::deque``)

``<boost/ptr_container/ptr_list.hpp>``                   class `ptr_list <ptr_list.html>`_  (and ``std::list``)

``<boost/ptr_container/ptr_vector.hpp>``                 class `ptr_vector <ptr_vector.html>`_ (and ``std::vector``)

``<boost/ptr_container/ptr_array.hpp>``                  class `ptr_array <ptr_array.html>`_ (and ``boost::array``)

``<boost/ptr_container/ptr_set.hpp>``                      classes `ptr_set <ptr_set.html>`_ and `ptr_multiset <ptr_multiset.html>`_
                                                           (and ``std::set`` and ``std::multiset``)

``<boost/ptr_container/ptr_map.hpp>``                      classes `ptr_map <ptr_map.html>`_ and `ptr_multimap <ptr_multimap.html>`_
                                                           (and ``std::map`` and ``std::multimap``)

``<boost/ptr_container/ptr_sequence_adapter.hpp>``       class `ptr_sequence_adapter <ptr_sequence_adapter.html>`_

``<boost/ptr_container/ptr_set_adapter.hpp>``            classes `ptr_set_adapter <ptr_set_adapter.html>`_ and `ptr_multiset_adapter <ptr_multiset_sdapter.html>`_

``<boost/ptr_container/ptr_map_adapter.hpp>``            classes `ptr_map_adapter <ptr_map_adapter.html>`_ and `ptr_multimap_adapter <ptr_multimap_adapter.html>`_

``<boost/ptr_container/exception.hpp>``                  classes ``bad_ptr_container_operation``, ``bad_index``
                                                           and ``bad_pointer``
``<boost/ptr_container/indirect_fun.hpp>``               class ``indirect_fun``

``<boost/ptr_container/nullable.hpp>``                   class ``nullable``
======================================================= =============================================================

.. _`heap_clone_allocator`: reference.html#the-clone-allocator-concept
.. _`view_clone_allocator`: reference.html#the-clone-allocator-concept

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_


:copyright:     Thorsten Ottosen 2004-2005.

