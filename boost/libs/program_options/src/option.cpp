// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/program_options/option.hpp>
#include <boost/program_options/detail/convert.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>

#include <boost/bind.hpp>

namespace boost { namespace program_options {

    namespace {
        
    }

    woption::woption(const option& opt)
    {
        this->string_key = opt.string_key;
        this->position_key = opt.position_key;

        std::transform(opt.value.begin(), opt.value.end(),
                       back_inserter(value),
                       bind(from_8_bit, _1, ref(facet)));
    }

}}
