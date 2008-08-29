//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_FA5836A2CADA11DC8CD47C8555D89593
#define UUID_FA5836A2CADA11DC8CD47C8555D89593

#include <boost/exception/enable_current_exception.hpp>
#include <boost/exception/detail/get_boost_exception.hpp>
#include <boost/detail/atomic_count.hpp>
#include <stdexcept>
#include <new>

namespace
boost
    {
    namespace
    exception_detail
        {
        class
        counted_clone:
            public counted_base
            {
            public:

            counted_clone():
                count_(0),
                clone_(0)
                {
                }

            void
            set( new_clone const & nc )
                {
                clone_ = nc.c_;
                clone_deleter_ = nc.d_;
                BOOST_ASSERT(clone_!=0);
                BOOST_ASSERT(clone_deleter_!=0);
                }

            void
            rethrow() const
                {
                BOOST_ASSERT(clone_!=0);
                clone_->rethrow();
                }

            private:

            counted_clone( counted_clone const & );
            counted_clone & operator=( counted_clone const & );

            mutable detail::atomic_count count_;
            clone_base const * clone_;
            void (*clone_deleter_)(clone_base const *);

            ~counted_clone() throw()
                {
                if( clone_ )
                    clone_deleter_(clone_);
                }

            void
            add_ref() const
                {
                ++count_;
                }

            void
            release() const
                {
                if( !--count_ )
                    delete this;
                }
            };
        }

    typedef intrusive_ptr<exception_detail::counted_clone const> exception_ptr;

    class
    unknown_exception:
        public exception,
        public std::exception
        {
        public:

        unknown_exception()
            {
            }

        explicit
        unknown_exception( boost::exception const & e ):
            boost::exception(e)
            {
            }

        ~unknown_exception() throw()
            {
            }
        };

    namespace
    exception_detail
        {
        template <class T>
        class
        current_exception_std_exception_wrapper:
            public T,
            public boost::exception
            {
            public:

            explicit
            current_exception_std_exception_wrapper( T const & e1 ):
                T(e1)
                {
                }

            current_exception_std_exception_wrapper( T const & e1, boost::exception const & e2 ):
                T(e1),
                boost::exception(e2)
                {
                }

            ~current_exception_std_exception_wrapper() throw()
                {
                }
            };

        template <class T>
        inline
        exception_ptr
        current_exception_std_exception( T const & e1 )
            {
            intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
            if( boost::exception const * e2 = get_boost_exception(&e1) )
                x->set(exception_detail::make_clone(current_exception_std_exception_wrapper<T>(e1,*e2)));
            else
                x->set(exception_detail::make_clone(current_exception_std_exception_wrapper<T>(e1)));
            return x;
            }

        inline
        exception_ptr
        current_exception_unknown_exception()
            {
            intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
            x->set(exception_detail::make_clone(unknown_exception()));
            return x;
            }

        inline
        exception_ptr
        current_exception_unknown_std_exception( std::exception const & e )
            {
            if( boost::exception const * be = get_boost_exception(&e) )
                {
                intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
                x->set(exception_detail::make_clone(unknown_exception(*be)));
                return x;
                }
            else
                return current_exception_unknown_exception();
            }

        inline
        exception_ptr
        current_exception_unknown_boost_exception( boost::exception const & e )
            {
            intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
            x->set(exception_detail::make_clone(unknown_exception(e)));
            return x;
            }
        }

    inline
    exception_ptr
    current_exception()
        {
        try
            {
            throw;
            }
        catch(
        exception_detail::cloning_base & e )
            {
            intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
            x->set(e.clone());
            return x;
            }
        catch(
        std::invalid_argument & e )
            {
            return exception_detail::current_exception_std_exception(e);
            }
        catch(
        std::out_of_range & e )
            {
            return exception_detail::current_exception_std_exception(e);
            }
        catch(
        std::logic_error & e )
            {
            return exception_detail::current_exception_std_exception(e);
            }
        catch(
        std::bad_alloc & e )
            {
            return exception_detail::current_exception_std_exception(e);
            }
        catch(
        std::bad_cast & e )
            {
            return exception_detail::current_exception_std_exception(e);
            }
        catch(
        std::bad_typeid & e )
            {
            return exception_detail::current_exception_std_exception(e);
            }
        catch(
        std::bad_exception & e )
            {
            return exception_detail::current_exception_std_exception(e);
            }
        catch(
        std::exception & e )
            {
            return exception_detail::current_exception_unknown_std_exception(e);
            }
        catch(
        boost::exception & e )
            {
            return exception_detail::current_exception_unknown_boost_exception(e);
            }
        catch(
        ... )
            {
            return exception_detail::current_exception_unknown_exception();
            }
        }

    template <class T>
    inline
    exception_ptr
    copy_exception( T const & e )
        {
        try
            {
            throw enable_current_exception(e);
            }
        catch( ... )
            {
            return current_exception();
            }
        }

    inline
    void
    rethrow_exception( exception_ptr const & p )
        {
        p->rethrow();
        }
    }

#endif
