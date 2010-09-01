//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//Based on an exception_ptr implementation by Anthony Williams.

#ifdef BOOST_NO_EXCEPTIONS
#error This file requires exception handling to be enabled.
#endif

#include <boost/exception/detail/clone_current_exception.hpp>
#include <boost/exception/exception.hpp>
#include <boost/shared_ptr.hpp>
#include <windows.h>

namespace
    {
    unsigned const exception_maximum_parameters=15;
    unsigned const exception_noncontinuable=1;

#if _MSC_VER==1310
    int const exception_info_offset=0x74;
#elif _MSC_VER==1400
    int const exception_info_offset=0x80;
#else
    int const exception_info_offset=-1;
#endif

    struct
    exception_record
        {
        unsigned long ExceptionCode;
        unsigned long ExceptionFlags;
        exception_record * ExceptionRecord;
        void * ExceptionAddress;
        unsigned long NumberParameters;
        ULONG_PTR ExceptionInformation[exception_maximum_parameters];
        };

    struct
    exception_pointers
        {
        exception_record * ExceptionRecord;
        void * ContextRecord;
        };

    unsigned const cpp_exception_code=0xE06D7363;
    unsigned const cpp_exception_magic_flag=0x19930520;
    unsigned const cpp_exception_parameter_count=3;

    struct
    dummy_exception_type
        {
        };

    typedef int(dummy_exception_type::*normal_copy_constructor_ptr)(void * src);
    typedef int(dummy_exception_type::*copy_constructor_with_virtual_base_ptr)(void * src,void * dest);
    typedef void (dummy_exception_type::*destructor_ptr)();

    union
    cpp_copy_constructor
        {
        normal_copy_constructor_ptr normal_copy_constructor;
        copy_constructor_with_virtual_base_ptr copy_constructor_with_virtual_base;
        };

    enum
    cpp_type_flags
        {
        class_is_simple_type=1,
        class_has_virtual_base=4
        };

    struct cpp_type_info
        {
        unsigned flags;
        void const * type_info; //std::type_info * type_info;
        int this_offset;
        int vbase_descr;
        int vbase_offset;
        unsigned long size;
        cpp_copy_constructor copy_constructor;
        };

    struct
    cpp_type_info_table
        {
        unsigned count;
        const cpp_type_info * info[1];
        };

    struct
    cpp_exception_type
        {
        unsigned flags;
        destructor_ptr destructor;
        void(*custom_handler)();
        cpp_type_info_table const * type_info_table;
        };

    struct
    exception_object_deleter
        {
        cpp_exception_type const * exception_type_;

        exception_object_deleter( cpp_exception_type const * exception_type ):
            exception_type_(exception_type)
            {
            BOOST_ASSERT(exception_type_!=0);
            }

        void
        operator()( void * exception_object )
            {
            BOOST_ASSERT(exception_object!=0);
            dummy_exception_type * dummy_exception_ptr=reinterpret_cast<dummy_exception_type *>(exception_object);
            (dummy_exception_ptr->*(exception_type_->destructor))();
            free(exception_object);
            }
        };

    boost::shared_ptr<void>
    copy_msvc_exception( void * source_object, cpp_exception_type const * exception_type )
        {
        void * exception_object = malloc(exception_type->type_info_table->info[0]->size);
        if( !exception_object )
            throw std::bad_alloc();
        cpp_type_info const * type = exception_type->type_info_table->info[0];
        if( !(type->flags & class_is_simple_type) && type->copy_constructor.normal_copy_constructor )
            {
            dummy_exception_type * dummy_exception_ptr = reinterpret_cast<dummy_exception_type *>(exception_object);
            if( type->flags & class_has_virtual_base )
                (dummy_exception_ptr->*(type->copy_constructor.copy_constructor_with_virtual_base))(source_object,exception_object);
            else
                (dummy_exception_ptr->*(type->copy_constructor.normal_copy_constructor))(source_object);
            }
        else
            memmove(exception_object,source_object,type->size);
        return boost::shared_ptr<void>(exception_object,exception_object_deleter(exception_type));
        }

    class
    cloned_exception:
        public boost::exception_detail::clone_base
        {
        cloned_exception( cloned_exception const & );
        cloned_exception & operator=( cloned_exception const & );

        cpp_exception_type const * exception_type_;
        boost::shared_ptr<void> exception_object_;

        public:

        cloned_exception( void * source_object, cpp_exception_type const * exception_type ):
            exception_type_(exception_type),
            exception_object_(copy_msvc_exception(source_object,exception_type_))
            {
            }

        ~cloned_exception() throw()
            {
            }

        boost::exception_detail::clone_base const *
        clone() const
            {
            return new cloned_exception(exception_object_.get(),exception_type_);
            }

        void
        rethrow() const
            {
            boost::shared_ptr<void const> clone=copy_msvc_exception(exception_object_.get(),exception_type_);
            ULONG_PTR args[cpp_exception_parameter_count];
            args[0]=cpp_exception_magic_flag;
            args[1]=reinterpret_cast<ULONG_PTR>(clone.get());
            args[2]=reinterpret_cast<ULONG_PTR>(exception_type_);
            RaiseException(cpp_exception_code,EXCEPTION_NONCONTINUABLE,cpp_exception_parameter_count,args);
            }
        };

    bool
    is_cpp_exception( EXCEPTION_RECORD * record )
        {
        return record && 
            (record->ExceptionCode==cpp_exception_code) &&
            (record->NumberParameters==cpp_exception_parameter_count) &&
            (record->ExceptionInformation[0]==cpp_exception_magic_flag);
        }

    unsigned long
    exception_cloning_filter( boost::exception_detail::clone_base const * * ptr, void * info_ )
        {
        BOOST_ASSERT(ptr!=0);
        BOOST_ASSERT(!*ptr);
        BOOST_ASSERT(info_!=0);
        EXCEPTION_POINTERS * info=reinterpret_cast<EXCEPTION_POINTERS *>(info_);
        EXCEPTION_RECORD * record=info->ExceptionRecord;
        if( is_cpp_exception(record) )
            {
            if( !record->ExceptionInformation[2] )
                {
                record = *reinterpret_cast<EXCEPTION_RECORD * *>(reinterpret_cast<char *>(_errno())+exception_info_offset);
                }
            if( is_cpp_exception(record) && record->ExceptionInformation[2] )
                try
                    {
                    *ptr = new cloned_exception(
                            reinterpret_cast<void *>(record->ExceptionInformation[1]),
                            reinterpret_cast<cpp_exception_type const *>(record->ExceptionInformation[2]));
                    }
                catch(
                std::bad_alloc & )
                    {
                    BOOST_ASSERT(!*ptr);
                    }
                catch(
                ... )
                    {
                    BOOST_ASSERT(0);
                    }
            }
        return EXCEPTION_EXECUTE_HANDLER;
        }
    }

namespace
boost
    {
    namespace
    exception_detail
        {
        int
        clone_current_exception_msvc( clone_base const * & cloned )
            {
            BOOST_ASSERT(!cloned);
            if( exception_info_offset<0 )
                return clone_current_exception_result::not_supported;
             clone_base const * res=0;
            __try
                {
                throw;
                }
            __except(exception_cloning_filter(&res,GetExceptionInformation()))
                {
                }
            if( !res )
                return clone_current_exception_result::bad_alloc;
            else
                {
                cloned=res;
                return clone_current_exception_result::success;
                }
            }
        }
    }

#if 0
//This is the original Anthony Williams implementation
#ifndef EXCEPTION_PTR_HPP
#define EXCEPTION_PTR_HPP
#include <typeinfo>
#include "thread_heap_alloc.hpp"
#include <string.h>
#include "thread_primitives.hpp"
#include <excpt.h>

namespace
boost
    {
    namespace
    exception_detail
        {
        namespace
        win32
            {
            unsigned const exception_maximum_parameters=15;
            unsigned const exception_noncontinuable=1;

            struct
            exception_record
                {
                unsigned long ExceptionCode;
                unsigned long ExceptionFlags;
                exception_record *ExceptionRecord;
                void* ExceptionAddress;
                unsigned long NumberParameters;
                ulong_ptr ExceptionInformation[exception_maximum_parameters];
                };

            struct
            exception_pointers
                {
                exception_record* ExceptionRecord;
                void* ContextRecord;
                };

            extern "C"
                {
                __declspec(dllimport) void __stdcall RaiseException(unsigned long,unsigned long,unsigned long,ulong_ptr*);
                }
            }

        unsigned const cpp_exception_code=0xE06D7363;
        unsigned const cpp_exception_magic_flag=0x19930520;
        unsigned const cpp_exception_parameter_count=3;

        struct
        dummy_exception_type
            {
            };

        typedef int(dummy_exception_type::*normal_copy_constructor_ptr)(void * src);
        typedef int(dummy_exception_type::*copy_constructor_with_virtual_base_ptr)(void * src,void * dest);
        typedef void (dummy_exception_type::*destructor_ptr)();

        union
        cpp_copy_constructor
            {
            normal_copy_constructor_ptr normal_copy_constructor;
            copy_constructor_with_virtual_base_ptr copy_constructor_with_virtual_base;
            };

        enum
        cpp_type_flags
            {
            class_is_simple_type=1,
            class_has_virtual_base=4
            };

        struct cpp_type_info
            {
            unsigned flags;
            void const * type_info; //std::type_info * type_info;
            int this_offset;
            int vbase_descr;
            int vbase_offset;
            unsigned long size;
            cpp_copy_constructor copy_constructor;
            };

        struct
        cpp_type_info_table
            {
            unsigned count;
            const cpp_type_info * info[1];
            };

        struct
        cpp_exception_type
            {
            unsigned flags;
            destructor_ptr destructor;
            void(*custom_handler)();
            cpp_type_info_table const * type_info_table;
            };

        class
        msvc_cloned_exception:
            clone_base
            {
            cpp_exception_type const * exception_type;
            void * exception_object;
            bool run_destructor;

            void
            copy( void * source_object )
                {
                BOOST_ASSERT(!exception_object);
                exception_object = malloc(exception_type->type_info_table->info[0]->size);
                if( exception_object )
                    {
                    cpp_type_info const * type = exception_type->type_info_table->info[0];
                    if( !(type->flags & class_is_simple_type) && type->copy_constructor.normal_copy_constructor )
                        {
                        dummy_exception_type * dummy_exception_ptr = reinterpret_cast<dummy_exception_type *>(exception_object);
                        if( type->flags & class_has_virtual_base )
                            (dummy_exception_ptr->*(type->copy_constructor.copy_constructor_with_virtual_base))(source_object,exception_object);
                        else
                            (dummy_exception_ptr->*(type->copy_constructor.normal_copy_constructor))(source_object);
                        }
                    else
                        memmove(exception_object,source_object,type->size);
                    run_destructor=true;
                    }
                }

            public:

            msvc_cloned_exception( void * source_object, cpp_exception_type const * exception_type_ ):
                exception_type(exception_type_),
                exception_object(0),
                run_destructor(false)
                {
                copy(source_object);
                }

            msvc_cloned_exception( msvc_cloned_exception const & other ):
                exception_type(other.exception_type),
                exception_object(0),
                run_destructor(false)
                {
                copy(other.exception_object);
                }

            ~msvc_cloned_exception()
                {
                if( exception_object )
                    {
                    if( run_destructor )
                        {
                        dummy_exception_type * dummy_exception_ptr=reinterpret_cast<dummy_exception_type *>(exception_object);
                        (dummy_exception_ptr->*(exception_type->destructor))();
                        }
                    free(exception_object);
                    }
                }

            void
            rethrow()
                {
                msvc_cloned_exception temp(*this);

                detail::win32::ulong_ptr args[detail::cpp_exception_parameter_count];
                args[0]=detail::cpp_exception_magic_flag;
                args[1]=reinterpret_cast<detail::win32::ulong_ptr>(temp.exception_object);
                args[2]=reinterpret_cast<detail::win32::ulong_ptr>(temp.exception_type);

                temp.run_destructor=false;

                detail::win32::RaiseException(detail::cpp_exception_code,detail::win32::exception_noncontinuable,detail::cpp_exception_parameter_count,args);
                }
            };
        }

    typedef boost::intrusive_ptr<detail::msvc_cloned_exception> exception_ptr;

    namespace
    exception_detail
        {
        extern "C" int * _errno();

        bool
        is_cpp_exception( win32::exception_record * record )
            {
            return record && 
                (record->ExceptionCode==cpp_exception_code) &&
                (record->NumberParameters==cpp_exception_parameter_count) &&
                (record->ExceptionInformation[0]==cpp_exception_magic_flag);
            }

        unsigned long
        exception_cloning_filter( exception_ptr * ptr, void * info_ )
            {
            win32::exception_pointers * info=reinterpret_cast<win32::exception_pointers *>(info_);
            win32::exception_record * record=info->ExceptionRecord;
            if( is_cpp_exception(record) )
                {
                if( !record->ExceptionInformation[2] )
                    {
#if _MSC_VER==1310
                    unsigned const exception_info_offset=0x74;
#elif _MSC_VER==1400
                    unsigned const exception_info_offset=0x80;
#endif
                    record = *reinterpret_cast<win32::exception_record * *>(reinterpret_cast<char *>(_errno())+exception_info_offset);
                    }
                if( is_cpp_exception(record) && record->ExceptionInformation[2] )
                    *ptr = detail::heap_new<msvc_cloned_exception>(reinterpret_cast<void *>(record->ExceptionInformation[1]),
                                                            reinterpret_cast<cpp_exception_type const *>(record->ExceptionInformation[2]));
                }
            return EXCEPTION_EXECUTE_HANDLER;
            }

        void
        clone_current_exception( exception_ptr * res )
            {
            __try
                {
                throw;
                }
            __except(exception_cloning_filter(res,GetExceptionInformation()))
                {
                }
            }
        }

    
    inline
    exception_ptr
    current_exception()
        {
        exception_ptr res;
        clone_current_exception(&res);
        return res;
        }

    inline
    void
    rethrow_exception(exception_ptr p)
        {
        if(p)
            p->rethrow();
        else
            throw "no exception stored";
        }

    template<class E>
    exception_ptr
    copy_exception(E e)
        {
        try
            {
            throw e;
            }
        catch( ... )
            {
            return current_exception();
            }
        }
    }

#endif
#endif
