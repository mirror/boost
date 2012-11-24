
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_COROUTINE_OBJECT_H
#define BOOST_COROUTINES_DETAIL_COROUTINE_OBJECT_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/move/move.hpp>
#include <boost/ref.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/function_traits.hpp>

#include <boost/coroutine/attributes.hpp>
#include <boost/coroutine/detail/arg.hpp>
#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_base.hpp>
#include <boost/coroutine/detail/exceptions.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/holder.hpp>
#include <boost/coroutine/detail/param.hpp>
#include <boost/coroutine/flags.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Context >
void trampoline1( intptr_t vp)
{
    BOOST_ASSERT( vp);

    holder< Context * > * hldr(
        reinterpret_cast< holder< Context * > * >( vp) );
    Context * ctx( hldr->data.get() );

    ctx->run( hldr->ctx);
}

template< typename Context, typename Arg >
void trampoline2( intptr_t vp)
{
    BOOST_ASSERT( vp);

    holder< tuple< Context *, Arg > > * hldr(
        reinterpret_cast< holder< tuple< Context *, Arg > > * >( vp) );
    Context * ctx( hldr->data.get().get< 0 >() );
    Arg arg( hldr->data.get().get< 1 >() );

    ctx->run( hldr->ctx, arg);
}

template<
    typename Signature,
    typename Fn, typename StackAllocator, typename Allocator,
    typename Caller,
    typename Result, int arity
>
class coroutine_object;

#include <boost/coroutine/detail/coroutine_object_void_0.ipp>
#include <boost/coroutine/detail/coroutine_object_void_1.ipp>
#include <boost/coroutine/detail/coroutine_object_void_arity.ipp>
#include <boost/coroutine/detail/coroutine_object_result_0.ipp>
#include <boost/coroutine/detail/coroutine_object_result_1.ipp>
#include <boost/coroutine/detail/coroutine_object_result_arity.ipp>

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_COROUTINE_OBJECT_H
