#ifndef BOOST_DETAIL_PLUGIN_HPP
#define BOOST_DETAIL_PLUGIN_HPP

#include <utility> // for std::pair

namespace boost {

  namespace detail {

    template <int TagMatched>
    struct plugin_value_dispatch { };

    template <>
    struct plugin_value_dispatch<1> {
      template <class Plugin, class T, class Tag>
      static T& get_value(Plugin& p, T, Tag) {
	return p.m_value; 
      }
      template <class Plugin, class T, class Tag>
      static const T& const_get_value(const Plugin& p, T, Tag) {
	return p.m_value; 
      }
    };
    template <>
    struct plugin_value_dispatch<0> {
      template <class Plugin, class T, class Tag>
      static T& get_value(Plugin& p, T t, Tag tag) {
	typedef typename Plugin::next_type Next;
	typedef typename Next::tag_type Next_tag;
	enum { match = int(Next_tag::num) == int(Tag::num) };
	return plugin_value_dispatch<match>
	  ::get_value(static_cast<Next&>(p), t, tag);
      }
      template <class Plugin, class T, class Tag>
      static const T& const_get_value(const Plugin& p, T t, Tag tag) {
	typedef typename Plugin::next_type Next;
	typedef typename Next::tag_type Next_tag;
	enum { match = int(Next_tag::num) == int(Tag::num) };
	return plugin_value_dispatch<match>
	  ::const_get_value(static_cast<const Next&>(p), t, tag);
      }
    };

    template <class Plugin>
    struct build_plugin_tag_value_alist
    {
      typedef typename Plugin::next_type NextPlugin;
      typedef typename Plugin::value_type Value;
      typedef typename Plugin::tag_type Tag;
      typedef typename build_plugin_tag_value_alist<NextPlugin>::type Next;
      typedef std::pair< std::pair<Tag,Value>, Next> type;
    };
    template <>
    struct build_plugin_tag_value_alist<no_plugin>
    {
      typedef no_plugin type;
    };

    struct error_plugin_not_found { };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class TagValueAList, class Tag>
    struct extract_value {
      typedef error_plugin_not_found type;
    };
    template <class Value, class Tag1, class Tag2, class Rest>
    struct extract_value< std::pair<std::pair<Tag1,Value>,Rest>, Tag2> {
      typedef typename extract_value<Rest,Tag2>::type type;
    };
    template <class Value, class Tag, class Rest>
    struct extract_value< std::pair<std::pair<Tag,Value>,Rest>, Tag> {
      typedef Value type;
    };
#else
    // VC++ workaround:
    // The main idea here is to replace partial specialization with
    // nested template member classes. Of course there is the
    // further complication that the outer class of the nested
    // template class cannot itself be a template class.
    // Hence the need for the ev_selector. -JGS

    struct recursive_extract;
    struct end_extract;

    template <class TagValueAList>
    struct ev_selector { typedef recursive_extract type; };
    template <>
    struct ev_selector<no_plugin> { typedef end_extract type; };

    struct recursive_extract {
      template <class TagValueAList, class Tag1>
      struct bind {
	typedef typename TagValueAList::first_type AListFirst;
	typedef typename AListFirst::first_type Tag2;
	typedef typename AListFirst::second_type Value;
	enum { tag1 = Tag1::num, tag2 = Tag2::num };

	typedef typename TagValueAList::second_type Next;
	typedef typename ev_selector<Next>::type Extractor;
	typedef typename boost::ct_if< tag1==tag2, Value, 
	  typename Extractor::BOOST_TEMPLATE bind<Next,Tag1>::type
	>::type type;
      };
    };
    struct end_extract {
      template <class AList, class Tag1>
      struct bind {
	typedef error_plugin_not_found type;
      };
    };
#endif //!defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  } // namespace detail 
} // namespace boost

#endif // BOOST_DETAIL_PLUGIN_HPP
