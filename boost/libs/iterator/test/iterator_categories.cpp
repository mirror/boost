// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/iterator/iterator_categories.hpp>

using namespace boost;

// Utility function which converts an iterator_category into a
// traversal tag
template <class C>
typename iterator_category_to_traversal<C>::type c2t(C)
{
    typedef typename iterator_category_to_traversal<C>::type result;
    return result();
}

struct v
{
    v();
    ~v();
};

//
// Test conversions from iterator_tag<...> to old-style iterator categories
//

// These "solid" tag types ensure exact matching of iterator
// classification, because unlike the std:: iterator tags, they're not
// inter-convertible
struct output_iter {};
struct input_iter {};
struct input_output_iter {};
struct forward_iter {};
struct bidirectional_iter {};
struct random_access_iter{} ;

// Convert various old-style categories into "solid" tags.
input_iter         cat(std::input_iterator_tag);
output_iter        cat(std::output_iterator_tag);
input_output_iter  cat(boost::detail::input_output_iterator_tag);
forward_iter       cat(std::forward_iterator_tag);
bidirectional_iter cat(std::bidirectional_iterator_tag);
random_access_iter cat(std::random_access_iterator_tag);

random_access_iter  x1 = cat(iterator_tag<v,v&,random_access_traversal_tag>());
random_access_iter  x2 = cat(iterator_tag<v,v const&,random_access_traversal_tag>());
bidirectional_iter  x3 = cat(iterator_tag<v,v const&,bidirectional_traversal_tag>());
forward_iter        x4 = cat(iterator_tag<v,v const&,forward_traversal_tag>());
input_output_iter   x5 = cat(iterator_tag<v,v,bidirectional_traversal_tag>());
input_iter          x6 = cat(iterator_tag<v const,v,bidirectional_traversal_tag>());
output_iter         x7 = cat(iterator_tag<v,v const&,incrementable_traversal_tag>());


//
// Test conversion from old-style iterator categories to traversal categories
//

// These "solid" tag types ensure exact matching of iterator
// classification, because unlike the traversal tags, they're not
// inter-convertible
struct incrementable_traversal {};
struct single_pass_traversal {};
struct forward_traversal {};
struct bidirectional_traversal {};
struct random_access_traversal {} ;

// Convert various traversal categories into "solid" tags
incrementable_traversal trav(incrementable_traversal_tag);
single_pass_traversal   trav(single_pass_traversal_tag);
forward_traversal       trav(forward_traversal_tag);
bidirectional_traversal trav(bidirectional_traversal_tag);
random_access_traversal trav(random_access_traversal_tag);

// Show that full types of tags that are already traversal categories
// are preserved
iterator_tag<v,v&,random_access_traversal_tag> yz1
     = c2t(iterator_tag<v,v&,random_access_traversal_tag>());

// Test traversal extraction from both old-style and new-style tags
random_access_traversal  yy1 = trav(c2t(iterator_tag<v,v&,random_access_traversal_tag>()));
bidirectional_traversal  yy2 = trav(c2t(iterator_tag<v,v&,bidirectional_traversal_tag>()));
forward_traversal        yy3 = trav(c2t(iterator_tag<v,v const&,forward_traversal_tag>()));
single_pass_traversal    yy4 = trav(c2t(iterator_tag<v const,v,single_pass_traversal_tag>()));
incrementable_traversal  yy5 = trav(c2t(iterator_tag<v,v const&,incrementable_traversal_tag>()));

random_access_traversal  z1 = trav(c2t(std::random_access_iterator_tag()));
bidirectional_traversal  z2 = trav(c2t(std::bidirectional_iterator_tag()));
forward_traversal        z3 = trav(c2t(std::forward_iterator_tag()));
single_pass_traversal    z4 = trav(c2t(std::input_iterator_tag()));
incrementable_traversal  z5 = trav(c2t(std::output_iterator_tag()));
