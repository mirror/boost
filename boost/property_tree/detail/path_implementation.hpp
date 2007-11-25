// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_PATH_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_PATH_IMPLEMENTATION_HPP_INCLUDED

namespace boost { namespace property_tree
{

    namespace detail
    {

        // Path-to-string converter for basic_path
        template<class Key>
        std::string path_to_string(const basic_path<Key> &path)
        {
            return path.to_string();
        }

    }

    ///////////////////////////////////////////////////////////////////////
    // Free functions

    inline path operator /(const path &p1, const path &p2)
    {
        return path(p1) /= p2;
    }

    inline wpath operator /(const wpath &p1, const wpath &p2)
    {
        return wpath(p1) /= p2;
    }

    ///////////////////////////////////////////////////////////////////////
    // Construction & destruction

    template<class Key>
    basic_path<Key>::basic_path()
    {
    }

    template<class Key>
    basic_path<Key>::basic_path(const Key &path, char_type separator)
    {
        parse(path.begin(), path.end(), separator);
    }

    template<class Key>
    basic_path<Key>::basic_path(const char_type *path, char_type separator)
    {
        parse(path, path + std::char_traits<char_type>::length(path), separator);
    }

    ///////////////////////////////////////////////////////////////////////
    // Path manipulation

    template<class Key>
    basic_path<Key> &basic_path<Key>::operator /=(const basic_path<Key> &rhs)
    {
        for (typename std::vector<Key>::const_iterator it = rhs.m_path.begin(); it != rhs.m_path.end(); ++it)
            m_path.push_back(*it);
        return *this;
    }

    template<class Key>
    std::string basic_path<Key>::to_string() const
    {
        std::string s;
        for (typename std::vector<Key>::const_iterator it = m_path.begin(); it != m_path.end(); ++it)
        {
            if (it == m_path.begin())
                s += detail::narrow(it->c_str());
            else
                s += '.', s += detail::narrow(it->c_str());
        }
        return s;
    }

    ///////////////////////////////////////////////////////////////////////
    // Operations

    template<class Key>
    template<class C, class D, class X>
    basic_ptree<C, Key, basic_path<Key>, D, X> *
        basic_path<Key>::get_child(basic_ptree<C, Key, basic_path<Key>, D, X> &root) const
    {
        typedef basic_ptree<C, Key, basic_path<Key>, D, X> ptree_type;
        ptree_type *pt = &root;
        for (typename std::vector<Key>::const_iterator it = m_path.begin(); it != m_path.end(); ++it)
        {
            typename ptree_type::iterator it_child = pt->find(*it);
            if (it_child == pt->end())
                return 0;
            else
                pt = &(it_child->second);
        }
        return pt;
    }

    template<class Key>
    template<class C, class D, class X>
    const basic_ptree<C, Key, basic_path<Key>, D, X> *
        basic_path<Key>::get_child(const basic_ptree<C, Key, basic_path<Key>, D, X> &root) const
    {
        typedef basic_ptree<C, Key, basic_path<Key>, D, X> ptree_type;
        basic_path<Key> *nc_this = const_cast<basic_path<Key> *>(this);
        ptree_type &nc_root = const_cast<ptree_type &>(root);
        return nc_this->get_child(nc_root);
    }

    template<class Key>
    template<class C, class D, class X>
    basic_ptree<C, Key, basic_path<Key>, D, X> *
        basic_path<Key>::put_child(basic_ptree<C, Key, basic_path<Key>, D, X> &root, 
                                   const basic_ptree<C, Key, basic_path<Key>, D, X> &child, 
                                   bool do_not_replace) const
    {
        if (m_path.empty())
        {
            return 0;
        }
        else
        {
            
            typedef basic_ptree<C, Key, basic_path<Key>, D, X> ptree_type;
            typedef typename std::vector<Key>::const_iterator path_iterator;
            
            ptree_type *pt = &root;
            for (path_iterator it = m_path.begin(), end = m_path.end() - 1; it != end; ++it)
            {
                typename ptree_type::iterator it_child = pt->find(*it);
                if (it_child == pt->end())
                    pt = &pt->push_back(typename ptree_type::value_type(*it, empty_ptree<ptree_type>()))->second;
                else
                    pt = &it_child->second;
            }
            
            if (do_not_replace)
                return &pt->push_back(typename ptree_type::value_type(m_path.back(), child))->second;
            else
            {
                typename ptree_type::iterator it = pt->find(m_path.back());
                if (it == pt->end())
                    return &pt->push_back(typename ptree_type::value_type(m_path.back(), child))->second;
                else
                {
                    it->second = child;
                    return &it->second;
                }
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    // Internal

    template<class Key>
    template<class RanIt>
    void basic_path<Key>::parse(RanIt begin, RanIt end, char_type separator)
    {
        m_path.reserve(8);
        while (1)
        {
            RanIt it = std::find(begin, end, separator);
            m_path.push_back(Key(begin, it));
            if (it == end)
                break;
            begin = it + 1;
        }
    }

} }

#endif
