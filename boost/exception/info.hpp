//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_8D22C4CA9CC811DCAA9133D256D89593
#define UUID_8D22C4CA9CC811DCAA9133D256D89593

#include <boost/exception/exception.hpp>
#include <boost/exception/detail/error_info_base.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/to_string_stub.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

#define BOOST_ERROR_INFO\
    ::boost::throw_function(BOOST_CURRENT_FUNCTION) <<\
    ::boost::throw_file(__FILE__) <<\
    ::boost::throw_line((int)__LINE__)

namespace
boost
    {
    typedef error_info<struct tag_throw_function,char const *> throw_function;
    typedef error_info<struct tag_throw_file,char const *> throw_file;
    typedef error_info<struct tag_throw_line,int> throw_line;

    template <class Tag,class T>
    class
    error_info:
        public exception_detail::error_info_base
        {
        public:

        typedef T value_type;

        error_info( value_type const & value ):
            value_(value)
            {
            }

        value_type const &
        value() const
            {
            return value_;
            }

        private:

        char const *
        tag_typeid_name() const
            {
            return exception_detail::type_name<Tag>();
            }

        std::string
        value_as_string() const
            {
            return to_string_stub(value_);
            }

        value_type const value_;
        };

    namespace
    exception_detail
        {
        class
        error_info_container_impl:
            public error_info_container
            {
            public:

            error_info_container_impl():
                count_(0)
                {
                }

            ~error_info_container_impl() throw()
                {
                }

            void
            set( shared_ptr<error_info_base const> const & x, type_info_ const & typeid_ )
                {
                BOOST_ASSERT(x);
                info_[type_info_wrapper(typeid_)] = x;
                what_.clear();
                }

            shared_ptr<error_info_base const>
            get( type_info_ const & ti ) const
                {
                error_info_map::const_iterator i=info_.find(type_info_wrapper(ti));
                if( info_.end()!=i )
                    {
                    shared_ptr<error_info_base const> const & p = i->second;
    #ifndef BOOST_NO_RTTI
                    BOOST_ASSERT( typeid(*p)==ti );
    #endif
                    return p;
                    }
                return shared_ptr<error_info_base const>();
                }

            char const *
            diagnostic_information( char const * std_what, char const * exception_type_name ) const
                {
                BOOST_ASSERT(exception_type_name!=0 && *exception_type_name );
                if( what_.empty() )
                    {
                    std::string tmp;
                    if( std_what )
                        {
                        tmp += std_what;
                        tmp += '\n';
                        }
                    tmp += "Dynamic exception type: ";
                    tmp += exception_type_name;
                    tmp += '\n';
                    for( error_info_map::const_iterator i=info_.begin(),end=info_.end(); i!=end; ++i )
                        {
                        shared_ptr<error_info_base const> const & x = i->second;
                        tmp += '[';
                        tmp += x->tag_typeid_name();
                        tmp += "] = ";
                        tmp += x->value_as_string();
                        tmp += '\n';
                        }
                    what_.swap(tmp);
                    }
                return what_.c_str();
                }

            private:

            friend class exception;

            typedef std::map< type_info_wrapper, shared_ptr<error_info_base const> > error_info_map;
            error_info_map info_;
            mutable std::string what_;
            mutable int count_;

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

        inline
        void
        set_data( exception const * e, shared_ptr<exception_detail::error_info_base const> const & x, exception_detail::type_info_ const & typeid_ )
            {
            if( !e->data_ )
                e->data_ = intrusive_ptr<exception_detail::error_info_container>(new exception_detail::error_info_container_impl);
            e->data_->set(x,typeid_);
            }
        }

    template <class E,class Tag,class T>
    inline
    E const &
    operator<<( E const & x, error_info<Tag,T> const & v )
        {
        typedef error_info<Tag,T> error_info_tag_t;
        shared_ptr<error_info_tag_t> p( new error_info_tag_t(v) );
        exception_detail::set_data(&x,p,BOOST_EXCEPTION_STATIC_TYPEID(error_info_tag_t));
        return x;
        }
    }

#endif
