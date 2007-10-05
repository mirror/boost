

All iterators in MPL are classified into three iterator concepts, or 
`categories`, named according to the type of traversal provided. The
categories are: |Forward Iterator|, |Bidirectional Iterator|, and 
|Random Access Iterator|. The concepts are hierarchical: 
|Random Access Iterator| is a refinement of |Bidirectional Iterator|,
which, in its turn, is a refinement of |Forward Iterator|.

Because of the inherently immutable nature of the value access, MPL 
iterators escape the problems of the traversal-only categorization 
discussed at length in [n1550]_.


.. [n1550] http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2003/n1550.htm
