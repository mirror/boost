#ifndef BOOST_QUICKBOOK_GLOB_HPP
#define BOOST_QUICKBOOK_GLOB_HPP
/*
 Copyright Redshift Software Inc 2011
 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or copy at
 http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Copyright 1994 Christopher Seiwald.  All rights reserved.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*
 * glob.c - match a string against a simple pattern
 *
 * Understands the following patterns:
 *
 *  *   any number of characters
 *  ?   any single character
 *  [a-z]   any single character in the range a-z
 *  [^a-z]  any single character not in the range a-z
 *  \x  match x
 *
 * External functions:
 *
 *  glob() - match a string against a simple pattern
 *
 * Internal functions:
 *
 *  globchars() - build a bitlist to check for character group match
 */

#include <boost/cstdint.hpp>

namespace quickbook
{
    namespace glob_detail
    {
        template < typename Char >
        struct bit_list
        {
            /* bytes used for [chars] in compiled expr */
            enum bit_list_size_t
            {
                bit_list_size = sizeof(Char)/8
            };

            boost::uint8_t tab[bit_list_size];

            bit_list()
            {
                for (unsigned i = 0; i<bit_list_size; ++i)
                    tab[i] = 0;
            }

            bool operator[](unsigned bit)
            {
                return (tab[bit/8]&(1<<(bit%8)));
            }

            void set(unsigned bit)
            {
                /* `bit != 0` :: Do not include \0 in either $[chars] or $[^chars]. */
                if (bit!=0)
                    tab[bit/8] |= (1<<(bit%8) );
            }

            void negate()
            {
                for (unsigned i = 0; i<bit_list_size; ++i)
                    tab[i] ^= 255;
            }
        };

        /*
         * globchars() - build a bitlist to check for character group match.
         */
        template < typename Char >
        bit_list<Char> globchars(const Char * s, const Char * e)
        {
            bit_list<Char> result;

            bool neg = false;

            if (*s==Char('^'))
            {
                neg = true;
                ++s;
            }

            while (s<e)
            {
                Char c;

                if ((s+2<e)&&(s[1]==Char('-')))
                {
                    for (c = s[0]; c<=s[2]; ++c)
                        result.set(c);
                    s += 3;
                }
                else
                {
                    c = *s++;
                    result.set(c);
                }
            }

            if (neg)
                result.negate();

            return result;
        }

        /*
         * glob() - match a string against a simple pattern.
         */
        template < typename Char >
        bool glob(const Char * c, const Char * s, bool & fail)
        {
            const Char eos = Char('\0');

            fail = false;

            while (true)
            {
                if (eos==*c)
                {
                    fail = eos!=*s;
                    return !fail;
                }
                else if (Char('?')==*c)
                {
                    ++c;
                    if (eos==*s++)
                        return false;
                }
                else if (Char('[')==*c)
                {
                    ++c;
                    /* Scan for matching ]. */

                    const Char * here = c;
                    do
                    {
                        if (eos==*c++)
                            return false;
                    }
                    while ((here==c)||(*c!=Char(']')));
                    ++c;

                    /* Build character class bitlist. */

                    glob_detail::bit_list<Char> bitlist =
                        glob_detail::globchars(here, c);

                    if (!bitlist[*s])
                        return false;
                    ++s;
                }
                else if (Char('*')==*c)
                {
                    ++c;
                    const Char * here = s;

                    while (eos!=*s)
                        ++s;

                    /* Try to match the rest of the pattern in a recursive */
                    /* call.  If the match fails we'll back up chars, retrying. */

                    while (s!=here)
                    {
                        bool r = false;

                        /* A fast path for the last token in a pattern. */
                        if (eos!=*c)
                            r = glob(c, s, fail);
                        else if (eos!=*s)
                        {
                            fail = true;
                            r = false;
                        }
                        else
                            r = true;

                        if (r)
                            return true;
                        if (fail)
                            return false;
                        --s;
                    }
                }
                else if (Char('\\')==*c)
                {
                    ++c;
                    /* Force literal match of next char. */
                    if (eos==*c||(*s++!=*c++))
                        return false;
                }
                else
                {
                    ++c;
                    if (*s++!=c[-1])
                        return false;
                }
            }

            return false;
        }
    }

    /*
     * glob() - match a string against a simple pattern.
     */
    template < typename Char >
    bool glob(const Char * pattern, const Char * s)
    {
        bool fail = false;
        bool result = glob_detail::glob(pattern, s, fail);
        return result;
    }
}

#endif
