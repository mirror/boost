// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_TRANSLATOR_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_TRANSLATOR_IMPLEMENTATION_HPP_INCLUDED

#include <boost/limits.hpp>

namespace boost { namespace property_tree
{

    namespace detail
    {
        
        ////////////////////////////////////////////////////////////////////////////
        // Helpers

        // Data-to-string converter for std::string
        inline std::string data_to_string(const std::string &data)
        {
            return data;
        }

        // Data-to-string converter for std::basic_string<Ch>
        template<class Ch>
        std::string data_to_string(const std::basic_string<Ch> &data)
        {
            return narrow(data.c_str());
        }

        template<class T>
        struct array_to_pointer_decay
        {
            typedef T type;
        };

        template<class T, std::size_t N>
        struct array_to_pointer_decay<T[N]>
        {
            typedef const T *type;
        };

        ////////////////////////////////////////////////////////////////////////////
        // Extractor

        // Various specializations of extractors and inserters are provided to:
        // 1. Optimize use of strings by copying them directly instead through stringstream
        // 2. Optimize use of native char (i.e the same char as used by data string) by copying 
        //    it directly instead of through stringstream
        // 3. Treat signed and unsigned chars as integers, not as characters, i.e.
        //    pt.put_value(signed char(65)) produces data equal to "65", instead of "A".
        //    Only plain char is treated as a character type, i.e pt.put_value(char(65)) will
        //    produce "A"
        // 4. Allow recognizing various bool strings (0, 1, true, false)
        
        template<class Ch, class T>
        struct extractor
        {
            inline bool operator()(const std::basic_string<Ch> &data, 
                                   T &extracted,
                                   const std::locale &loc) const
            {
                std::basic_istringstream<Ch> stream(data);
                stream.imbue(loc);
                stream >> extracted;
                if (!stream.eof())
                	stream >> std::ws;
                return stream.eof() && !stream.fail() && !stream.bad();
            }
        };

        template<class Ch>
        struct extractor<Ch, std::basic_string<Ch> >
        {
            inline bool operator()(const std::basic_string<Ch> &data, 
                                   std::basic_string<Ch> &extracted,
                                   const std::locale &loc) const
            {
                extracted = data;
                return true;
            }
        };

        template<class Ch>
        struct extractor<Ch, Ch>
        {
            inline bool operator()(const std::basic_string<Ch> &data, 
                                   Ch &extracted,
                                   const std::locale &loc) const
            {
                if (data.size() == 1)
                {
                    extracted = data[0];
                    return true;
                }
                else
                    return false;
            }
        };

        template<class Ch>
        struct extractor<Ch, signed char>
        {
            inline bool operator()(const std::basic_string<Ch> &data, 
                                   signed char &extracted,
                                   const std::locale &loc) const
            {
                std::basic_istringstream<Ch> stream(data);
                stream.imbue(loc);
                int tmp;
                stream >> tmp;
                if (!stream.eof())
	               	stream >> std::ws;
                if (stream.eof() && !stream.fail() && !stream.bad())
                {
                    extracted = static_cast<signed char>(tmp);
                    return true;
                }
                else
                    return false;
            }
        };

        template<class Ch>
        struct extractor<Ch, unsigned char>
        {
            inline bool operator()(const std::basic_string<Ch> &data, 
                                   unsigned char &extracted,
                                   const std::locale &loc) const
            {
                std::basic_istringstream<Ch> stream(data);
                stream.imbue(loc);
                unsigned int tmp;
                stream >> tmp;
                if (!stream.eof())
                	stream >> std::ws;
                if (stream.eof() && !stream.fail() && !stream.bad())
                {
                    extracted = static_cast<unsigned char>(tmp);
                    return true;
                }
                else
                    return false;
            }
        };

        template<class Ch>
        struct extractor<Ch, bool>
        {
            inline bool operator()(const std::basic_string<Ch> &data, 
                                   bool &extracted,
                                   const std::locale &loc) const
            {
                std::basic_istringstream<Ch> stream(data);
                stream.imbue(loc);
                bool tmp;
                stream >> std::boolalpha >> tmp;
                if (!stream.eof())
                    stream >> std::ws;
                if (stream.eof() && !stream.fail() && !stream.bad())
                {
                    extracted = tmp;
                    return true;
                }
                else
                {
                    std::basic_istringstream<Ch> stream2(data);
                    stream2.imbue(loc);
                    bool tmp;
                    stream2 >> tmp;
                    if (!stream2.eof())
                        stream >> std::ws;
                    if (stream2.eof() && !stream2.fail() && !stream2.bad())
                    {
                        extracted = tmp;
                        return true;
                    }
                }
                return false;
            }
        };

        ////////////////////////////////////////////////////////////////////////////
        // Inserter

        template<class Ch, class T>
        struct inserter
        {
            inline bool operator()(std::basic_string<Ch> &data, 
                                   const T &to_insert,
                                   const std::locale &loc) const
            {
                typedef typename detail::array_to_pointer_decay<T>::type T2;
                std::basic_ostringstream<Ch> stream;
                stream.imbue(loc);
                if (std::numeric_limits<T2>::is_specialized
                    && !std::numeric_limits<T2>::is_exact)
                    stream.precision(std::numeric_limits<T2>::digits10 + 1);
                stream << std::boolalpha << to_insert;
                data = stream.str();
                return !stream.fail() && !stream.bad();
            }
        };

        template<class Ch>
        struct inserter<Ch, signed char>
        {
            inline bool operator()(std::basic_string<Ch> &data, 
                                   const signed char &to_insert,
                                   const std::locale &loc) const
            {
                return detail::inserter<Ch, int>()(data, static_cast<int>(to_insert), loc);
            }
        };

        template<class Ch>
        struct inserter<Ch, unsigned char>
        {
            inline bool operator()(std::basic_string<Ch> &data, 
                                   const unsigned char &to_insert,
                                   const std::locale &loc) const
            {
                return detail::inserter<Ch, unsigned int>()(data, static_cast<unsigned int>(to_insert), loc);
            }
        };

        template<class Ch>
        struct inserter<Ch, std::basic_string<Ch> >
        {
            inline bool operator()(std::basic_string<Ch> &data, 
                                   const std::basic_string<Ch> &to_insert,
                                   const std::locale &loc) const
            {
                data = to_insert;
                return true;
            }
        };

    }

    inline translator::translator()
    {
    }

    inline translator::translator(const std::locale &loc):
        m_locale(loc)
    {
    }

    template<class Ptree, class T> 
    bool translator::get_value(const Ptree &pt, T &value) const
    {
        typedef typename Ptree::data_type::value_type Ch;
        return detail::extractor<Ch, T>()(pt.data(), value, m_locale);
    }

    template<class Ptree, class T> 
    bool translator::put_value(Ptree &pt, const T &value) const
    {

        typedef typename Ptree::data_type::value_type Ch;

        // Make sure that no pointer other than char_type * is allowed
        BOOST_STATIC_ASSERT((is_pointer<T>::value == false ||
                             is_same<Ch, typename remove_const<typename remove_pointer<T>::type>::type>::value == true));

        return detail::inserter<Ch, T>()(pt.data(), value, m_locale);

    }

} }

#endif
