
#include <boost/regex.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/concept_check.hpp>


int main()
{
   typedef boost::bidirectional_iterator_archetype<char> iterator_type;
   boost::regex r;
   iterator_type a, b;
   boost::detail::dummy_constructor dummy;
   boost::output_iterator_archetype<char> out(dummy);
   std::string s;
   boost::match_results<iterator_type> what;

   boost::regex_match(a, b, r);
   boost::regex_match(a, b, what, r);
   boost::regex_search(a, b, r);
   boost::regex_search(a, b, what, r);
   out = boost::regex_replace(out, a, b, r, s, boost::match_default);
   s = boost::regex_replace(s, r, s, boost::match_default);

   out = what.format(out, s, boost::format_default);
   s = what.format(s, boost::format_default);

   boost::function_requires<
      boost::ForwardIteratorConcept<
         boost::regex_iterator<iterator_type>
      >
   >();
   boost::function_requires<
      boost::ForwardIteratorConcept<
         boost::regex_token_iterator<iterator_type>
      >
   >();

}
