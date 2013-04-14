// See http://www.boost.org/libs/any for Documentation.

#ifndef BOOST_ANY_INCLUDED
#define BOOST_ANY_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// what:  variant type boost::any
// who:   contributed by Kevlin Henney,
//        with features contributed and bugs found by
//        Antony Polukhin, Ed Brey, Mark Rodgers, 
//        Peter Dimov, and James Curran
// when:  July 2001, Aplril 2013

#include <algorithm>
#include <typeinfo>

#include "boost/config.hpp"
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/throw_exception.hpp>
#include <boost/static_assert.hpp>
#include <boost/move/move.hpp>

// See boost/python/type_id.hpp
// TODO: add BOOST_TYPEID_COMPARE_BY_NAME to config.hpp
# if (defined(__GNUC__) && __GNUC__ >= 3) \
 || defined(_AIX) \
 || (   defined(__sgi) && defined(__host_mips)) \
 || (defined(__hpux) && defined(__HP_aCC)) \
 || (defined(linux) && defined(__INTEL_COMPILER) && defined(__ICC))
#  define BOOST_AUX_ANY_TYPE_ID_NAME
#include <cstring>
# endif 

#ifdef BOOST_MSVC
#pragma warning (push)
#pragma warning (disable : 4521 ) // multiple copy constructors specified
#pragma warning (disable : 4522 ) // multiple assignment operators specified
#endif

namespace boost
{
    class any
    {
    private:
        // Mark this class copyable and movable
        BOOST_COPYABLE_AND_MOVABLE(any)
    public: // structors

        any() BOOST_NOEXCEPT
          : content(0)
        {
        }
        
        any(const any & other)
          : content(other.content ? other.content->clone() : 0)
        {
        }

        //Move constructor
        any(BOOST_RV_REF(any) other) BOOST_NOEXCEPT
          : content(other.content)
        {
            other.content = 0;
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        any(any & other)
          : content(other.content ? other.content->clone() : 0)
        {
        }

        template<typename ValueType>
        any(ValueType&& value)
          : content(new holder< BOOST_DEDUCED_TYPENAME remove_reference<ValueType>::type >(
                ::boost::forward<ValueType>(value)
          ))
        {
        }
#else
        any(const ::boost::rv<any>& other)
          : content(other.content ? other.content->clone() : 0)
        {
        }

        template<typename ValueType>
        any(const ValueType & value)
          : content(new holder<ValueType>(value))
        {
            BOOST_STATIC_ASSERT_MSG(!boost::move_detail::is_rv<ValueType>::value,
                "You compiler can not deal with emulated move semantics."
                "Please remove moves of non boost::any types to boost::any container."
            );
        }
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        template<typename ValueType>
        any(const ::boost::rv<ValueType> & value)
          : content(new holder<ValueType>(value))
        {
        }

        template<typename ValueType>
        any(::boost::rv<ValueType> & value)
          : content(new holder<ValueType>(value))
        {
        }
#endif
#endif // BOOST_NO_CXX11_RVALUE_REFERENCES

        ~any()
        {
            delete content;
        }

    public: // modifiers

        any & swap(any & rhs) BOOST_NOEXCEPT
        {
            std::swap(content, rhs.content);
            return *this;
        }
        
        any & operator=(BOOST_COPY_ASSIGN_REF(any) rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

        any & operator=(BOOST_RV_REF(any) rhs) BOOST_NOEXCEPT
        {
            rhs.swap(*this); // noexcept
            any().swap(rhs); // noexcept
            return *this;
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        any & operator=(any& rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

        template<typename ValueType>
        any & operator=(ValueType&& rhs)
        {
            any( ::boost::forward<ValueType>(rhs) )
                .swap(*this);
            return *this;
        }
#else 
        template<typename ValueType>
        any & operator=(const ValueType & rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

        template<typename ValueType>
        any & operator=(ValueType & rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    public: // queries

        bool empty() const BOOST_NOEXCEPT
        {
            return !content;
        }

        const std::type_info & type() const
        {
            return content ? content->type() : typeid(void);
        }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    private: // types
#else
    public: // types (public so any_cast can be non-friend)
#endif

        class placeholder
        {
        public: // structors

            virtual ~placeholder()
            {
            }

        public: // queries

            virtual const std::type_info & type() const = 0;

            virtual placeholder * clone() const = 0;

        };

        template<typename ValueType>
        class holder : public placeholder
        {
        public: // structors

            holder(const ValueType & value)
              : held(value)
            {
            }

            holder(BOOST_RV_REF(ValueType) value)
              : held( boost::move(value) )
            {
            }
        public: // queries

            virtual const std::type_info & type() const
            {
                return typeid(ValueType);
            }

            virtual placeholder * clone() const
            {
                return new holder(held);
            }

        public: // representation

            ValueType held;

        private: // intentionally left unimplemented
            holder & operator=(const holder &);
        };

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

    private: // representation

        template<typename ValueType>
        friend ValueType * any_cast(any *) BOOST_NOEXCEPT;

        template<typename ValueType>
        friend ValueType * unsafe_any_cast(any *);

#else

    public: // representation (public so any_cast can be non-friend)

#endif

        placeholder * content;

    };

    inline void swap(any & lhs, any & rhs) BOOST_NOEXCEPT
    {
        lhs.swap(rhs);
    }

    class bad_any_cast : public std::bad_cast
    {
    public:
        virtual const char * what() const throw()
        {
            return "boost::bad_any_cast: "
                   "failed conversion using boost::any_cast";
        }
    };

    template<typename ValueType>
    ValueType * any_cast(any * operand) BOOST_NOEXCEPT
    {
        return operand && 
#ifdef BOOST_AUX_ANY_TYPE_ID_NAME
            std::strcmp(operand->type().name(), typeid(ValueType).name()) == 0
#else
            operand->type() == typeid(ValueType)
#endif
            ? &static_cast<any::holder<ValueType> *>(operand->content)->held
            : 0;
    }

    template<typename ValueType>
    inline const ValueType * any_cast(const any * operand) BOOST_NOEXCEPT
    {
        return any_cast<ValueType>(const_cast<any *>(operand));
    }

    template<typename ValueType>
    ValueType any_cast(any & operand)
    {
        typedef BOOST_DEDUCED_TYPENAME remove_reference<ValueType>::type nonref;

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        // If 'nonref' is still reference type, it means the user has not
        // specialized 'remove_reference'.

        // Please use BOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION macro
        // to generate specialization of remove_reference for your class
        // See type traits library documentation for details
        BOOST_STATIC_ASSERT(!is_reference<nonref>::value);
#endif

        nonref * result = any_cast<nonref>(&operand);
        if(!result)
            boost::throw_exception(bad_any_cast());
        return *result;
    }

    template<typename ValueType>
    inline ValueType any_cast(const any & operand)
    {
        typedef BOOST_DEDUCED_TYPENAME remove_reference<ValueType>::type nonref;

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        // The comment in the above version of 'any_cast' explains when this
        // assert is fired and what to do.
        BOOST_STATIC_ASSERT(!is_reference<nonref>::value);
#endif

        return any_cast<const nonref &>(const_cast<any &>(operand));
    }

    // Note: The "unsafe" versions of any_cast are not part of the
    // public interface and may be removed at any time. They are
    // required where we know what type is stored in the any and can't
    // use typeid() comparison, e.g., when our types may travel across
    // different shared libraries.
    template<typename ValueType>
    inline ValueType * unsafe_any_cast(any * operand)
    {
        return &static_cast<any::holder<ValueType> *>(operand->content)->held;
    }

    template<typename ValueType>
    inline const ValueType * unsafe_any_cast(const any * operand)
    {
        return unsafe_any_cast<ValueType>(const_cast<any *>(operand));
    }
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning (pop)
#endif

// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif
