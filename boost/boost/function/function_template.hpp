// Boost.Function library

// Copyright (C) 2001 Doug Gregor (gregod@cs.rpi.edu)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

// For more information, see http://www.boost.org

/* Note: this header is a header template and must NOT have multiple-inclusion
   protection. */

#include <cassert>
#include <algorithm>

// Zero-initialize the "invoker" member of the functionN object.
// The invoker member only exists when we aren't using the virtual
// function implementation
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
#  define BOOST_FUNCTION_INIT
#else
#  define BOOST_FUNCTION_INIT , invoker(0)
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS

// Type of the default allocator
#ifndef BOOST_NO_STD_ALLOCATOR
#  define BOOST_FUNCTION_DEFAULT_ALLOCATOR std::allocator<function_base>
#else
#  define BOOST_FUNCTION_DEFAULT_ALLOCATOR int
#endif // BOOST_NO_STD_ALLOCATOR

namespace boost {
  namespace detail {
    namespace function {
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      template<typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
      struct BOOST_FUNCTION_INVOKER_BASE
      {
        virtual ~BOOST_FUNCTION_INVOKER_BASE() {}
        virtual R call(BOOST_FUNCTION_PARMS) const = 0;
        virtual BOOST_FUNCTION_INVOKER_BASE* clone() const = 0;
        virtual void destroy(BOOST_FUNCTION_INVOKER_BASE*) = 0;
      };
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS

      template<
        typename FunctionPtr,
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename Allocator,
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
        >
      struct BOOST_FUNCTION_FUNCTION_INVOKER
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        : public BOOST_FUNCTION_INVOKER_BASE<
                   R BOOST_FUNCTION_COMMA
                   BOOST_FUNCTION_TEMPLATE_ARGS
                 >
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      {
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        explicit BOOST_FUNCTION_FUNCTION_INVOKER(FunctionPtr f) : 
          function_ptr(f) {}

        virtual R call(BOOST_FUNCTION_PARMS) const
        {
          return function_ptr(BOOST_FUNCTION_ARGS);
        }

        virtual BOOST_FUNCTION_FUNCTION_INVOKER* clone() const
        {
#  ifdef BOOST_NO_STD_ALLOCATOR
          return new BOOST_FUNCTION_FUNCTION_INVOKER(function_ptr);
#  else
          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_FUNCTION_INVOKER>::other 
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          pointer_type copy = allocator.allocate(1);
          allocator.construct(copy, *this);
          return static_cast<BOOST_FUNCTION_FUNCTION_INVOKER*>(copy);
#  endif // BOOST_NO_STD_ALLOCATOR
        }

        virtual void destroy(BOOST_FUNCTION_INVOKER_BASE<
                               R BOOST_FUNCTION_COMMA
                               BOOST_FUNCTION_TEMPLATE_ARGS
                             >* p)
        {
#  ifdef BOOST_NO_STD_ALLOCATOR
          delete p;
#  else
          BOOST_FUNCTION_FUNCTION_INVOKER* victim = 
            dynamic_cast<BOOST_FUNCTION_FUNCTION_INVOKER*>(p);

          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_FUNCTION_INVOKER>::other 
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          allocator.destroy(victim);
          allocator.deallocate(victim, 1);
#  endif // BOOST_NO_STD_ALLOCATOR
        }

      private:
        mutable FunctionPtr function_ptr;
#else
        static R invoke(any_pointer function_ptr BOOST_FUNCTION_COMMA
                        BOOST_FUNCTION_PARMS)
        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
          return f(BOOST_FUNCTION_ARGS);
        }
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      };

      template<
        typename FunctionPtr,
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename Allocator,
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
        >
      struct BOOST_FUNCTION_VOID_FUNCTION_INVOKER
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        : public BOOST_FUNCTION_INVOKER_BASE<
                   unusable BOOST_FUNCTION_COMMA
                   BOOST_FUNCTION_TEMPLATE_ARGS
                 >
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      {
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        explicit BOOST_FUNCTION_VOID_FUNCTION_INVOKER(FunctionPtr f) : 
          function_ptr(f) {}

        virtual unusable call(BOOST_FUNCTION_PARMS) const
        {
          function_ptr(BOOST_FUNCTION_ARGS);
          return unusable();
        }

        virtual BOOST_FUNCTION_VOID_FUNCTION_INVOKER* clone() const
        {
#    ifdef BOOST_NO_STD_ALLOCATOR
          return new BOOST_FUNCTION_VOID_FUNCTION_INVOKER(function_ptr);
#    else
          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_VOID_FUNCTION_INVOKER>::other
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          pointer_type copy = allocator.allocate(1);
          allocator.construct(copy, *this);
          return static_cast<BOOST_FUNCTION_VOID_FUNCTION_INVOKER*>(copy);
#    endif // BOOST_NO_STD_ALLOCATOR
        }

        virtual void destroy(BOOST_FUNCTION_INVOKER_BASE<
                               unusable BOOST_FUNCTION_COMMA
                               BOOST_FUNCTION_TEMPLATE_ARGS
                             >* p)
        {
#    ifdef BOOST_NO_STD_ALLOCATOR
          delete p;
#    else
          BOOST_FUNCTION_VOID_FUNCTION_INVOKER* victim =
            dynamic_cast<BOOST_FUNCTION_VOID_FUNCTION_INVOKER*>(p);

          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_VOID_FUNCTION_INVOKER>::other
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          allocator.destroy(victim);
          allocator.deallocate(victim, 1);
#    endif // BOOST_NO_STD_ALLOCATOR
        }

      private:
        mutable FunctionPtr function_ptr;
#  else
        static unusable invoke(any_pointer function_ptr BOOST_FUNCTION_COMMA
                               BOOST_FUNCTION_PARMS)

        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
          f(BOOST_FUNCTION_ARGS);
          return unusable();
        }
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      };

      template<
        typename FunctionObj,
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename Allocator,
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_FUNCTION_OBJ_INVOKER
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        : public BOOST_FUNCTION_INVOKER_BASE<
                   R BOOST_FUNCTION_COMMA
                   BOOST_FUNCTION_TEMPLATE_ARGS
                 >
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      {
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        explicit BOOST_FUNCTION_FUNCTION_OBJ_INVOKER(const FunctionObj& f) :
          function_obj(f) {}

        virtual R call(BOOST_FUNCTION_PARMS) const
        {
          return function_obj(BOOST_FUNCTION_ARGS);
        }

        virtual BOOST_FUNCTION_FUNCTION_OBJ_INVOKER* clone() const
        {
#ifdef BOOST_NO_STD_ALLOCATOR
          return new BOOST_FUNCTION_FUNCTION_OBJ_INVOKER(function_obj);
#else
          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_FUNCTION_OBJ_INVOKER>::other
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          pointer_type copy = allocator.allocate(1);
          allocator.construct(copy, *this);
          return static_cast<BOOST_FUNCTION_FUNCTION_OBJ_INVOKER*>(copy);
#endif // BOOST_NO_STD_ALLOCATOR
        }

        virtual void destroy(BOOST_FUNCTION_INVOKER_BASE<
                               R BOOST_FUNCTION_COMMA
                               BOOST_FUNCTION_TEMPLATE_ARGS
                             >* p)
        {
#ifdef BOOST_NO_STD_ALLOCATOR
          delete p;
#else
          BOOST_FUNCTION_FUNCTION_OBJ_INVOKER* victim =
            dynamic_cast<BOOST_FUNCTION_FUNCTION_OBJ_INVOKER*>(p);

          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_FUNCTION_OBJ_INVOKER>::other 
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          allocator.destroy(victim);
          allocator.deallocate(victim, 1);
#endif // BOOST_NO_STD_ALLOCATOR
        }

      private:
        mutable FunctionObj function_obj;
#else
        static R invoke(any_pointer function_obj_ptr BOOST_FUNCTION_COMMA
                        BOOST_FUNCTION_PARMS)

        {
          FunctionObj* f = static_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          return (*f)(BOOST_FUNCTION_ARGS);
        }
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      };

      template<
        typename FunctionObj,
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename Allocator,
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        : public BOOST_FUNCTION_INVOKER_BASE<
                   unusable BOOST_FUNCTION_COMMA
                   BOOST_FUNCTION_TEMPLATE_ARGS
                 >
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      {
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        explicit BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER(const FunctionObj& f)
          : function_obj(f) {}

        virtual unusable call(BOOST_FUNCTION_PARMS) const
        {
          function_obj(BOOST_FUNCTION_ARGS);
          return unusable();
        }

        virtual BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER* clone() const
        {
#  ifdef BOOST_NO_STD_ALLOCATOR
          return new BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER(function_obj);
#  else
          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER>::other
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          pointer_type copy = allocator.allocate(1);
          allocator.construct(copy, *this);
          return static_cast<BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER*>(copy);
#  endif // BOOST_NO_STD_ALLOCATOR
        }

        virtual void destroy(BOOST_FUNCTION_INVOKER_BASE<
                               unusable BOOST_FUNCTION_COMMA
                               BOOST_FUNCTION_TEMPLATE_ARGS
                             >* p)
        {
#  ifdef BOOST_NO_STD_ALLOCATOR
          delete p;
#  else
          BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER* victim =
            dynamic_cast<BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER*>(p);

          typedef typename Allocator::
            template rebind<BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER>::other
            allocator_type;
          typedef typename allocator_type::pointer pointer_type;
          allocator_type allocator;

          allocator.destroy(victim);
          allocator.deallocate(victim, 1);
#  endif // BOOST_NO_STD_ALLOCATOR
        }

      private:
        mutable FunctionObj function_obj;
#  else
        static unusable invoke(any_pointer function_obj_ptr 
                               BOOST_FUNCTION_COMMA
                               BOOST_FUNCTION_PARMS)

        {
          FunctionObj* f = static_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          (*f)(BOOST_FUNCTION_ARGS);
          return unusable();
        }
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      };

      template<
        typename FunctionPtr,
        typename Allocator,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_GET_FUNCTION_INVOKER
      {
        typedef typename IF<(is_void<R>::value),
                            BOOST_FUNCTION_VOID_FUNCTION_INVOKER<
                            FunctionPtr,
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            Allocator,
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >,
                          BOOST_FUNCTION_FUNCTION_INVOKER<
                            FunctionPtr,
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            Allocator,
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >
                       >::type type;
      };

      template<
        typename FunctionObj,
        typename Allocator,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
       >
      struct BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER
      {
        typedef typename IF<(is_void<R>::value),
                            BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER<
                            FunctionObj,
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            Allocator,
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >,
                          BOOST_FUNCTION_FUNCTION_OBJ_INVOKER<
                            FunctionObj,
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            Allocator,
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >
                       >::type type;
      };
    } // end namespace function
  } // end namespace detail

  template<
    typename R BOOST_FUNCTION_COMMA
    BOOST_FUNCTION_TEMPLATE_PARMS,
    typename Policy    = empty_function_policy,
    typename Mixin     = empty_function_mixin,
    typename Allocator = BOOST_FUNCTION_DEFAULT_ALLOCATOR
  >
  class BOOST_FUNCTION_FUNCTION : public function_base, public Mixin
  {
  public:
    BOOST_STATIC_CONSTANT(int, args = BOOST_FUNCTION_NUM_ARGS);
    
#if BOOST_FUNCTION_NUM_ARGS == 1
    typedef T1 argument_type;
#elif BOOST_FUNCTION_NUM_ARGS == 2
    typedef T1 first_argument_type;
    typedef T2 second_argument_type;
#endif
    typedef typename detail::function::function_return_type<R>::type 
      result_type;
    typedef Policy    policy_type;
    typedef Mixin     mixin_type;
    typedef Allocator allocator_type;
    typedef BOOST_FUNCTION_FUNCTION self_type;

  private:    
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
    typedef detail::function::BOOST_FUNCTION_INVOKER_BASE<
                                result_type BOOST_FUNCTION_COMMA
                                BOOST_FUNCTION_TEMPLATE_ARGS
                              >
          impl_type;
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS

  public:
    BOOST_FUNCTION_FUNCTION() : function_base(), Mixin() BOOST_FUNCTION_INIT {}

    explicit BOOST_FUNCTION_FUNCTION(const Mixin& m) : 
      function_base(), Mixin(m) BOOST_FUNCTION_INIT 
    {
    }

    // MSVC chokes if the following two constructors are collapsed into
    // one with a default parameter.
    template<typename Functor>
    BOOST_FUNCTION_FUNCTION(const Functor& f) :
      function_base(), Mixin() BOOST_FUNCTION_INIT
    {
      this->assign_to(f);
    }

    template<typename Functor>
    BOOST_FUNCTION_FUNCTION(const Functor& f, const Mixin& m) :
      function_base(), Mixin(m) BOOST_FUNCTION_INIT
    {
      this->assign_to(f);
    }

#ifdef __BORLANDC__
    template<typename Functor>
    BOOST_FUNCTION_FUNCTION(Functor* f, const Mixin& m = Mixin()) : 
      function_base(), Mixin(m) BOOST_FUNCTION_INIT
    {
      this->assign_to(f);
    }
#endif // __BORLANDC__

    BOOST_FUNCTION_FUNCTION(const BOOST_FUNCTION_FUNCTION& f) :
      function_base(), Mixin(static_cast<const Mixin&>(f))
      BOOST_FUNCTION_INIT
    {
      this->assign_to_own(f);
    }

    ~BOOST_FUNCTION_FUNCTION() { clear(); }

    result_type operator()(BOOST_FUNCTION_PARMS) const
    {
      assert(!this->empty());

      policy_type policy;
      policy.precall(this);

#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      const impl_type* i = reinterpret_cast<const impl_type*>(impl);
      result_type result = i->call(BOOST_FUNCTION_ARGS);
#else
      result_type result = invoker(functor BOOST_FUNCTION_COMMA
                                   BOOST_FUNCTION_ARGS);
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS

      policy.postcall(this);
      return result;
    }

    // The distinction between when to use BOOST_FUNCTION_FUNCTION and
    // when to use self_type is obnoxious. MSVC cannot handle self_type as
    // the return type of these assignment operators, but Borland C++ cannot
    // handle BOOST_FUNCTION_FUNCTION as the type of the temporary to 
    // construct.
    template<typename Functor>
    BOOST_FUNCTION_FUNCTION& operator=(const Functor& f)
    {
      self_type(f, static_cast<const Mixin&>(*this)).swap(*this);
      return *this;
    }

#ifdef __BORLANDC__
    template<typename Functor>
    BOOST_FUNCTION_FUNCTION& operator=(Functor* f)
    {
      self_type(f, static_cast<const Mixin&>(*this)).swap(*this);
      return *this;
    }
#endif // __BORLANDC__

    template<typename Functor>
    void set(const Functor& f)
    {
      self_type(f, static_cast<const Mixin&>(*this)).swap(*this);
    }

#ifdef __BORLANDC__
    template<typename Functor>
    void set(Functor* f)
    {
      self_type(f, static_cast<const Mixin&>(*this)).swap(*this);
    }
#endif // __BORLANDC__

    // Assignment from another BOOST_FUNCTION_FUNCTION
    BOOST_FUNCTION_FUNCTION& operator=(const BOOST_FUNCTION_FUNCTION& f)
    {
      if (&f == this)
        return *this;

      self_type(f).swap(*this);
      return *this;
    }

    // Assignment from another BOOST_FUNCTION_FUNCTION
    void set(const BOOST_FUNCTION_FUNCTION& f)
    {
      if (&f == this)
        return;

      self_type(f).swap(*this);
    }

    void swap(BOOST_FUNCTION_FUNCTION& other)
    {
      if (&other == this)
        return;

#ifndef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      std::swap(manager, other.manager);
      std::swap(functor, other.functor);
      std::swap(invoker, other.invoker);
#else
      std::swap(impl, other.impl);
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      std::swap(static_cast<Mixin&>(*this),static_cast<Mixin&>(other));
    }

    // Clear out a target, if there is one
    void clear()
    {
#ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      if (impl) {
        impl_type* i = reinterpret_cast<impl_type*>(impl);
        i->destroy(i);
        impl = 0;
      }
#else
      if (manager)
        functor = manager(functor, detail::function::destroy_functor);
    
      manager = 0;
      invoker = 0;
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
    }

  private:
    void assign_to_own(const BOOST_FUNCTION_FUNCTION& f)
    {
      if (!f.empty()) {
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
        impl_type* other_impl = reinterpret_cast<impl_type*>(f.impl);
        impl = static_cast<void*>(other_impl->clone());
#  else
        invoker = f.invoker;
        manager = f.manager;
        functor = f.manager(f.functor, detail::function::clone_functor);
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS      
      }          
    }

    template<typename Functor>
    void assign_to(const Functor& f)
    {
      typedef typename detail::function::get_function_tag<Functor>::type tag;
      this->assign_to(f, tag());
    }

    template<typename MemberPtr>
    void assign_to(MemberPtr f, detail::function::member_ptr_tag)
    {
      this->assign_to(mem_fn(f));
    }

    template<typename FunctionPtr>
    void assign_to(FunctionPtr f, detail::function::function_ptr_tag)
    {
      clear();
        
      if (f) {
        typedef typename detail::function::BOOST_FUNCTION_GET_FUNCTION_INVOKER<
                           FunctionPtr,
                           Allocator,
                           R BOOST_FUNCTION_COMMA
                           BOOST_FUNCTION_TEMPLATE_ARGS
                         >::type
          invoker_type;
    
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
#    ifdef BOOST_NO_STD_ALLOCATOR
        impl_type* i = new invoker_type(f);
#    else
        typedef typename Allocator::template rebind<invoker_type>::other
          allocator_type;
        typedef typename allocator_type::pointer pointer_type;
        allocator_type allocator;
    
        pointer_type copy = allocator.allocate(1);
        new (copy) invoker_type(f);
        impl_type* i = static_cast<impl_type*>(copy);
#    endif // BOOST_NO_STD_ALLOCATOR
        impl = static_cast<void*>(i);
#  else
        invoker = &invoker_type::invoke;
        manager = &detail::function::functor_manager<FunctionPtr, 
                                                     Allocator>::manage;
        functor = manager(detail::function::any_pointer(
                            reinterpret_cast<void (*)()>(f)
                          ),
                          detail::function::clone_functor);
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      }
    }  
        
    template<typename FunctionObj>
    void assign_to(const FunctionObj& f, detail::function::function_obj_tag)
    {
      if (!detail::function::has_empty_target(&f)) {
        typedef 
          typename detail::function::BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER<
                                       FunctionObj,
                                       Allocator,
                                       R BOOST_FUNCTION_COMMA
                                       BOOST_FUNCTION_TEMPLATE_ARGS
                                     >::type
          invoker_type;
    
#  ifdef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
#    ifdef BOOST_NO_STD_ALLOCATOR
        impl_type* i = new invoker_type(f);
#    else
        typedef typename Allocator::template rebind<invoker_type>::other
          allocator_type;
        typedef typename allocator_type::pointer pointer_type;
        allocator_type allocator;
    
        pointer_type copy = allocator.allocate(1);
        new (copy) invoker_type(f);
        impl_type* i = static_cast<impl_type*>(copy);
#    endif // BOOST_NO_STD_ALLOCATOR
        impl = static_cast<void*>(i);
#  else
        invoker = &invoker_type::invoke;
        manager = &detail::function::functor_manager<FunctionObj, 
                                                     Allocator>::manage;
        functor = 
          manager(detail::function::any_pointer(const_cast<FunctionObj*>(&f)),
                  detail::function::clone_functor);
#  endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
      }
    }
    
#ifndef BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
    typedef result_type (*invoker_type)(detail::function::any_pointer
                                        BOOST_FUNCTION_COMMA
                                        BOOST_FUNCTION_TEMPLATE_ARGS);
    
    invoker_type invoker;
#endif // BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
  };

  template<typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS ,
           typename Policy, typename Mixin, typename Allocator>
  inline void swap(BOOST_FUNCTION_FUNCTION<
                     R BOOST_FUNCTION_COMMA
                     BOOST_FUNCTION_TEMPLATE_ARGS ,
                     Policy,
                     Mixin,
                     Allocator
                   >& f1,
                   BOOST_FUNCTION_FUNCTION<
                     R BOOST_FUNCTION_COMMA 
                     BOOST_FUNCTION_TEMPLATE_ARGS,
                     Policy,
                     Mixin,
                     Allocator
                   >& f2)
  {
    f1.swap(f2);
  }
}

// Cleanup after ourselves...
#undef BOOST_FUNCTION_DEFAULT_ALLOCATOR
#undef BOOST_FUNCTION_INIT
