//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// These are the headers included by the Boost.TR1 implementation,
// by including these directly we probe for problems with cyclic
// dependencies when the TR1 headers are in the include search path.

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/if.hpp>

#include <boost/ref.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/math/complex.hpp>

// All of these are broken by cyclic dependencies:
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/functional/hash.hpp>


