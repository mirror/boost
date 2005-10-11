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
#include <functional>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/filter_iterator.hpp>

namespace boost { namespace xpressive { namespace detail
{

template<typename TypeT>
struct tracking_ptr;

template<typename DerivedT>
struct enable_reference_tracking;

///////////////////////////////////////////////////////////////////////////////
// weak_iterator
//  steps through a set of weak_ptr, converts to shared_ptrs on the fly and
//  removes from the set the weak_ptrs that have expired.
template<typename DerivedT>
struct weak_iterator
  : boost::iterator_facade
    <
        weak_iterator<DerivedT>
      , boost::shared_ptr<DerivedT>
      , std::forward_iterator_tag
      , boost::shared_ptr<DerivedT> const &
    >
{
    typedef std::set<boost::weak_ptr<DerivedT> > set_type;
    typedef typename set_type::iterator base_iterator;

    weak_iterator()
      : cur_()
      , iter_()
      , set_(0)
    {
    }

    weak_iterator(base_iterator iter, set_type *set)
      : cur_()
      , iter_(iter)
      , set_(set)
    {
        this->satisfy_();
    }

private:
    friend class boost::iterator_core_access;

    boost::shared_ptr<DerivedT> const &dereference() const
    {
        return this->cur_;
    }

    void increment()
    {
        ++this->iter_;
        this->satisfy_();
    }

    bool equal(weak_iterator const &that) const
    {
        return this->iter_ == that.iter_;
    }

    void satisfy_()
    {
        while(this->iter_ != this->set_->end())
        {
            this->cur_ = this->iter_->lock();
            if(this->cur_)
                return;
            base_iterator tmp = this->iter_++;
            this->set_->erase(tmp);
        }
        this->cur_.reset();
    }

    boost::shared_ptr<DerivedT> cur_;
    base_iterator iter_;
    set_type *set_;
};

///////////////////////////////////////////////////////////////////////////////
// reference_deleter
//
template<typename DerivedT>
struct reference_deleter
{
    void operator ()(void *pv) const
    {
        typedef enable_reference_tracking<DerivedT> impl_type;
        impl_type *pimpl = static_cast<impl_type *>(pv);
        pimpl->refs_.clear();
    }
};

///////////////////////////////////////////////////////////////////////////////
// filter_self
//  for use with a filter_iterator to filter a node out of a list of dependencies
template<typename DerivedT>
struct filter_self
  : std::unary_function<boost::shared_ptr<DerivedT>, bool>
{
    filter_self(enable_reference_tracking<DerivedT> *self)
      : self_(self)
    {
    }

    bool operator() (boost::shared_ptr<DerivedT> const &that) const
    {
        return this->self_ != that.get();
    }

private:
    enable_reference_tracking<DerivedT> *self_;
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
    typedef enable_reference_tracking<DerivedT> this_type;
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

    void track_reference(shared_ptr<DerivedT> const &that)
    {
        // avoid some unbounded memory growth in certain circumstances by
        // opportunistically removing stale dependencies from "that"
        that->purge_stale_deps_();
        // add "that" as a reference
        this->refs_.insert(that);
        // also inherit that's references
        this->refs_.insert(that->refs_.begin(), that->refs_.end());
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
      : refs_()
      , deps_()
    {
        this->operator =(that);
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
    friend struct reference_deleter<DerivedT>;

    DerivedT &derived_()
    {
        return *static_cast<DerivedT *>(this);
    }

    bool has_deps_() const
    {
        return !this->deps_.empty();
    }

    shared_ptr<void> get_ref_deleter_()
    {
        return shared_ptr<void>(static_cast<void*>(this), reference_deleter<DerivedT>());
    }

    void update_references_()
    {
        typename references_type::iterator cur = this->refs_.begin();
        typename references_type::iterator end = this->refs_.end();
        for(; cur != end; ++cur)
        {
            if(this != cur->get()) // not necessary, but avoids a call to shared_from_this()
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
            weak_iterator<DerivedT> cur(this->deps_.begin(), &this->deps_);
            weak_iterator<DerivedT> end(this->deps_.end(), &this->deps_);

            for(; cur != end; ++cur)
            {
                (*cur)->track_reference(this->shared_from_this());
            }
        }
    }

    void track_dependency_(shared_ptr<DerivedT> const &dep)
    {
        if(this != dep.get()) // never add ourself as a dependency
        {
            // add dep as a dependency
            this->deps_.insert(dep);

            filter_self<DerivedT> not_self(this);
            weak_iterator<DerivedT> begin(dep->deps_.begin(), &dep->deps_);
            weak_iterator<DerivedT> end(dep->deps_.end(), &dep->deps_);

            // also inherit dep's dependencies
            this->deps_.insert(
                boost::make_filter_iterator(not_self, begin, end)
              , boost::make_filter_iterator(not_self, end, end)
            );
        }
    }

    void purge_stale_deps_()
    {
        weak_iterator<DerivedT> cur(this->deps_.begin(), &this->deps_);
        weak_iterator<DerivedT> end(this->deps_.end(), &this->deps_);

        for(; cur != end; ++cur)
            ;
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
    mutable shared_ptr<void> refs_;
};

}}} // namespace boost::xpressive::detail

#endif
