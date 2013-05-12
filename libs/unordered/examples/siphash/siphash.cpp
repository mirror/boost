
// Copyright 2012 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This is also released into the public domain.

#include "siphash.hpp"

namespace hash
{
    const unsigned siphash_c = 2;
    const unsigned siphash_d = 4;

    siphash_state::siphash_state(sipkey const& key) :
        v0(0x736f6d6570736575ull ^ key.k0),
        v1(0x646f72616e646f6dull ^ key.k1),
        v2(0x6c7967656e657261ull ^ key.k0),
        v3(0x7465646279746573ull ^ key.k1),
        buffered(0), b(0)
    {
    }

    namespace
    {
        inline boost::uint64_t rotate_left(boost::uint64_t x, unsigned c)
        {
            return (x << c) | (x >> (64-c));
        }
    }

    void siphash_state::sip_round(unsigned rounds)
    {
        for (unsigned i = 0; i < rounds; ++i) {
            v0 += v1;
            v1 = rotate_left(v1, 13);
            v1 ^= v0;
            v0 = rotate_left(v0, 32);

            v2 += v3;
            v3 = rotate_left(v3, 16);
            v3 ^= v2;

            v2 += v1;
            v1 = rotate_left(v1, 17);
            v1 ^= v2;
            v2 = rotate_left(v2, 32);

            v0 += v3;
            v3 = rotate_left(v3, 21);
            v3 ^= v0;
        }
    }

    void siphash_state::update(void const* data, unsigned length)
    {
        char const* ptr = static_cast<char const*>(data);

        while (length > 0) {
            buffer[buffered++] = *ptr++;
            ++b;
            --length;

            if (buffered == 8)
            {
                v3 ^= m;
                sip_round(siphash_c);
                v0 ^= m;
                buffered = 0;
            }
        }
    }

    boost::uint64_t siphash_state::finalize()
    {
        // Compress the final 8 bytes.
        while (buffered < 7) buffer[buffered++] = 0;
        buffer[7] = b;

        v3 ^= m;
        sip_round(siphash_c);
        v0 ^= m;

        // Finalize the hash

        v2 ^= 0xff;
        sip_round(siphash_d);

        return v0 ^ v1 ^ v2 ^ v3;
    }
}
