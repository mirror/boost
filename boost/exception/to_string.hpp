//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_7E48761AD92811DC9011477D56D89593
#define UUID_7E48761AD92811DC9011477D56D89593

#include <boost/utility/enable_if.hpp>
#include <boost/exception/detail/is_output_streamable.hpp>
#include <sstream>

namespace
boost
    {
	namespace
	exception_detail
		{
		template <bool>
		struct
		has_to_string_dispatch
			{
			enum e { value=1 };
			};

		template <>
		struct
		has_to_string_dispatch<false>
			{
			enum e { value=0 };
			};

		template <class T>
		std::string
		to_string( T const & x, typename enable_if< is_output_streamable<T> >::type * = 0 )
			{
			std::ostringstream out;
			out << x;
			return out.str();
			}

        template <class T>
        char to_string( T const &, typename disable_if< is_output_streamable<T> >::type * = 0 );

		template <class T>
        struct
		has_to_string_impl
			{
			enum e { value=has_to_string_dispatch<1!=sizeof(to_string(*(T*)0))>::value };
			};
		}

	template <class T>
    struct
	has_to_string
		{
		enum e { value=exception_detail::has_to_string_impl<T>::value };
		};

	template <class T>
    std::string
	to_string( T const & x, typename enable_if< is_output_streamable<T> >::type * = 0 )
        {
		return exception_detail::to_string(x);
        }
    }

#endif
