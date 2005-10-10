///////////////////////////////////////////////////////////////////////////////
// tracking_ptr.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_UTILITY_TRACKING_PTR_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_UTILITY_TRACKING_PTR_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef NDEBUG
# include <iosfwd>
#endif
#include <set>
#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost { namespace xpressive { namespace detail
{

template<typename TypeT>
struct tracking_ptr;

///////////////////////////////////////////////////////////////////////////////
// reference_deleter
//
template<typename DerivedT>
struct reference_deleter
{
    void operator ()(std::set<shared_ptr<DerivedT> > *refs) const
    {
        refs->clear();
    }
};

///////////////////////////////////////////////////////////////////////////////
// enable_reference_tracking
//   inherit from this type to enable reference tracking for a type. You can
//   then use tracking_ptr (below) as a holder for derived objects.
//
template<typename DerivedT>
struct enable_reference_tracking
  : enable_shared_from_this<DerivedT>
{
    typedef std::set<shared_ptr<DerivedT> > references_type;
    typedef std::set<weak_ptr<DerivedT> > dependents_type;

    void tracking_copy(DerivedT const &that)
    {
        this->derived_() = that;
        this->tracking_update();
    }

    // called automatically as a result of a tracking_copy(). Must be called explicitly
    // if you change the references without calling tracking_copy().
    void tracking_update()
    {
        // add "this" as a dependency to all the references
        this->update_references_();
        // notify our dependencies that we have new references
        this->update_dependents_();
    }

    void tracking_clear()
    {
        this->derived_() = DerivedT();
    }

    void track_reference(shared_ptr<DerivedT> const &ref)
    {
        this->refs_.insert(ref);
        // also inherit ref's references
        this->refs_.insert(ref->refs_.begin(), ref->refs_.end());
    }

    //{{AFX_DEBUG
    #ifndef NDEBUG
    friend std::ostream &operator <<(std::ostream &sout, enable_reference_tracking<DerivedT> const &that)
    {
        that.dump_(sout);
        return sout;
    }
    #endif
    //}}AFX_DEBUG

protected:

    enable_reference_tracking()
      : refs_()
      , deps_()
    {
    }

    enable_reference_tracking(enable_reference_tracking<DerivedT> const &that)
      : refs_(that.refs_)
      , deps_()
    {
    }

    enable_reference_tracking<DerivedT> &operator =(enable_reference_tracking<DerivedT> const &that)
    {
        // BUGBUG derived classes will need to do something special to make their
        // assignment operators exception-safe. Can we make this easier?
        references_type(that.refs_).swap(this->refs_);
        return *this;
    }

    void swap(enable_reference_tracking<DerivedT> &that)
    {
        this->refs_.swap(that.refs_);
    }

private:

    friend struct tracking_ptr<DerivedT>;

    DerivedT &derived_()
    {
        return *static_cast<DerivedT *>(this);
    }

    bool has_deps_() const
    {
        return !this->deps_.empty();
    }

    shared_ptr<references_type> get_ref_deleter_()
    {
        return shared_ptr<references_type>(& this->refs_, reference_deleter<DerivedT>());
    }

    void update_references_()
    {
        typename references_type::iterator cur = this->refs_.begin();
        typename references_type::iterator end = this->refs_.end();
        for(; cur != end; ++cur)
        {
            if(this != cur->get())
            {
                // for each reference, add this as a dependency
                (*cur)->track_dependency_(this->shared_from_this());
            }
        }
    }

    void update_dependents_()
    {
        // called whenever this regex object changes (i.e., is assigned to). it walks
        // the list of dependent regexes and updates *their* lists of references,
        // thereby spreading out the reference counting responsibility evenly.
        if(!this->refs_.empty())
        {
            typename dependents_type::iterator cur = this->deps_.begin();
            typename dependents_type::iterator end = this->deps_.end();
            typename dependents_type::iterator tmp;
            while(cur != end)
            {
                if(shared_ptr<DerivedT> dep = cur->lock())
                {
                    dep->track_reference(this->shared_from_this());
                    ++cur;
                }
                else
                {
                    // remove stale dependency
                    tmp = cur++;
                    this->deps_.erase(tmp);
                }
            }
        }
    }

    void track_dependency_(shared_ptr<DerivedT> const &dep)
    {
        if(this != dep.get()) // never add ourself as a dependency
        {
            this->deps_.insert(dep);

            // also inherit dep's dependencies
            // BUGBUG this is O(N log N) because we are doing N individual
            // insert ops. Change to use a filter/transform iterator so we
            // can call the range insert function and get this down to O(N).
            typename dependents_type::iterator cur = dep->deps_.begin();
            typename dependents_type::iterator end = dep->deps_.end();
            typename dependents_type::iterator tmp;
            for(; cur != end; ++cur)
            {
                if(shared_ptr<DerivedT> dep2 = cur->lock())
                {
                    if(this != dep2.get()) // never add ourself as a dependency
                    {
                        this->deps_.insert(dep2);
                    }
                }
                else
                {
                    // remove stale dependency
                    tmp = cur++;
                    dep->deps_.erase(tmp);
                }
            }
        }
    }

    //{{AFX_DEBUG
    #ifndef NDEBUG
    void dump_(std::ostream &sout) const;
    #endif
    //}}AFX_DEBUG

    references_type refs_;
    dependents_type deps_;
};

//{{AFX_DEBUG
#ifndef NDEBUG
///////////////////////////////////////////////////////////////////////////////
// dump_
//
template<typename DerivedT>
inline void enable_reference_tracking<DerivedT>::dump_(std::ostream &sout) const
{
    shared_ptr<DerivedT const> this_ = this->shared_from_this();
    sout << "0x" << (void*)this << " cnt=" << this_.use_count()-1 << " refs={";
    typename references_type::const_iterator cur1 = this->refs_.begin();
    typename references_type::const_iterator end1 = this->refs_.end();
    for(; cur1 != end1; ++cur1)
    {
        sout << "0x" << (void*)&**cur1 << ',';
    }
    sout << "} deps={";
    typename dependents_type::const_iterator cur2 = this->deps_.begin();
    typename dependents_type::const_iterator end2 = this->deps_.end();
    for(; cur2 != end2; ++cur2)
    {
        if(shared_ptr<DerivedT> dep = cur2->lock())
        {
            sout << "0x" << (void*)&*dep << ',';
        }
    }
    sout << '}';
}
#endif
//}}AFX_DEBUG

///////////////////////////////////////////////////////////////////////////////
// tracking_ptr
//   holder for a reference-tracked type. Does cycle-breaking, lazy initialization
//   and copy-on-write. TODO: implement move semantics.
//
template<typename TypeT>
struct tracking_ptr
{
private:
    struct dummy_ { int n_; };
	BOOST_MPL_ASSERT((is_base_and_derived<enable_reference_tracking<TypeT>, TypeT>));

public:

    tracking_ptr()
      : data_()
      , refs_()
    {
    }

    tracking_ptr(tracking_ptr<TypeT> const &that)
      : data_()
      , refs_()
    {
        this->operator =(that);
    }

    tracking_ptr<TypeT> &operator =(tracking_ptr<TypeT> const &that)
    {
        // Note: the copy-and-swap idiom doesn't work here if has_deps_()==true
        // because it invalidates references to the TypeT object.

        if(that)
        {
            if(that.has_deps_() || this->has_deps_())
            {
                this->tracking_copy(*that.data_); // deep copy, forks data if necessary
            }
            else
            {
                this->refs_ = that.refs_; // shallow, copy-on-write
                this->data_ = that.data_;
            }
        }
        else if(*this)
        {
            this->data_->tracking_clear();
        }

        return *this;
    }

    // NOTE: this does *not* do tracking. Can't provide a non-throwing swap that tracks references
    void swap(tracking_ptr<TypeT> &that) // throw()
    {
        this->data_.swap(that.data_);
        this->refs_.swap(that.refs_);
    }

    // deep copy, forces a fork and calls update() to update all the
    // dependents and references.
    void tracking_copy(TypeT const &that)
    {
        this->get_(false)->tracking_copy(that);
    }

    // calling this forces this->data_ to fork.
    shared_ptr<TypeT> const &get() const
    {
        return this->get_(true); // copy == true
    }

    // smart-pointer operators
    operator int dummy_::*() const
    {
        return this->data_ ? &dummy_::n_ : 0;
    }

    bool operator !() const
    {
        return !this->data_;
    }

    // Since this does not un-share the data, it returns a ptr-to-const
    TypeT const *operator ->() const
    {
        return this->data_.get();
    }

    // Since this does not un-share the data, it returns a ref-to-const
    TypeT const &operator *() const
    {
        return *this->data_;
    }

private:

    // calling this forces data_ to fork. if 'copy' is true, then
    // the old data is copied into the fork.
    shared_ptr<TypeT> const &get_(bool copy) const
    {
        if(!*this)
        {
            this->data_.reset(new TypeT);
            this->refs_ = this->data_->get_ref_deleter_();
        }
        else if(!this->unique_())
        {
            BOOST_ASSERT(!this->has_deps_());
            shared_ptr<TypeT> new_data(new TypeT);
            if(copy)
            {
                new_data->tracking_copy(*this->data_);
            }
            this->data_.swap(new_data);
            this->refs_ = this->data_->get_ref_deleter_();
        }

        return this->data_;
    }

    // are we the only holders of this data?
    bool unique_() const
    {
        return this->refs_.unique();
    }

    // does anybody have a dependency on us?
    bool has_deps_() const
    {
        return this->data_ && this->data_->has_deps_();
    }

    // mutable to allow lazy initialization
    mutable shared_ptr<TypeT> data_;
    mutable shared_ptr<std::set<shared_ptr<TypeT> > > refs_;
};

}}} // namespace boost::xpressive::detail

#endif
