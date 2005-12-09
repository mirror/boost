++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: boost.png

================
Usage Guidelines
================

The recommended usage pattern of the container classes are the same as the 
for normal standard containers.  

``ptr_vector``, ``ptr_list`` and ``ptr_deque`` offer the programmer different 
complexity tradeoffs and should be used accordingly.  ``ptr_vector`` is the 
type of sequence that should be used by default.  ``ptr_list`` should be used 
when there are frequent insertions and deletions from the middle of the 
sequence and if the container is fairly large (eg.  more than 100 
elements).  ``ptr_deque`` is the data structure of choice when most insertions 
and deletions take place at the beginning or at the end of the sequence.  
The special container ``ptr_array`` may be used when the size of the container is invariant
and known at compile time.

An associative container supports unique keys if it may contain at most 
one element for each key. Otherwise, it supports equivalent keys.  
``ptr_set`` and ``ptr_map`` support unique keys.  
``ptr_multiset`` and ``ptr_multimap`` 
support equivalent keys.  

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_

:copyright:     Thorsten Ottosen 2004-2005. 

