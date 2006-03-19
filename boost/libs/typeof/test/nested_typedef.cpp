#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


void do_int(int) {}

struct {
    template<typename T>
    T operator[](const T&) {}
} int_p;


template<typename T> struct wrap
{
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,int_p[& do_int])
    typedef typename nested::type type;
};

BOOST_TYPEOF_REGISTER_TEMPLATE(wrap,1)

template<typename T> struct parser
{
    struct __rule {
        static T & a_placeholder;
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,int_p[a_placeholder])
        typedef typename nested::type type;
    };
};

BOOST_STATIC_ASSERT((boost::is_same<wrap<double>::type,void(*)(int)>::value));
BOOST_STATIC_ASSERT((boost::is_same<parser<wrap<double> >::__rule::type,wrap<double> >::value));
