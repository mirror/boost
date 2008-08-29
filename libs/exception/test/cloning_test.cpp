//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/exception_ptr.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/exception/info.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>

typedef boost::error_info<struct my_tag,int> my_info;

struct
derives_nothing
    {
    int & count;

    explicit
    derives_nothing( int & count ):
        count(count)
        {
        ++count;
        }

    derives_nothing( derives_nothing const & x ):
        count(x.count)
        {
        ++count;
        }

    ~derives_nothing()
        {
        --count;
        }
    };

struct
derives_std_exception:
    std::exception
    {
    };

struct
derives_std_boost_exception:
    std::exception,
    boost::exception
    {
    };

struct
derives_boost_exception:
    boost::exception
    {
    };

template <class T>
void
test_std_exception()
    {
    try
        {
        throw T();
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        T & )
            {
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }
    }

template <class T>
void
test_std_exception_what()
    {
    try
        {
        throw T("what");
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        T & x )
            {
            BOOST_TEST(std::string("what")==x.what());
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }
    }

int
main()
    {
    int count=0;
    try
        {
        throw boost::enable_current_exception(derives_nothing(count));
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        derives_nothing & )
            {
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }
    BOOST_TEST(count==0);

    try
        {
        throw boost::enable_current_exception(derives_std_exception());
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        derives_std_exception & )
            {
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }

    try
        {
        throw derives_std_exception();
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        boost::unknown_exception & )
            {
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }

    test_std_exception_what<std::invalid_argument>();
    test_std_exception_what<std::out_of_range>();
    test_std_exception_what<std::logic_error>();
    test_std_exception<std::bad_alloc>();
    test_std_exception<std::bad_cast>();
    test_std_exception<std::bad_typeid>();
    test_std_exception<std::bad_exception>();

    try
        {
        throw derives_std_boost_exception() << my_info(42);
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        boost::unknown_exception & x )
            {
            BOOST_TEST(boost::get_error_info<my_info>(x));
            if( boost::shared_ptr<int const> p=boost::get_error_info<my_info>(x) )
                BOOST_TEST(*p==42);
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }

    try
        {
        throw derives_boost_exception() << my_info(42);
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        boost::unknown_exception & x )
            {
            BOOST_TEST(boost::get_error_info<my_info>(x));
            if( boost::shared_ptr<int const> p=boost::get_error_info<my_info>(x) )
                BOOST_TEST(*p==42);
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }

    return boost::report_errors();
    }
