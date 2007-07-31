// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_PTREE_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>    // Must be the first include, because of config.hpp

#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/any.hpp>
#include <boost/throw_exception.hpp>

#ifdef BOOST_PROPERTY_TREE_DEBUG
#   include <boost/detail/lightweight_mutex.hpp>   // For syncing debug instances counter
#endif

#include <functional>               // for std::less
#include <limits>
#include <list>
#include <sstream>
#include <stdexcept>
#include <utility>                  // for std::pair
#include <vector>
#include <cstdlib>

// Throwing macro to avoid no return warnings portably
#define BOOST_PROPERTY_TREE_THROW(e) { throw_exception(e); std::exit(1); }

namespace boost { namespace property_tree
{

    template<class C, class K, class P, class D, class X>
    class basic_ptree
    {

    private:

        // Internal types
        typedef basic_ptree<C, K, P, D, X> self_type;
    
    public:

        // Basic types
        typedef C key_compare;
        typedef K key_type;
        typedef P path_type;
        typedef D data_type;
        typedef X translator_type;
        typedef std::pair<key_type, self_type> value_type;

    private:

        // Internal types
        typedef std::list<value_type> container_type;

    public:
        
        // Container-related types
        typedef typename container_type::size_type size_type;
        typedef typename container_type::iterator iterator;
        typedef typename container_type::const_iterator const_iterator;
        typedef typename container_type::reverse_iterator reverse_iterator;
        typedef typename container_type::const_reverse_iterator const_reverse_iterator;

    public:
        
        ///////////////////////////////////////////////////////////////////////////
        // Construction & destruction

        basic_ptree();
        explicit basic_ptree(const data_type &data);
        basic_ptree(const self_type &rhs);
        ~basic_ptree();

        ///////////////////////////////////////////////////////////////////////////
        // Iterator access

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        
        ///////////////////////////////////////////////////////////////////////////
        // Data access

        size_type size() const;
        size_type max_size() const;
        bool empty() const;
        
        data_type &data();
        const data_type &data() const;

        value_type &front();
        const value_type &front() const;
        value_type &back();
        const value_type &back() const;

        ///////////////////////////////////////////////////////////////////////////
        // Operators

        self_type &operator =(const self_type &rhs);

        bool operator ==(const self_type &rhs) const;
        bool operator !=(const self_type &rhs) const;

        ///////////////////////////////////////////////////////////////////////////
        // Container operations

        iterator find(const key_type &key);
        const_iterator find(const key_type &key) const;

        size_type count(const key_type &key) const;

        void clear();

        iterator insert(iterator where, const value_type &value);
        template<class It> void insert(iterator where, It first, It last);

        iterator erase(iterator where);
        size_type erase(const key_type &key);
        template<class It> iterator erase(It first, It last);

        iterator push_front(const value_type &value);
        iterator push_back(const value_type &value);

        void pop_front();
        void pop_back();

        void swap(self_type &rhs);

        void reverse();
        template<class SortTr> void sort(SortTr tr);

        ///////////////////////////////////////////////////////////////////////////
        // ptree operations

        // Get child ptree with default separator
        self_type &get_child(const path_type &path);
        const self_type &get_child(const path_type &path) const;
        self_type &get_child(const path_type &path, self_type &default_value);
        const self_type &get_child(const path_type &path, const self_type &default_value) const;
        optional<self_type &> get_child_optional(const path_type &path);
        optional<const self_type &> get_child_optional(const path_type &path) const;

        // Put child ptree with default separator
        self_type &put_child(const path_type &path, const self_type &value, bool do_not_replace = false);

        // Get value from data of ptree
        template<class Type> Type get_value(const translator_type &x = translator_type()) const;
        template<class Type> Type get_value(const Type &default_value, const translator_type &x = translator_type()) const;
        template<class CharType> std::basic_string<CharType> get_value(const CharType *default_value, const translator_type &x = translator_type()) const;
        template<class Type> optional<Type> get_value_optional(const translator_type &x = translator_type()) const;

        // Get value from data of child ptree (default path separator)
        template<class Type> Type get(const path_type &path, const translator_type &x = translator_type()) const;
        template<class Type> Type get(const path_type &path, const Type &default_value, const translator_type &x = translator_type()) const;
        template<class CharType> std::basic_string<CharType> get(const path_type &path, const CharType *default_value, const translator_type &x = translator_type()) const;
        template<class Type> optional<Type> get_optional(const path_type &path, const translator_type &x = translator_type()) const;

        // Put value in data of ptree
        template<class Type> void put_value(const Type &value, const translator_type &x = translator_type());

        // Put value in data of child ptree (default path separator)
        template<class Type> self_type &put(const path_type &path, const Type &value, bool do_not_replace = false, const translator_type &x = translator_type());

    private:

        data_type m_data;
        container_type m_container;

        ////////////////////////////////////////////////////////////////////////////
        // Debugging

#ifdef BOOST_PROPERTY_TREE_DEBUG
    private:
        static boost::detail::lightweight_mutex debug_mutex;    // Mutex for syncing instances counter
        static size_type debug_instances_count;                 // Total number of instances of this ptree class
    public:
        static size_type debug_get_instances_count();
#endif

    };

    ///////////////////////////////////////////////////////////////////////////
    // basic_path class template

    template<class Key>
    class basic_path
    {

    private:

        typedef typename Key::value_type char_type;

    public:

        ///////////////////////////////////////////////////////////////////////
        // Construction & destruction

        basic_path();
        basic_path(const Key &path, char_type separator = char_type('.'));
        basic_path(const char_type *path, char_type separator = char_type('.'));
        
        ///////////////////////////////////////////////////////////////////////
        // Path manipulation

        basic_path<Key> &operator /=(const basic_path<Key> &rhs);
        std::string to_string() const;

        ///////////////////////////////////////////////////////////////////////
        // Operations

        template<class C, class D, class X> 
        basic_ptree<C, Key, basic_path<Key>, D, X> *get_child(basic_ptree<C, Key, basic_path<Key>, D, X> &root) const;
        
        template<class C, class D, class X> 
        const basic_ptree<C, Key, basic_path<Key>, D, X> *get_child(const basic_ptree<C, Key, basic_path<Key>, D, X> &root) const;

        template<class C, class D, class X> 
        basic_ptree<C, Key, basic_path<Key>, D, X> *put_child(basic_ptree<C, Key, basic_path<Key>, D, X> &root, 
                                                              const basic_ptree<C, Key, basic_path<Key>, D, X> &child,
                                                              bool do_not_replace) const;

    private:

        std::vector<Key> m_path;

        ///////////////////////////////////////////////////////////////////////
        // Internal

        template<class RanIt> void parse(RanIt begin, RanIt end, char_type separator);

    };

    ///////////////////////////////////////////////////////////////////////////
    // translator class

    class translator
    {

    public:

        translator();
        translator(const std::locale &loc);

        template<class Ptree, class T> bool get_value(const Ptree &pt, T &value) const;
        template<class Ptree, class T> bool put_value(Ptree &pt, const T &value) const;

    private:

        std::locale m_locale;

    };

    ///////////////////////////////////////////////////////////////////////////
    // exceptions

    // Base error class
    class ptree_error: public std::runtime_error
    {
    
    public:
    
        ptree_error(const std::string &what);
        ~ptree_error() throw();

    };

    // Bad data
    class ptree_bad_data: public ptree_error
    {
    
    public:
    
        template<class T> ptree_bad_data(const std::string &what, const T &data);
        ~ptree_bad_data() throw();
        template<class T> T data();
    
    private:

        boost::any m_data;

    };
    
    // Bad path
    class ptree_bad_path: public ptree_error
    {
    
    public:
    
        template<class T> ptree_bad_path(const std::string &what, const T &path);
        ~ptree_bad_path() throw();
        template<class T> T path();

    private:

        boost::any m_path;

    };

} }

// Include implementations
#include <boost/property_tree/detail/ptree_implementation.hpp>
#include <boost/property_tree/detail/exceptions_implementation.hpp>
#include <boost/property_tree/detail/path_implementation.hpp>
#include <boost/property_tree/detail/translator_implementation.hpp>

#endif
