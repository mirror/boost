
The metafunctions that form the essential interface of sequence `classes`__
documented in the corresponding |sequence concepts| are known as 
*intrinsic sequence operations*. They differ from generic 
|sequence algorithms| in that, in general, they need to be implemented 
from scratch for each new sequence class [#intrinsic]_. 

__ `label-Sequences-Classes`_

It's worth noting that STL counterparts of these metafunctions are 
usually implemented as member functions.

.. [#intrinsic] In practice, many of intrinsic metafunctions offer a 
   default implementation that will work in majority of cases, given 
   that you've implemented the core functionality they rely on (such 
   as |begin| / |end|).

