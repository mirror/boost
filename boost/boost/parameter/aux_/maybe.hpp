// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_MAYBE_060211_HPP
# define BOOST_PARAMETER_MAYBE_060211_HPP

# include <boost/mpl/if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/type_traits/is_reference.hpp>
# include <boost/type_traits/add_reference.hpp>
# include <boost/type_traits/add_const.hpp>
# include <boost/optional.hpp>
# include <boost/python/detail/referent_storage.hpp>

namespace boost { namespace parameter { namespace aux {

struct maybe_base {};

template <class T>
struct maybe : maybe_base
{
    typedef typename mpl::if_<
        is_reference<T>
      , T
      , typename add_reference<
            typename add_const<T>::type
        >::type
    >::type reference;

    explicit maybe(T value)
      : value(value)
      , constructed(false)
    {}

    maybe()
      : constructed(false)
    {}

    ~maybe()
    {
        if (constructed)
            destroy((void(*)(reference))0);
    }

    reference construct(reference value) const
    {
        return value;
    }

    template <class U, class V>
    reference construct(U const& value, void(*)(V&)) const
    {
        new (m_storage.bytes) V(value);
        constructed = true;
        return *(V*)m_storage.bytes;
    }

    template <class U>
    reference construct(U const& value) const
    {
        return construct(value, (void(*)(reference))0);
    }

    template <class U>
    void destroy(void(*)(U&))
    {
        ((U*)m_storage.bytes)->~U();
    }

    typedef reference(maybe<T>::*safe_bool)() const;

    operator safe_bool() const
    {
        return value ? &maybe<T>::get : 0 ;
    }

    reference get() const
    {
        return value.get();
    }

private:
    boost::optional<T> value;
    mutable bool constructed;
    mutable typename boost::python::detail::referent_storage<
        reference
    >::type m_storage;
};

}}} // namespace boost::parameter::aux

#endif // BOOST_PARAMETER_MAYBE_060211_HPP

