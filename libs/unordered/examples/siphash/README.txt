Siphash example
---------------

Most of the commonly used hash functions are vunerable to
'hash-flooding' attacks. These can happen if the table is filled with
values which are likely to cause hash collisions. SipHash[1] is a fast
hash function proposed by Jean-Philippe Aumasson and Daniel J.
Bernstein2 to resist these attacks. While young and relatively untested,
it's been demonstrated that it's less vulnerable to attacks than popular
hash functions, such as MurmurHash and CityHash.

This a nice example, as it has a distinct practial use to boost::hash
and demonstrates a hash function with state. It also shows how a generic
hash function might be built on top of a binary hash function.

Note that this is an example, and far from fully polished. Some issues
with the current implementation:

 - It's slow.
 - Only works on little endian machines.
 - Only supports a subset of the standard library.

I should improve it a bit before it's properly released. But if you wish
to implement something better, there are several C implementations
listed on the SipHash page[1]. I probably won't even try to compete with
them. If anyone is willing to implement a high quality SipHash library for
boost, that would be very much appreciated.

[1] https://131002.net/siphash/

--------------------------------------------------------------------------------

Copyright 2012 Daniel James.
Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
