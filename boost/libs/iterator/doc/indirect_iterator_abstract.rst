The indirect iterator adapts an iterator by applying an *extra*
dereference inside of ``operator*()``. For example, this iterator
adaptor makes it possible to view a container of pointers
(e.g. ``list<foo*>``) as if it were a container of the pointed-to type
(e.g. ``list<foo>``) .

.. At some point we should add the capability to handle
   iterators over smart pointers, which the impl handles. -JGS
