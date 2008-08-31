//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_274DA366004E11DCB1DDFE2E56D89593
#define UUID_274DA366004E11DCB1DDFE2E56D89593

namespace
boost
    {

    ////////////////////////////////////////////////////////////////////////

    namespace
    exception_detail
        {
        template <class T>
        class
        refcount_ptr
            {
            public:

            refcount_ptr():
                px_(0)
                {
                }

            ~refcount_ptr()
                {
                release();
                }

            refcount_ptr( refcount_ptr const & x ):
                px_(x.px_)
                {
                add_ref();
                }

            refcount_ptr &
            operator=( refcount_ptr const & x )
                {
                adopt(x.px_);
                return *this;
                }

            void
            adopt( T * px )
                {
                release();
                px_=px;
                add_ref();
                }

            T *
            get() const
                {
                return px_;
                }

            private:

            T * px_;

            void
            add_ref()
                {
                if( px_ )
                    intrusive_ptr_add_ref(px_);
                }

            void
            release()
                {
                if( px_ )
                    intrusive_ptr_release(px_);
                }
            };
        }

    ////////////////////////////////////////////////////////////////////////

    namespace
    exception_detail
        {
        class
        counted_base
            {
            friend
            void
            intrusive_ptr_add_ref( counted_base const * c )
                {
                c->add_ref();
                }

            friend
            void
            intrusive_ptr_release( counted_base const * c )
                {
                c->release();
                }

            virtual void add_ref() const=0;
            virtual void release() const=0;

            protected:

            virtual
            ~counted_base() throw()
                {
                }
            };
        }

    ////////////////////////////////////////////////////////////////////////

    class exception;

    template <class>
    class shared_ptr;

    namespace
    exception_detail
        {
        class error_info_base;
        struct type_info_;

        struct
        error_info_container:
            public exception_detail::counted_base
            {
            virtual char const * diagnostic_information() const = 0;
            virtual shared_ptr<error_info_base const> get( type_info_ const & ) const = 0;
            virtual void set( shared_ptr<error_info_base const> const &, type_info_ const & ) = 0;
            };

        template <class ErrorInfo>
        shared_ptr<typename ErrorInfo::value_type const> get_data( exception const & );

        void set_data( exception const *, shared_ptr<exception_detail::error_info_base const> const &, type_info_ const & );
        }

    class
    exception
        {
        public:

        virtual
        char const *
        diagnostic_information() const throw()
            {
            return _diagnostic_information();
            }

        protected:

        exception()
            {
            }

        virtual ~exception() throw()=0;

        char const *
        _diagnostic_information() const throw()
            {
            if( exception_detail::error_info_container * c=data_.get() )
                try
                    {
                    if( char const * w = c->diagnostic_information() )
                        return w;
                    }
                catch(...)
                    {
                    }
            return "";
            }

        private:

        template <class ErrorInfo>
        friend shared_ptr<typename ErrorInfo::value_type const> exception_detail::get_data( exception const & );

        friend void exception_detail::set_data( exception const *, shared_ptr<exception_detail::error_info_base const> const &, exception_detail::type_info_ const & );

        mutable exception_detail::refcount_ptr<exception_detail::error_info_container> data_;
        };

    inline
    exception::
    ~exception() throw()
        {
        }

    ////////////////////////////////////////////////////////////////////////

    namespace
    exception_detail
        {
        template <class T>
        struct
        error_info_injector:
            public T,
            public exception
            {
            explicit
            error_info_injector( T const & x ):
                T(x)
                {
                }

            ~error_info_injector() throw()
                {
                }
            };

        struct large_size { char c[256]; };
        large_size dispatch( exception * );

        struct small_size { };
        small_size dispatch( void * );

        template <class,int>
        struct enable_error_info_helper;

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(large_size)>
            {
            typedef T type;
            };

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(small_size)>
            {
            typedef error_info_injector<T> type;
            };

        template <class T>
        struct
        enable_error_info_return_type
            {
            typedef typename enable_error_info_helper<T,sizeof(dispatch((T*)0))>::type type;
            };
        }

    template <class T>
    inline
    typename
    exception_detail::enable_error_info_return_type<T>::type
    enable_error_info( T const & x )
        {
        return typename exception_detail::enable_error_info_return_type<T>::type(x);
        }

    ////////////////////////////////////////////////////////////////////////

    namespace
    exception_detail
        {
        class
        clone_base
            {
            public:

            virtual clone_base const * clone() const = 0;
            virtual void rethrow() const = 0;
            virtual ~clone_base() throw() = 0;
            };

        inline
        clone_base::
        ~clone_base() throw()
            {
            }

        inline
        void
        copy_boost_exception( exception * a, exception const * b )
            {
            *a = *b;
            }

        inline
        void
        copy_boost_exception( void *, void const * )
            {
            }

        template <class T>
        class
        clone_impl:
            public T,
            public clone_base
            {
            public:

            explicit
            clone_impl( T const & x ):
                T(x)
                {
                copy_boost_exception(this,&x);
                }

            ~clone_impl() throw()
                {
                }

            private:

            clone_base const *
            clone() const
                {
                return new clone_impl(*this);
                }

            void
            rethrow() const
                {
                throw *this;
                }
            };
        }

    template <class T>
    inline
    exception_detail::clone_impl<T>
    enable_current_exception( T const & x )
        {
        return exception_detail::clone_impl<T>(x);
        }

    ////////////////////////////////////////////////////////////////////////

    }

#endif
