//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_FA5836A2CADA11DC8CD47C8555D89593
#define UUID_FA5836A2CADA11DC8CD47C8555D89593

#include <boost/exception/exception.hpp>
#include <boost/exception/detail/type_info.hpp>
#include <boost/detail/atomic_count.hpp>
#include <boost/intrusive_ptr.hpp>
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
            set( clone_base const * c )
                {
                clone_ = c;
                BOOST_ASSERT(clone_!=0);
                }

            void
            rethrow() const
                {
                if( clone_ )
                    clone_->rethrow();
                else
                    throw enable_current_exception(std::bad_alloc());
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
                    delete clone_;
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

        struct
        bad_alloc_tag
            {
            };

        struct
        bad_exception_tag
            {
            };
        }

    class exception_ptr;
    void rethrow_exception( exception_ptr const & );

    class
    exception_ptr
        {
        private:

        friend void rethrow_exception( exception_ptr const & );

        enum
            {
            bad_alloc_caught,
            clone_failed,
            ok
            } what_happened_;

        intrusive_ptr<exception_detail::counted_clone> c_;

        void
        rethrow() const
            {
            switch(
            what_happened_ )
                {
                case
                bad_alloc_caught:
                    throw enable_current_exception(std::bad_alloc());
                case
                clone_failed:
                    throw enable_current_exception(std::bad_exception());
                case
                ok:
                    BOOST_ASSERT(c_.get()!=0);
                    c_->rethrow();
                }
            BOOST_ASSERT(0);
            }

        typedef intrusive_ptr<exception_detail::counted_clone> exception_ptr::*unspecified_bool_type;

        public:

        explicit
        exception_ptr( exception_detail::bad_alloc_tag ):
            what_happened_(bad_alloc_caught)
            {
            }

        explicit
        exception_ptr( exception_detail::bad_exception_tag ):
            what_happened_(clone_failed)
            {
            }

        exception_ptr():
            what_happened_(ok)
            {
            }

        explicit
        exception_ptr( intrusive_ptr<exception_detail::counted_clone> const & c ):
            what_happened_(ok),
            c_(c)
            {
            BOOST_ASSERT(c_.get()!=0);
            }

        friend
        bool
        operator==( exception_ptr const & a, exception_ptr const & b )
            {
            return
                a.what_happened_==ok &&
                b.what_happened_==ok &&
                a.c_==b.c_;
            }

        friend
        bool
        operator!=( exception_ptr const & a, exception_ptr const & b )
            {
            return !(a==b);
            }

        operator unspecified_bool_type() const
            {
            return (what_happened_!=ok || c_) ? &exception_ptr::c_ : 0;
            }
        };

    class
    unknown_exception:
        public exception,
        public std::exception,
        public exception_detail::clone_base
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

        private:

        clone_base const *
        clone() const
            {
            return new unknown_exception(*this);
            }

        void
        rethrow() const
            {
            throw *this;
            }
        };

    namespace
    exception_detail
        {
        template <class T>
        class
        current_exception_std_exception_wrapper:
            public T,
            public boost::exception,
            public clone_base
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

            private:

            clone_base const *
            clone() const
                {
                return new current_exception_std_exception_wrapper(*this);
                }

            void
            rethrow() const
                {
                throw *this;
                }
            };

#ifdef BOOST_NO_RTTI
        template <class T>
        exception const *
        get_boost_exception( T const * )
            {
            try
                {
                throw;
                }
            catch(
            exception & x )
                {
                return &x;
                }
            catch(...)
                {
                return 0;
                }
            }
#else
        template <class T>
        exception const *
        get_boost_exception( T const * x )
            {
            return dynamic_cast<exception const *>(x);
            }
#endif

        template <class T>
        inline
        exception_ptr
        current_exception_std_exception( T const & e1 )
            {
            intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
            if( boost::exception const * e2 = get_boost_exception(&e1) )
                x->set(new current_exception_std_exception_wrapper<T>(e1,*e2));
            else
                x->set(new current_exception_std_exception_wrapper<T>(e1));
            return exception_ptr(x);
            }

        inline
        exception_ptr
        current_exception_unknown_exception()
            {
            intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
            x->set(new unknown_exception());
            return exception_ptr(x);
            }

        inline
        exception_ptr
        current_exception_unknown_std_exception( std::exception const & e )
            {
            if( boost::exception const * be = get_boost_exception(&e) )
                {
                intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
                x->set(new unknown_exception(*be));
                return exception_ptr(x);
                }
            else
                return current_exception_unknown_exception();
            }

        inline
        exception_ptr
        current_exception_unknown_boost_exception( boost::exception const & e )
            {
            intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
            x->set(new unknown_exception(e));
            return exception_ptr(x);
            }
        }

    inline
    exception_ptr
    current_exception()
        {
        try
            {
            try
                {
                throw;
                }
            catch(
            exception_detail::clone_base & e )
                {
                intrusive_ptr<exception_detail::counted_clone> x(new exception_detail::counted_clone);
                x->set(e.clone());
                return exception_ptr(x);
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
#ifndef BOOST_NO_TYPEID
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
#endif
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
        catch(
        std::bad_alloc & )
            {
            return exception_ptr( exception_detail::bad_alloc_tag() );
            }
        catch(
        ... )
            {
            return exception_ptr( exception_detail::bad_exception_tag() );
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
        p.rethrow();
        }
    }

#endif
