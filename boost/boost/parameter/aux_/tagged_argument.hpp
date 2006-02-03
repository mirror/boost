// Copyright Daniel Wallin, David Abrahams 2005. Use, modification and
// distribution is subject to the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAGGED_ARGUMENT_050328_HPP
#define TAGGED_ARGUMENT_050328_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/parameter/aux_/result_of0.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace parameter { namespace aux {

struct empty_arg_list;
struct arg_list_tag;

// Holds a reference to an argument of type Arg associated with
// keyword Keyword
    
template <class Keyword, class Arg>
struct tagged_argument
{
    typedef Keyword key_type;
    typedef Arg value_type;
    typedef Arg& reference;

    tagged_argument(reference x) : value(x) {}

    // A metafunction class that, given a keyword and a default
    // type, returns the appropriate result type for a keyword
    // lookup given that default
    struct binding
    {
        template <class KW, class Default>
        struct apply
        {
          typedef typename mpl::if_<
                boost::is_same<KW, key_type>
              , reference
              , Default
          >::type type;
        };
    };

    // Comma operator to compose argument list without using parameters<>.
    // Useful for argument lists with undetermined length.
    template <class Keyword2, class Arg2>
    arg_list<
        tagged_argument<Keyword, Arg>
      , arg_list<tagged_argument<Keyword2, Arg2> > 
    >
    operator,(tagged_argument<Keyword2, Arg2> x) const
    {
        return arg_list<
            tagged_argument<Keyword, Arg>
          , arg_list<tagged_argument<Keyword2, Arg2> > 
        >(
            *this
          , arg_list<tagged_argument<Keyword2, Arg2> >(x, empty_arg_list())
        );
    }

    reference operator[](keyword<Keyword> const&) const
    {
        return value;
    }

#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template <class KW, class Default>
    Default& get_with_default(default_<KW,Default> const& x, int) const
    {
        return x.value;
    }

    template <class Default>
    reference get_with_default(default_<key_type,Default> const&, long) const
    {
        return value;
    }

    template <class KW, class Default>
    typename mpl::apply_wrap2<binding, KW, Default&>::type
    operator[](default_<KW,Default> const& x) const
    {
        return get_with_default(x, 0L);
    }

    template <class KW, class F>
    typename result_of0<F>::type 
    get_with_lazy_default(lazy_default<KW,F> const& x, int) const
    {
        return x.compute_default();
    }

    template <class F>
    reference get_with_lazy_default(lazy_default<key_type,F> const&, long) const
    {
        return value;
    }

    template <class KW, class F>
    typename mpl::apply_wrap2<
        binding,KW
      , typename result_of0<F>::type
    >::type
    operator[](lazy_default<KW,F> const& x) const
    {
        return get_with_lazy_default(x, 0L);
    }
#else
    template <class Default>
    reference operator[](default_<key_type,Default> const& x) const
    {
        return value;
    }

    template <class F>
    reference operator[](lazy_default<key_type,F> const& x) const
    {
        return value;
    }

    template <class KW, class Default>
    Default& operator[](default_<KW,Default> const& x) const
    {
        return x.value;
    }

    template <class KW, class F>
    typename result_of0<F>::type operator[](lazy_default<KW,F> const& x) const
    {
        return x.compute_default();
    }

    template <class ParameterRequirements>
    static typename ParameterRequirements::has_default
    satisfies(ParameterRequirements*);

    template <class HasDefault, class Predicate>
    static typename mpl::apply1<Predicate, value_type>::type
    satisfies(
        parameter_requirements<key_type,Predicate,HasDefault>*
    );
#endif

    reference value;
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
    // warning suppression
 private:
    void operator=(tagged_argument const&);
 public:    
#endif
    // MPL sequence support
    typedef tagged_argument type;            // Convenience for users
    typedef empty_arg_list tail_type;        // For the benefit of iterators
    typedef arg_list_tag tag; // For dispatching to sequence intrinsics
};

template <class K, class T>
char is_tagged_argument_check(tagged_argument<K,T> const*);
char(&is_tagged_argument_check(...))[2];

// Defines a metafunction, is_tagged_argument, that identifies
// tagged_argument specializations.
// MAINTAINER NOTE: Not using BOOST_DETAIL_IS_XXX_DEF here because
// we need to return true for tagged_argument<K,T> const.
template <class T>
struct is_tagged_argument
{
    BOOST_STATIC_CONSTANT(bool, value =
        sizeof(is_tagged_argument_check((T*)0)) == 1
    );

    typedef mpl::bool_<value> type;
};

}}} // namespace boost::parameter::aux

#endif // TAGGED_ARGUMENT_050328_HPP

