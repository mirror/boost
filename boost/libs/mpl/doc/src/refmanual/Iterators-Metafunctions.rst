
From the implementation standpoint, iterators are almost-opaque types which
guarantee to provide us with the only memeber that we can access directly:
their category. Incrementing, dereferencing and the rest of iterator 
functionality is available to us through the accosiated iterator 
metafunctions.

