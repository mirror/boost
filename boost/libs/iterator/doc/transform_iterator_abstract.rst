The transform iterator adapts an iterator by applying some function
object to the result of dereferencing the iterator. In other words,
the ``operator*`` of the transform iterator first dereferences the
base iterator, passes the result of this to the function object, and
then returns the result.
