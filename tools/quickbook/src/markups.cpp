/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "quickbook.hpp"
#include "markups.hpp"
#include "block_tags.hpp"
#include "phrase_tags.hpp"
#include <boost/foreach.hpp>
#include <ostream>

namespace quickbook
{
    const char* comment_pre         = "<!--";
    const char* comment_post        = "-->";
    const char* paragraph_pre       = "<para>\n";
    const char* paragraph_post      = "</para>\n";
    const char* hr_                 = "<para/>";
    const char* blurb_pre           = "<sidebar role=\"blurb\">\n";
    const char* blurb_post          = "</sidebar>\n";
    const char* blockquote_pre      = "<blockquote>";
    const char* blockquote_post     = "</blockquote>";
    const char* preformatted_pre    = "<programlisting>";
    const char* preformatted_post   = "</programlisting>";
    const char* warning_pre         = "<warning>";
    const char* warning_post        = "</warning>";
    const char* caution_pre         = "<caution>";
    const char* caution_post        = "</caution>";
    const char* important_pre       = "<important>";
    const char* important_post      = "</important>";
    const char* note_pre            = "<note>";
    const char* note_post           = "</note>";
    const char* tip_pre             = "<tip>";
    const char* tip_post            = "</tip>";
    const char* list_item_pre       = "<listitem><simpara>\n";
    const char* list_item_post      = "\n</simpara></listitem>";
    const char* bold_pre_           = "<emphasis role=\"bold\">";
    const char* bold_post_          = "</emphasis>";
    const char* italic_pre_         = "<emphasis>";
    const char* italic_post_        = "</emphasis>";
    const char* underline_pre_      = "<emphasis role=\"underline\">";
    const char* underline_post_     = "</emphasis>";
    const char* teletype_pre_       = "<literal>";
    const char* teletype_post_      = "</literal>";
    const char* strikethrough_pre_  = "<emphasis role=\"strikethrough\">";
    const char* strikethrough_post_ = "</emphasis>";
    const char* quote_pre_          = "<quote>";
    const char* quote_post_         = "</quote>";
    const char* break_mark          = "<sbr/>\n";
    const char* url_pre_            = "<ulink url=\"";
    const char* url_post_           = "</ulink>";
    const char* link_pre_           = "<link linkend=\"";
    const char* link_post_          = "</link>";
    const char* start_varlistentry_ = "<varlistentry>";
    const char* end_varlistentry_   = "</varlistentry>\n";
    const char* start_varlistterm_  = "<term>";
    const char* end_varlistterm_    = "</term>";
    const char* start_varlistitem_  = "<listitem>";
    const char* end_varlistitem_    = "</listitem>";
    const char* start_header_       = "<thead>";
    const char* end_header_         = "</thead>\n";
    const char* start_row_          = "<row>";
    const char* end_row_            = "</row>\n";
    const char* start_cell_         = "<entry>";
    const char* end_cell_           = "</entry>";
    const char* funcref_pre_        = "<functionname alt=\"";
    const char* funcref_post_       = "</functionname>";
    const char* classref_pre_       = "<classname alt=\"";
    const char* classref_post_      = "</classname>";
    const char* memberref_pre_      = "<methodname alt=\"";
    const char* memberref_post_     = "</methodname>";
    const char* enumref_pre_        = "<enumname alt=\"";
    const char* enumref_post_       = "</enumname>";
    const char* macroref_pre_       = "<macroname alt=\"";
    const char* macroref_post_      = "</macroname>";
    const char* headerref_pre_      = "<headername alt=\"";
    const char* headerref_post_     = "</headername>";
    const char* conceptref_pre_     = "<conceptname alt=\"";
    const char* conceptref_post_    = "</conceptname>";
    const char* globalref_pre_      = "<globalname alt=\"";
    const char* globalref_post_     = "</globalname>";
    const char* footnote_pre_       = "<footnote><para>";
    const char* footnote_post_      = "</para></footnote>";
    const char* escape_pre_         = "<!--quickbook-escape-prefix-->";
    const char* escape_post_        = "<!--quickbook-escape-postfix-->";
    const char* replaceable_pre_    = "<replaceable>";
    const char* replaceable_post_   = "</replaceable>";

    namespace detail
    {
        std::map<value::tag_type, markup> markups;

        void initialise_markups()
        {
            markup init_markups[] = {
                { block_tags::paragraph, paragraph_pre, paragraph_post },
                { block_tags::blurb, blurb_pre, blurb_post },
                { block_tags::blockquote, blockquote_pre, blockquote_post },
                { block_tags::preformatted, preformatted_pre, preformatted_post },
                { block_tags::warning, warning_pre, warning_post },
                { block_tags::caution, caution_pre, caution_post },
                { block_tags::important, important_pre, important_post },
                { block_tags::note, note_pre, note_post },
                { block_tags::tip, tip_pre, tip_post },
                { block_tags::ordered_list, "<orderedlist>", "</orderedlist>" },
                { block_tags::itemized_list, "<itemizedlist>", "</itemizedlist>" },
                { block_tags::hr, hr_, 0 },
                { phrase_tags::url, url_pre_, url_post_ },
                { phrase_tags::link, link_pre_, link_post_ },
                { phrase_tags::funcref, funcref_pre_, funcref_post_ },
                { phrase_tags::classref, classref_pre_, classref_post_ },
                { phrase_tags::memberref, memberref_pre_, memberref_post_ },
                { phrase_tags::enumref, enumref_pre_, enumref_post_ },
                { phrase_tags::macroref, macroref_pre_, macroref_post_ },
                { phrase_tags::headerref, headerref_pre_, headerref_post_ },
                { phrase_tags::conceptref, conceptref_pre_, conceptref_post_ },
                { phrase_tags::globalref, globalref_pre_, globalref_post_ },
                { phrase_tags::bold, bold_pre_, bold_post_ },
                { phrase_tags::italic, italic_pre_, italic_post_ },
                { phrase_tags::underline, underline_pre_, underline_post_ },
                { phrase_tags::teletype, teletype_pre_, teletype_post_ },
                { phrase_tags::strikethrough, strikethrough_pre_, strikethrough_post_ },
                { phrase_tags::quote, quote_pre_, quote_post_ },
                { phrase_tags::replaceable, replaceable_pre_, replaceable_post_ },
                { phrase_tags::footnote, footnote_pre_, footnote_post_ },
                { phrase_tags::escape, escape_pre_, escape_post_ }
            };

            BOOST_FOREACH(markup m, init_markups)
            {
                markups[m.tag] = m;
            }
        }

        std::ostream& operator<<(std::ostream& out, markup const& m)
        {
            return out<<"{"<<m.tag<<": \""<<m.pre<<"\", \""<<m.post<<"\"}";
        }
    }
}
