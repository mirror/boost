// Copyright David Abrahams 2003. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/static_assert.hpp>
#include "static_assert_same.hpp"
#include <boost/type_traits/broken_compiler_spec.hpp>


struct X { int a; };

BOOST_TT_BROKEN_COMPILER_SPEC(X)

struct Xiter : boost::iterator_adaptor<Xiter,X*>
{
    Xiter();
    Xiter(X* p) : boost::iterator_adaptor<Xiter, X*>(p) {}
};

void take_xptr(X*) {}
void operator_arrow_test()
{
    // check that the operator-> result is a pointer for lvalue iterators
    X x;
    take_xptr(Xiter(&x).operator->());
}

template <class T, class U, class Min>
struct static_assert_min_cat
  : static_assert_same<
       typename boost::detail::minimum_category<T,U>::type, Min
    >
{};

void category_test()
{
    using namespace boost;
    using namespace boost::detail;
    
    BOOST_STATIC_ASSERT((
        !is_tag<
            input_output_iterator_tag
          , std::input_iterator_tag>::value));
    
    BOOST_STATIC_ASSERT((
        !is_tag<
            input_output_iterator_tag
          , std::output_iterator_tag>::value));
    
    BOOST_STATIC_ASSERT((
        is_tag<
            std::input_iterator_tag
          , input_output_iterator_tag>::value));
    
    BOOST_STATIC_ASSERT((
        is_tag<
            std::output_iterator_tag
          , input_output_iterator_tag>::value));

    BOOST_STATIC_ASSERT((
        is_tag<
            input_output_iterator_tag
          , std::forward_iterator_tag>::value));

    int test = static_assert_min_cat<
        std::input_iterator_tag,input_output_iterator_tag, std::input_iterator_tag
    >::value;

    test = static_assert_min_cat<
        input_output_iterator_tag,std::input_iterator_tag, std::input_iterator_tag
    >::value;

    test = static_assert_min_cat<
        input_output_iterator_tag,std::forward_iterator_tag, input_output_iterator_tag
    >::value;

    test = static_assert_min_cat<
        std::input_iterator_tag,std::forward_iterator_tag, std::input_iterator_tag
    >::value;

    test = static_assert_min_cat<
        std::input_iterator_tag,std::random_access_iterator_tag, std::input_iterator_tag
    >::value;

    test = static_assert_min_cat<
        std::output_iterator_tag,std::random_access_iterator_tag, std::output_iterator_tag
    >::value;
    
    BOOST_STATIC_ASSERT((is_traversal_tag< incrementable_traversal_tag >::value));
    BOOST_STATIC_ASSERT((is_traversal_tag< single_pass_traversal_tag   >::value));
    BOOST_STATIC_ASSERT((is_traversal_tag< forward_traversal_tag       >::value));
    BOOST_STATIC_ASSERT((is_traversal_tag< bidirectional_traversal_tag >::value));
    BOOST_STATIC_ASSERT((is_traversal_tag< random_access_traversal_tag >::value));

    BOOST_STATIC_ASSERT((!is_traversal_tag< std::input_iterator_tag >::value));
    BOOST_STATIC_ASSERT((!is_traversal_tag< readable_iterator_tag   >::value));

    BOOST_STATIC_ASSERT((is_access_tag< readable_iterator_tag          >::value));
    BOOST_STATIC_ASSERT((is_access_tag< writable_iterator_tag          >::value));
    BOOST_STATIC_ASSERT((is_access_tag< swappable_iterator_tag         >::value));
    BOOST_STATIC_ASSERT((is_access_tag< readable_writable_iterator_tag >::value));
    BOOST_STATIC_ASSERT((is_access_tag< readable_lvalue_iterator_tag   >::value));
    BOOST_STATIC_ASSERT((is_access_tag< writable_lvalue_iterator_tag   >::value));

    BOOST_STATIC_ASSERT((!is_access_tag< std::input_iterator_tag     >::value));
    BOOST_STATIC_ASSERT((!is_access_tag< incrementable_traversal_tag >::value));

    (void)test;
}

int main()
{
    category_test();
    operator_arrow_test();
    return 0;
}

