//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_E788439ED9F011DCB181F25B55D89593
#define UUID_E788439ED9F011DCB181F25B55D89593

#include <boost/exception/to_string.hpp>
#include <iomanip>
#include <typeinfo>

namespace
boost
	{
	namespace
	exception_detail
		{
		template <bool ShiftLeftAvailable>
		struct shift_left_dispatcher;

		template <>
		struct
		shift_left_dispatcher<true>
			{
			template <class T,class CharT,class Traits,class Stub>
			static
			void
			convert( std::basic_ostream<CharT,Traits> & out, T const & x, Stub )
				{
				out << x;
				}
			};

		template <>
		struct
		shift_left_dispatcher<false>
			{
			template <class T,class CharT,class Traits,class Stub>
			static
			void
			convert( std::basic_ostream<CharT,Traits> & out, T const & x, Stub s )
				{
				out << s(x);
				}
			};

		namespace
		shift_left_dispatch
			{
			template <class T,class CharT,class Traits>
			char operator<<( std::basic_ostream<CharT,Traits> &, T );

			template <class T,class CharT,class Traits,class Stub>
			void
			dispatch( std::basic_ostream<CharT,Traits> & out, T const & x, Stub s )
				{
				shift_left_dispatcher<1!=sizeof(out<<x)>::convert(out,x,s);
				}
			}
		}

	namespace
	exception_detail
		{
		template <bool ToStringAvailable>
		struct to_string_dispatcher;

		template <>
		struct
		to_string_dispatcher<true>
			{
			template <class T,class Stub>
			static
			std::string
			convert( T const & x, Stub )
				{
				return to_string(x);
				}
			};

		template <>
		struct
		to_string_dispatcher<false>
			{
			template <class T,class Stub>
			static
			std::string
			convert( T const & x, Stub s )
				{
				std::ostringstream out;
				shift_left_dispatch::dispatch(out,x,s);
				return out.str();
				}
			};

		namespace
		to_string_dispatch
			{
			template <class T>
			char to_string( T );

			template <class T,class Stub>
			std::string
			dispatch( T const & x, Stub s )
				{
				return to_string_dispatcher<1!=sizeof(to_string(x))>::convert(x,s);
				}
			}

		template <class T>
		std::string
		string_stub_dump( T const & x )
			{
			std::ostringstream s;
			s << "[ type: " << typeid(x).name() << ", size: " << sizeof(T) << ", dump: ";
			size_t n=sizeof(T)>16?16:sizeof(T);
			s.fill('0');
			s.width(2);
			for( unsigned char const * b=reinterpret_cast<unsigned char const *>(&x),* e=b+n; b!=e; ++b )
				s << std::setw(2) << std::hex << (unsigned int)*b << " ";
			s << "]";
			return s.str();
			}
		}

	template <class T>
	std::string
	to_string_stub( T const & x )
		{
		return exception_detail::to_string_dispatch::dispatch(x,&exception_detail::string_stub_dump<T>);
		}

	template <class T,class Stub>
	std::string
	to_string_stub( T const & x, Stub s )
		{
		return exception_detail::to_string_dispatch::dispatch(x,s);
		}

	template <class T,class U>
	std::string
	to_string( std::pair<T,U> const & x )
		{
		return std::string("(") + to_string(x.first) + ',' + to_string(x.second) + ')';
		}
	}

#endif
