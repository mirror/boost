// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

/// This header contains definition of basic_ptree class template and supporting definitions.

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

#if !defined(BOOST_PROPERTY_TREE_DOXYGEN_INVOKED)
    // Throwing macro to avoid no return warnings portably
#   define BOOST_PROPERTY_TREE_THROW(e) { throw_exception(e); std::exit(1); }
#endif

namespace boost { namespace property_tree
{

    /**
     * Class template implementing property tree.
     *
     * A property tree can have data associated with it
     * along with a sequence of @c (key,basic_ptree) children.
     * Iterators provide bidirectional iterative access into children sequence.
     *
     * @tparam C Key comparison type
     * @tparam K Key type
     * @tparam P Path type
     * @tparam D Data type
     * @tparam X Translator type to use for converting values to and from std::string
     */
    template<class C, class K, class P, class D, class X>
    class basic_ptree
    {
#if defined(BOOST_PROPERTY_TREE_DOXYGEN_INVOKED)
    public:
#endif
        // Internal types
        /**
         * Simpler way to refer to this basic_ptree<C,K,P,D,X> type.
         * Do not use in client code; exposed only for documentation purposes.
         */
        typedef basic_ptree<C, K, P, D, X> self_type; 

    public:
        // Basic types
        typedef C key_compare;
        typedef K key_type;
        typedef P path_type;
        typedef D data_type;
        typedef X translator_type;

        /**
         * Property tree stores a sequence of values of this type.
         *
         * The first element is the key and the second is the child property tree
         * stored at this key.
         */
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

        /** Creates an empty property tree. */
        basic_ptree();

        /**
         * Creates a property_tree with the given data.
         * @param data Data to be assigned to the tree's data field.
         */
        explicit basic_ptree(const data_type &data);

        /**
         * Copy constructor from another property_tree.
         * @param rhs The property tree to be copied.
         */
        basic_ptree(const self_type &rhs);

        /** Destroys the property tree including recusively destoying all children. */
        ~basic_ptree();

        ///////////////////////////////////////////////////////////////////////////
        // Iterator access

        /**
         * Access to the start of the direct children sequence.
         * @return iterator pointing to the first element of the direct children sequence.
         */
        iterator begin();

        /**
         * Const access to the start of the direct children sequence.
         * @return const_iterator pointing to the first element of the direct children sequence.
         */
        const_iterator begin() const;

        /**
         * Access to the end of the direct children sequence.
         * @return iterator pointing just past the end of the direct children sequence.
         */
        iterator end();

        /**
         * Const access to the end of the direct children sequence.
         * @return const_iterator pointing just past the end of the direct children sequence.
         */
        const_iterator end() const;

        /**
         * Access to the start of the reversed direct children sequence.
         * @return reverse_iterator pointing to first element of the reversed direct children sequence.
         */
        reverse_iterator rbegin();

        /**
         * Const access to the start of the reversed direct children sequence.
         * @return const_reverse_iterator pointing to first element of the reversed direct children sequence.
         */
        const_reverse_iterator rbegin() const;

        /**
         * Access to the end of the reverse direct children sequence.
         * @return reverse_iterator pointing just past the end of the reversed direct children sequence.
         */
        reverse_iterator rend();

        /**
         * Const access to the end of the reverse direct children sequence.
         * @return const_reverse_iterator pointing just past the end of the reversed direct children sequence.
         */
        const_reverse_iterator rend() const;

        ///////////////////////////////////////////////////////////////////////////
        // Data access

        /**
         * The size fo the direct children sequnce.
         * @return Number of direct children of the property tree.
         */
        size_type size() const;    

        size_type max_size() const;

        /**
         * Determine whether the children sequence is empty.
         * @note empty() should be prefered over <tt>size() == 0</tt>
         * @retval true There are no direct children.
         * @retval false There is at least one direct child.
         */
        bool empty() const;

        /**
         * Retruns a reference to the data of a property tree.
         * @return Reference to the stored data which can be used to modify the data.
         */
        data_type &data();

        /**
         * Returns a const reference to the data of a property tree.
         * @return Const reference to the stored data.
         */
        const data_type &data() const;

        /**
         * Returns a reference to the first element in the direct children sequence.
         * @pre !(this->empty())
         * @return Reference to the first element in the direct children sequence.
         */
        value_type &front();

        /**
         * Returns a const reference to the first element in the direct children sequence.
         * @pre !(this->empty())
         * @return Const reference to the first element in the direct children sequence.
         */
        const value_type &front() const;

        /**
         * Returns a reference to the last element in the direct children sequence.
         * @pre !(this->empty())
         * @return Reference to the last element in the direct children sequence.
         */
        value_type &back();

        /**
         * Returns a const reference to the last element in the direct children sequence.
         * @pre !(this->empty())
         * @return Const reference to the last element in the direct children sequence.
         */
        const value_type &back() const;

        ///////////////////////////////////////////////////////////////////////////
        // Operators

        /**
         * Replaces current contents of this property tree with another's contents.
         * @param rhs The property tree to assign to this property tree.
         */
        self_type &operator =(const self_type &rhs);

        /**
         * Check for equality of property trees.
         * @retval true If both property trees contain the same data values and equivalent
         *              children sequences, recusively.
         * @retval false Otherwise.
         */
        bool operator ==(const self_type &rhs) const;

        /**
         * Check for inequality of property trees.
         * @return !(*this == rhs)
         */
        bool operator !=(const self_type &rhs) const;

        ///////////////////////////////////////////////////////////////////////////
        // Container operations

        /**
         * Finds direct child stored at specified key.
         *
         * If there is more than one child with the same key, the first one is
         * returned. Time complexity is <tt>O(log n)</tt>. Keys equivalence is
         * tested with a predicate supplied as basic_ptree template parameter.
         * If childe is not found, returns end(). Both const and non-const 
         * versions are provided. To find non-direct children use get_child 
         * function.
         *
         * @param key The key to search in the direct children sequence.
         * @return iterator pointing to the found sequence element, or end()
         *         if no such element exists.
         */
        iterator find(const key_type &key);

        /**
         * Finds direct child stored at specified key.
         *
         * If there is more than one child with the same key, the first one is
         * returned. Time complexity is <tt>O(log n)</tt>. Keys equivalence is
         * tested with a predicate supplied as basic_ptree template parameter.
         * If child is not found, returns end(). Both const and non-const 
         * versions are provided. To find non-direct children use get_child 
         * function.
         *
         * @param key The key to search in the direct children sequence.
         * @return const_iterator pointing to the found sequence element,
         *         or end() if no such element exists.
         */
        const_iterator find(const key_type &key) const;

        /**
         * Count the number of direct children with the given key.
         *
         * Keys equivalence is tested with a predicate supplied as basic_ptree 
         * template parameter.
         * @param key Key to count.
         * @return Number of direct children with given key. 
         */
        size_type count(const key_type &key) const;

        /**
         * Recursively deletes all children of the property tree and clears the
         * data from the property tree.
         */
        void clear();

        /**
         * Inserts a new direct child into the property tree.
         *
         * @param where Iterator pointing at the position where new element will be
         *              inserted. Passing begin() will insert at the front of the
         *              list. Passing end() will insert at the back. Any other
         *              valid iterator will insert in the appropriate place in the
         *              middle.
         * @param value value to be inserted.
         * @return iterator pointing to newly inserted element of the sequence.
         */
        iterator insert(iterator where, const value_type &value);

        /**
         * Inserts a range of direct children into the property tree.
         *
         * Time complexity is <tt>O(m log n)</tt>, where @c m is number of inserted
         * children, @c n is number of existing children.
         *
         * @param where Iterator pointing at the position where new elements will be
         *              inserted. Passing begin() will insert at the front of the
         *              list. Passing end() will insert at the back. Any other
         *              valid iterator will insert in the appropriate place in the
         *              middle.
         * @param first Iterator designating the first element of range to be
         *              inserted.
         * @param last Iterator referring to just past the end of the range to be
         *             inserted.
         */
        template<class It> void insert(iterator where, It first, It last);

        /**
         * Erases a direct child from the property tree.
         *
         * @param where Iterator pointing at the child to be erased from the property tree.
         * @return Iterator pointing to the element after the erased element of the sequence,
         *         or end() if the element erased was the last in the sequence.
         */
        iterator erase(iterator where);

        /**
         * Erases direct children from the property tree matching the given key.
         *
         * @param key Key designating child or children to erase.
         * @return Number of children that were erased.
         */
        size_type erase(const key_type &key);

        /**
         * Erases a range of direct children from the property tree.
         *
         * @param first Iterator designating the first element of range to be
         *              erased.
         * @param last Iterator referring to just past the end of the range to be
         *             erased.
         */
        template<class It> iterator erase(It first, It last);

        /**
         * Inserts a new direct child at the front of the sequence.
         *
         * Equivalent to insert(begin(), value).
         * @param value Value to be inserted.
         * @return Iterator pointing to newly inserted element of the sequence.
         */
        iterator push_front(const value_type &value);

        /**
         * Inserts a new direct child at the back of the sequence.
         *
         * Equivalent to insert(end(), value)
         * @param value Value to be inserted.
         * @return Iterator pointing to newly inserted element of the sequence.
         */
        iterator push_back(const value_type &value);

        /**
         * Erases the first direct child in the sequence.
         *
         * Equivalent to erase(begin()).
         * @pre !(this->empty())
         */
        void pop_front();

        /**
         * Erases the last direct child in the sequence.
         *
         * Equivalent to erase(boost::prior(end())).
         * @pre !(this->empty())
         */
        void pop_back();

        /**
         * Swaps contents of this property tree with the contents of another.
         *
         * Time complexity is <tt>O(1)</tt>.
         * @param rhs Property tree with which to swap.
         */
        void swap(self_type &rhs);

        /** Reverses the order of direct children in the property tree. */
        void reverse();

        /**
         * Sorts direct children of the property tree in ascending order.
         * @param tr The binary predicate used to sort child values of type @c #value_type.
         * @post For each adjacent child of the sequence, @c v1 followed by @c v2,
         *       @c tr(v1,v2) evaluates to true.
         */
        template<class SortTr> void sort(SortTr tr);

        ///////////////////////////////////////////////////////////////////////////
        // ptree operations

        /**
         * Get a reference to the child property tree at the given path.
         *
         * Traverses the tree using the given path and retrieves a child property tree
         * stored there.  This function will retrieve indirect children if the path contains
         * at least one separator.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @throw ptree_bad_path if child property tree cannot be located.
         * @return A reference to the child property tree at the given path relative to this
         *         property tree.
         */
        self_type &get_child(const path_type &path);

        /**
         * Get a const reference to the child property tree at the given path.
         *
         * Traverses the tree using the given path and retrieves a child property tree
         * stored there.  This function will retrieve indirect children if the path contains
         * at least one separator.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @throw ptree_bad_path if child property tree cannot be located.
         * @return A const reference to the child property tree at the given path relative to this
         *         property tree.
         */
        const self_type &get_child(const path_type &path) const;

        /**
         * Get a reference to the child property tree at the given path or a default if none found.
         *
         * Traverses the tree using the given path and retrieves a child property tree
         * stored there.  This function will retrieve indirect children if the path contains
         * at least one separator.  If child isn't found then the @c default_value will be returned.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @param default_value The value to be returned if no child is found at @c path.
         * @return A reference to the child property tree at the given path relative to this
         *         property tree or the @c default_value if that child isn't found
         */
        self_type &get_child(const path_type &path, self_type &default_value);

        /**
         * Get a const reference to the child property tree at the given path or a default if none found.
         *
         * Traverses the tree using the given path and retrieves a child property tree
         * stored there.  This function will retrieve indirect children if the path contains
         * at least one separator.  If child isn't found then the @c default_value will be returned.
         * @note One use of default value is to return a reference to empty property tree if the
         *       required one is not found. In many cases, the subsequent code using the return
         *       value can be then made simpler. @see boost::property_tree::empty_ptree.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @param default_value The value to be returned if no child is found at @c path.
         * @return A const reference to the child property tree at the given path relative to this
         *         property tree or the @c default_value if that child isn't found
         */
        const self_type &get_child(const path_type &path, const self_type &default_value) const;

        /**
         * Get a reference to the child property tree at the given path if it exists.
         *
         * Traverses the tree using the given path and retrieves a child property tree
         * stored there.  This function will retrieve indirect children if the path contains 
         * at least one separator.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @return If the child is found, the function returns boost::optional initialized  with
         *         a reference to it. Otherwise it returns uninitialized boost::optional.
         */
        optional<self_type &> get_child_optional(const path_type &path);

        /**
         * Get a const reference to the child property tree at the given path if it exists.
         *
         * Traverses the tree using the given path and retrieves a child property tree
         * stored there.  This function will retrieve indirect children if the path contains 
         * at least one separator.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @return If the child is found, the function returns boost::optional initialized  with
         *         a const reference to it. Otherwise it returns uninitialized boost::optional.
         */
        optional<const self_type &> get_child_optional(const path_type &path) const;

        /**
         * Traverses the tree using given path, and inserts a new property tree or replaces 
         * existing one.  If any of the intermediate keys specified by path does not exist,
         * it is inserted, with empty data and no children, at the back of existing sequence.
         *
         * For example, if @c path is "key1.key2.key3", the function will find a child designated
         * by "key1.key2" path. This child will be checked for presence of "key3" subkey. If it
         * exists, it will be replaced with the one specified by value parameter. If it does not
         * exist, "key3" will be added at the back of existing sequence (if any). If either
         * "key1" or "key1.key2" do not exist, the function will insert them as well.
         *
         * This function is a complement to @c #get_child. If @c put_child(path,value) was called,
         * @c get_child(path) will return a reference to element inserted/replaced by put_child.
         *
         * @param path Location to place value.  A sequence of keys with zero or more separator
         *             characters.
         * @param value Property tree to be inserted as a child of this property tree.
         * @param do_not_replace If set to true, causes function to always insert a new key,
         *                       even if there already exists key with the same name.
         * @return Reference to the inserted property tree.
         */
        self_type &put_child(const path_type &path, const self_type &value, bool do_not_replace = false);

        /**
         * Extracts value stored in property tree data and translates it to Type using 
         * the given translator.
         * @throw ptree_bad_data If data cannot be translated to an instance of @c Type
         *                       using the given translator_type.
         * @param x Translator to use to extract and convert the contained #data_type to @c Type
         *          using <tt>bool translator_type::get_value(self_type const&, Type&)</tt>.
         * @return The extracted value as an instance of @c Type.
         */
        template<class Type> Type get_value(const translator_type &x = translator_type()) const;

        /**
         * Extracts value stored in property tree data and translates it to Type using the
         * given translator.  If extraction does not succeed then return the given default value.
         * @param default_value The value to be returned if the the given translator cannot 
         *                     extract the data as an instance of @c Type.
         * @param x Translator to use to extract and convert the contained #data_type to @c Type
         *          using <tt>bool translator_type::get_value(self_type const&, Type&)</tt>.
         * @return The extracted value as an instance of @c Type if extraction succeeds.
         *         Otherwise it returns the @c default_value.
         */
        template<class Type> Type get_value(const Type &default_value, const translator_type &x = translator_type()) const;

        /**
         * Extracts value stored in property tree data and translates it to @c std::basic_string<CharType>
         * using the given translator.  If extraction does not succeed then return the given default string.
         * @param default_value The string to be returned if the the given translator cannot
         *                     extract the data as an instance of @c Type.
         * @param x Translator to use to extract and convert the contained #data_type to @c std::basic_string<CharType>
         *          using <tt>bool translator_type::get_value(self_type const&, std::basic_string<CharType>&)</tt>.
         * @return The extracted value as an instance of @c std::basic_string<CharType> if extraction succeeds.
         *         Otherwise it returns the @c default_value.
         */
        template<class CharType> std::basic_string<CharType> get_value(const CharType *default_value, const translator_type &x = translator_type()) const;

        /**
         * Extracts value stored in property tree data and translates it to Type using the
         * given translator.
         * @param default_value The value to be returned if the the given translator cannot 
         *                     extract the data as an instance of @c Type.
         * @param x Translator to use to extract and convert the contained #data_type to @c Type
         *          using <tt>bool translator_type::get_value(self_type const&, Type&)</tt>.
         * @return The extracted value as an instance of @c Type if extraction succeeds.
         *         Otherwise it returns an uninitialized @c boost::optional<Type>.
         */
        template<class Type> optional<Type> get_value_optional(const translator_type &x = translator_type()) const;

        /**
         * Get the property tree value at the given path.
         *
         * Traverses the tree using the given path and retrieves the value stored there.
         * This function will retrieve values of indirect children if the path contains at least
         * one separator.  The value will be converted to an instance of @c Type using the
         * given translator.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @param x Translator to use to extract and convert the contained #data_type to @c Type
         *          using <tt>bool translator_type::get_value(self_type const&, Type&)</tt>.
         * @throw ptree_bad_path if child property tree cannot be located using the given path.
         * @return The child property tree's value at the given path relative to this
         *         property tree.
         */
        template<class Type> Type get(const path_type &path, const translator_type &x = translator_type()) const;

        /**
         * Get the property tree value at the given path or a default if none found.
         *
         * Traverses the tree using the given path and retrieves the value stored there
         * This function will retrieve values of indirect children if the path contains at least
         * one separator.  The value will be converted to an instance of @c Type using the
         * given translator.  If child isn't found then the @c default_value will be returned.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @param default_value The value to be returned if no child is found at @c path
         *                      or translation fails.
         * @param x Translator to use to extract and convert the contained #data_type to @c Type
         *          using <tt>bool translator_type::get_value(self_type const&, Type&)</tt>.
         * @return The child property tree's value at the given path relative to this
         *         property tree or the @c default_value if that child is not found.
         */
        template<class Type> Type get(const path_type &path, const Type &default_value, const translator_type &x = translator_type()) const;

        /**
         * Get the property tree value as @c std::basic_string<CharType> at the given path
         * or a default if none found.
         *
         * Traverses the tree using the given path and retrieves the value stored there
         * This function will retrieve values of indirect children if the path contains at least
         * one separator.  The value will be converted to an instance of 
         * @c std::basic_string<CharType> using the given translator.  If child isn't
         * found then the @c default_value will be returned.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @param default_value The string to be returned if no child is found at @c path
         *                       or translation fails.
         * @param x Translator to use to extract and convert the contained #data_type to @c std::basic_string<CharType>
         *          using <tt>bool translator_type::get_value(self_type const&, std::basic_string<CharType>&)</tt>.
         * @return The child property tree's value as @c std::basic_string<CharType> at 
         *         the given path relative to this property tree or the @c default_value
         *         if that child is not found or translation fails.
         */
        template<class CharType> std::basic_string<CharType> get(const path_type &path, const CharType *default_value, const translator_type &x = translator_type()) const;

        /**
         * Get the property tree value at the given path or an uninitialized 
         * @c boost::optional<Type> if none found.
         *
         * Traverses the tree using the given path and retrieves the value stored there
         * This function will retrieve values of indirect children if the path contains at least
         * one separator.  The value will be converted to an instance of @c Type using the
         * given translator.  If child isn't found then an unitialized @c boost::optional<Type>
         * will be returned.
         * @param path A sequence of keys with zero or more separator characters.
         *             Can indicate indirect children if path contains at least one separator
         *             character.
         * @param x Translator to use to extract and convert the contained #data_type to @c Type
         *          using <tt>bool translator_type::get_value(self_type const&, Type&)</tt>.
         * @return The child property tree's value at the given path relative to this
         *         property tree or an unitialized @c boost::optional<Type> if that child is not
         *        found or translation fails.
         */
        template<class Type> optional<Type> get_optional(const path_type &path, const translator_type &x = translator_type()) const;

        /**
         * Store the given value as the data of this property tree.
         *
         * Translates @c value from @c Type to @c #data_type using the given translator, and stores the
         * result as the data value of this property tree.
         * @throw ptree_bad_data If the given value cannot be translated to @c #data_type.
         * @param value The parameter to store as the data of this property tree.
         * @param x Translator to use to convert @c value to an instance of @c #data_type
         *          using <tt>bool translator_type::put_value(self_type&,Type const&)</tt>.
         */
        template<class Type> void put_value(const Type &value, const translator_type &x = translator_type());

        /**
         * Traverses the tree using given path, and inserts a new value or replaces existing one.
         * If any of the intermediate keys specified by path does not exist, it is inserted,
         * with empty data and no children, at the back of existing sequence.
         *
         * For example, if @c path is "key1.key2.key3", the function will find a child designated
         * by "key1.key2" path. This child will be checked for presence of "key3" subkey. If it
         * exists, it will be replaced with the one specified by value parameter. If it does not
         * exist, "key3" will be added at the back of existing sequence (if any). If either
         * "key1" or "key1.key2" do not exist, the function will insert them as well.
         *
         * This function is a complement to @c #get. If @c put(path,value) was called,
         * @c get(path) will return the value inserted by @c #put.
         *
         * @param path Location to place value.  A sequence of keys with zero or more separator
         *             characters.
         * @param value value to be inserted as the data of a child of this property tree.
         * @param do_not_replace If set to true, causes function to always insert a new key,
         *                       even if there already exists key with the same name.
         * @param x Translator to use to convert @c value to an instance of @c #data_type
         *          using <tt>bool translator_type::put_value(self_type&,Type const&)</tt>.
         * @return Reference to the property tree where the value was inserted.  It is either a
         *         newly inserted property tree or an existing one if it was there prior to 
         *         this call.
         */
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

    /** Class template used to represent a path containing a sequence of Key instances. */
    template<class Key>
    class basic_path
    {
#if defined(BOOST_PROPERTY_TREE_DOXYGEN_INVOKED)
    public:
#endif
        /**
         * Simpler way to refer to the Key::value_type type.
         * Do not use in client code; exposed only for documentation purposes.
         */
        typedef typename Key::value_type char_type;

    public:

        ///////////////////////////////////////////////////////////////////////
        // Construction & destruction

        /** Constructs an empty basic_path<Key> instance */
        basic_path();

        /**
         * Constructs an path using the given path using the given separator to split it.
         * @param path The path to which to initialize the constructed instance.
         * @param separator The separator to use to split the @c path parameter.
         */
        basic_path(const Key &path, char_type separator = char_type('.'));

        /**
         * Constructs an path using the given path using the given separator to split it.
         * @param path The path to which to initialize the constructed instance.  This
         *             path instance must be terminated with char_type('\\0');
         * @param separator The separator to use to split the @c path parameter.
         */
        basic_path(const char_type *path, char_type separator = char_type('.'));

        ///////////////////////////////////////////////////////////////////////
        // Path manipulation

        /**
         * Append the given path to this instance.
         * @param rhs The path to append.
         * @return A reference to this path instance after appending @c rhs.
         */
        basic_path<Key> &operator /=(const basic_path<Key> &rhs);

        /**
         * Convert this path instance to a @c std::string representation.
         * @return A string representation of this path.
         */
        std::string to_string() const;

        ///////////////////////////////////////////////////////////////////////
        // Operations

        /**
         * Extract the child subtree of the given property tree at the location indicated
         * by this path instance.
         * @param root The property tree from which to extract the child subtree.
         * @return Pointer to the child subtree of the input property tree indicated by the
         *         location given by this path instance.  If no child exists at the indicated
         *         location then NULL is returned.
         */
        template<class C, class D, class X> 
        basic_ptree<C, Key, basic_path<Key>, D, X> *get_child(basic_ptree<C, Key, basic_path<Key>, D, X> &root) const;

        /**
         * Extract the child subtree of the given property tree at the location indicated
         * by this path instance.
         * @param root The property tree from which to extract the child subtree.
         * @return Pointer to the constant child subtree of the input property tree indicated by the
         *         location given by this path instance.  If no child exists at the indicated
         *         location then NULL is returned.
         */
        template<class C, class D, class X> 
        const basic_ptree<C, Key, basic_path<Key>, D, X> *get_child(const basic_ptree<C, Key, basic_path<Key>, D, X> &root) const;

        /**
         * Insert or replace in the given property tree at the location indicated by this path
         * instance the second given property tree as a child.
         * @param root The property tree in which to insert or replace the child.
         * @param child The property tree to insert within the tree given by that @c root parameter.
         * @param do_not_replace If set to true, causes function to always insert a new key,
         *                       even if there already exists key with the same name.  Otherwise
         * @return Pointer to the child property tree inserted at the given location
         *         location given by this path instance.  If this path is empty then return NULL.
         */
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
        /** Default construct a translator instance. */
        translator();

        /**
         * Construct a translator instance setting the internal locale state using
         * the given input locale.
         * @param loc The locale to use in this instance.
         */
        translator(const std::locale &loc);

        /**
         * Extract data value from the given property tree and convert it to an 
         * instance of type @c T.
         * @param pt Property tree from which to retrieve the data value.
         * @param[out] value The variable in which to store the retrieved data value.
         * @return @c true If the data value was sucessfully converted and retrieved.
         *         Otherwise return @c false.
         */
        template<class Ptree, class T> bool get_value(const Ptree &pt, T &value) const;

        /**
         * Insert the given value as the data member in the given property tree after
         * converting it to instance of type @c Ptree::data_type.
         * @param pt Property tree in which to insert the given value as data.
         * @param value The value to store as data in the given property tree.
         * @return @c true If the data value was sucessfully converted and retrieved.
         *         Otherwise return @c false.
         */
        template<class Ptree, class T> bool put_value(Ptree &pt, const T &value) const;

    private:

        std::locale m_locale;

    };

    ///////////////////////////////////////////////////////////////////////////
    // exceptions

    /// Base class for all property tree errors. Derives from @c std::runtime_error.
    /// Call member function @c what to get human readable message associated with the error.
    class ptree_error: public std::runtime_error
    {
    public:
        /// Instantiate a ptree_error instance with the given message.
        /// @param what The message to associate with this error.
        ptree_error(const std::string &what);

        ~ptree_error() throw();
    };


    /// Error indicating that translation from given value to the property tree data_type
    /// (or vice versa) failed. Derives from ptree_error.
    class ptree_bad_data: public ptree_error
    {
    public:
        /// Instantiate a ptree_bad_data instance with the given message and data.
        /// @param what The message to associate with this error.
        /// @param data The value associated with this error that was the source of the 
        ///             translation failure.
        template<class T> ptree_bad_data(const std::string &what, const T &data);

        ~ptree_bad_data() throw();

        /// Retrieve the data associated with this error.  This is the source value that 
        /// failed to be translated.
        template<class T> T data();
    private:
        boost::any m_data;
    };


    /// Error indicating that specified path does not exist. Derives from ptree_error.
    class ptree_bad_path: public ptree_error
    {
    public:
        /// Instantiate a ptree_bad_path with the given message and path data.
        /// @param what The message to associate with this error.
        /// @param path The path that could not be found in the property_tree.
        template<class T> ptree_bad_path(const std::string &what, const T &path);

        ~ptree_bad_path() throw();

        /// Retrieve the invalid path.
        template<class T> T path();
    private:
        boost::any m_path;
    };

} }

// Include implementations
#include <boost/property_tree/detail/ptree_implementation.hpp>
// FIXME: There's a very nasty order dependency between exceptions_impl and
// the other two headers on compilers that do really compliant ADL, like
// GCC 4.3.
#include <boost/property_tree/detail/path_implementation.hpp>
#include <boost/property_tree/detail/translator_implementation.hpp>
#include <boost/property_tree/detail/exceptions_implementation.hpp>

#endif
