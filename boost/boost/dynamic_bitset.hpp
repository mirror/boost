// (C) Copyright Chuck Allison and Jeremy Siek 2001, 2002. 
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

#ifndef BOOST_DYNAMIC_BITSET_HPP
#define BOOST_DYNAMIC_BITSET_HPP

#include <cassert>
#include <string>
#include <iosfwd>
#include <cstring>             // for memset, memcpy, memcmp, etc.
#include <stdexcept>           // for std::domain_error
#include <algorithm>           // for std::swap, std::min, std::copy, std::fill

#if defined(__GNUC__) && !defined(__SGI_STL_PORT)
#include <ctype.h>
#else
#include <cctype>               // for isspace
#endif

#include <vector>

#include <boost/dynamic_bitset_fwd.hpp>

#ifdef __GNUC__ // this isn't right... what's the right way to detect?
#define BOOST_OLD_IOSTREAMS
#endif

namespace boost {

  namespace detail {

    // Forward references
    template <typename BlockInputIterator>
    std::size_t initial_num_blocks(BlockInputIterator first,
                                   BlockInputIterator last,
                                   std::input_iterator_tag);
    template <typename BlockForwardIterator>
    std::size_t initial_num_blocks(BlockForwardIterator first,
                                   BlockForwardIterator last,
                                   std::forward_iterator_tag);

    // The following 2 classes make sure that the bitset
    // gets allocated in an exception safe manner
    template <typename Allocator>
    class dynamic_bitset_alloc_base {
    public:
      dynamic_bitset_alloc_base(const Allocator& alloc)
        : m_alloc(alloc) { }
    protected:
      Allocator m_alloc;
    };
    template <typename Block, typename Allocator>
    class dynamic_bitset_base : public dynamic_bitset_alloc_base<Allocator> {
      typedef std::size_t size_type;
      enum { block_size = CHAR_BIT * sizeof(Block) };
    public:
      dynamic_bitset_base()
        : m_bits(0), m_num_bits(0), m_num_blocks(0) { }

      dynamic_bitset_base(size_type num_bits, const Allocator& alloc)
        : dynamic_bitset_alloc_base<Allocator>(alloc),
          m_bits(dynamic_bitset_alloc_base<Allocator>::
                 m_alloc.allocate(num_blocks(num_bits))),
          m_num_bits(num_bits),
          m_num_blocks(num_blocks(num_bits))
      {
        using namespace std;
        memset(m_bits, 0, m_num_blocks * sizeof(Block));
      }
      ~dynamic_bitset_base() {
        if (m_bits)
          this->m_alloc.deallocate(m_bits, m_num_blocks);
      }
    protected:
      Block* m_bits;
      size_type m_num_bits;
      size_type m_num_blocks;

      static Block word(size_type bit) { return bit / block_size; }
      static Block offset(size_type bit) 
        { return block_size - bit % block_size - 1;}
      static Block mask1(size_type bit) { return Block(1) << offset(bit); }
      static Block mask0(size_type bit) { return ~(Block(1) << offset(bit)); }
      static size_type num_blocks(size_type num_bits) 
        { return (num_bits + block_size - 1) / block_size; }
    };

  } // namespace detail

template <typename Block, typename Allocator>
class dynamic_bitset : private detail::dynamic_bitset_base<Block, Allocator>
{
  // Portability note: member function templates are defined inside
  // this class definition to avoid problems with VC++. Similarly,
  // with the member functions of the nested class.
public:
    typedef Block block_type;
    typedef std::size_t size_type;
    enum { block_size = CHAR_BIT * sizeof(Block) };

    // reference to a bit
    class reference
    {
        friend class dynamic_bitset;
        dynamic_bitset* bs;
        size_type bit;
        reference(); // intentionally not implemented 
        reference(dynamic_bitset& bs_, size_type bit_) : bs(&bs_), bit(bit_){ }
    public:
        reference& operator=(bool value)          // for b[i] = x
        {
            if (value)
                bs->set(bit);
            else
                bs->reset(bit);
            return *this;       
        }
        reference& operator|=(bool value)         // for b[i] |= x
        {
            if (value)
                bs->set(bit);
            return *this;       
        }
        reference& operator&=(bool value)         // for b[i] &= x
        {
            if (! (value && bs->test(bit)))
                bs->reset(bit);
            return *this;       
        }
        reference& operator^=(bool value)         // for b[i] ^= x
        {
            bs->set(bit, bs->test(bit) ^ value);
            return *this;       
        }
        reference& operator-=(bool value)         // for b[i] -= x
        {
            if (!value)
                bs->reset(bit);
            return *this;       
        }
        reference& operator=(const reference& j)  // for b[i] = b[j]
        {
            if (j.bs->test(j.bit))
                bs->set(bit);
            else
                bs->reset(bit);
            return *this;           
        }
        reference& operator|=(const reference& j) // for b[i] |= b[j]
        {
            if (j.bs->test(j.bit))
                bs->set(bit);
            return *this;           
        }
        reference& operator&=(const reference& j) // for b[i] &= b[j]
        {
            if (! (j.bs->test(j.bit) && bs->test(bit)))
                bs->reset(bit);
            return *this;           
        }
        reference& operator^=(const reference& j) // for b[i] ^= b[j]
        {
            bs->set(bit, bs->test(bit) ^ j.bs->test(j.bit));
            return *this;           
        }
        reference& operator-=(const reference& j) // for b[i] -= b[j]
        {
            if (!j.bs->test(j.bit))
                bs->reset(bit);
            return *this;           
        }
        bool operator~() const                    // flips the bit
        {
            return ! bs->test(bit);         
        }
        operator bool() const                     // for x = b[i]
        {
            return bs->test(bit);
        }
        reference& flip()                         // for b[i].flip();
        {
            bs->flip(bit);
            return *this;           
        }
    };
    typedef bool const_reference;

    // constructors, etc.
    explicit
    dynamic_bitset(const Allocator& alloc = Allocator());

    explicit
    dynamic_bitset(size_type num_bits, unsigned long value = 0,
               const Allocator& alloc = Allocator());

    // from string
#ifdef BOOST_OLD_IOSTREAMS
    explicit
    dynamic_bitset(const std::string& s,
               std::string::size_type pos = 0, 
               std::string::size_type n = std::string::npos,
               const Allocator& alloc = Allocator())
        : detail::dynamic_bitset_base<Block, Allocator>
            (std::min(n, s.size() - pos), alloc)
#else
    template <typename CharT, typename Traits, typename Alloc>
    explicit
    dynamic_bitset(const std::basic_string<CharT, Traits, Alloc>& s, 
        typename std::basic_string<CharT, Traits, Alloc>::size_type pos = 0, 
        typename std::basic_string<CharT, Traits, Alloc>::size_type n 
            = std::basic_string<CharT, Traits, Alloc>::npos,
        const Allocator& alloc = Allocator())
        : detail::dynamic_bitset_base<Block, Allocator>
            (std::min(n, s.size() - pos), alloc)
#endif
    {
        // Locate sub string
        if (pos > s.length())
            throw std::out_of_range("invalid argument: pos > s.length(), dynamic_bitset::dynamic_bitset(const std::string&,...)");
        from_string(s, pos, std::min(n, s.size() - pos));   
    }

    // The first bit in *first is the least significant bit, and the
    // last bit in the block just before *last is the most significant bit.
    template <typename BlockInputIterator>
    dynamic_bitset(BlockInputIterator first, BlockInputIterator last,
               const Allocator& alloc = Allocator())
        : detail::dynamic_bitset_base<Block, Allocator>
            (detail::initial_num_blocks(first, last, 
      typename std::iterator_traits<BlockInputIterator>::iterator_category()) 
            * block_size, alloc)           
    {
        if (first != last) {
            if (this->m_num_bits == 0) { // dealing with input iterators
                this->append(first, last);
            } else {
                // dealing with forward iterators, memory has been allocated
                for (std::size_t i = 0; first != last; ++first, ++i)
                    set_block_(i, *first);
            }
        }   
    }


    // copy constructor
    dynamic_bitset(const dynamic_bitset& b);

    void swap(dynamic_bitset& b);

    dynamic_bitset& operator=(const dynamic_bitset& b);

    // size changing operations
    void resize(size_type num_bits, bool value = false);
    void clear();
    void push_back(bool bit);
    void append(Block block);

    template <typename BlockInputIterator>
    void append(BlockInputIterator first, BlockInputIterator last)
    {
        if (first != last) {
            typename std::iterator_traits<BlockInputIterator>::iterator_category cat;
            std::size_t nblocks = detail::initial_num_blocks(first, last, cat);
            if (nblocks == 0) { // dealing with input iterators
                for (; first != last; ++first)
                    append(*first);
            } else { // dealing with forward iterators
                if (size() % block_size == 0) {
                    std::size_t old_nblocks = this->m_num_blocks;
                    resize(size() + nblocks * block_size);
                    for (std::size_t i = old_nblocks; first != last; ++first)
                        set_block_(i++, *first);
                } else {
                    // probably should optimize this,
                    // but I'm sick of bit twiddling
                    for (; first != last; ++first)
                        append(*first);
                }
            }
        }       
    }


    // bitset operations
    dynamic_bitset& operator&=(const dynamic_bitset& b);
    dynamic_bitset& operator|=(const dynamic_bitset& b);
    dynamic_bitset& operator^=(const dynamic_bitset& b);
    dynamic_bitset& operator-=(const dynamic_bitset& b);
    dynamic_bitset& operator<<=(size_type n);
    dynamic_bitset& operator>>=(size_type n);
    dynamic_bitset operator<<(size_type n) const;
    dynamic_bitset operator>>(size_type n) const;

    // basic bit operations
    dynamic_bitset& set(size_type n, bool val = true);
    dynamic_bitset& set();
    dynamic_bitset& reset(size_type n);
    dynamic_bitset& reset();
    dynamic_bitset& flip(size_type n);
    dynamic_bitset& flip();
    bool test(size_type n) const;
    bool any() const;
    bool none() const;
    dynamic_bitset operator~() const;
    size_type count() const;

    // subscript
    reference operator[](size_type pos) { return reference(*this, pos); }
    bool operator[](size_type pos) const { return test(pos); }

    unsigned long to_ulong() const;
  
    size_type size() const;

    bool is_subset_of(const dynamic_bitset& a) const;
    bool is_proper_subset_of(const dynamic_bitset& a) const;

    // lexicographical comparison
    template <typename B, typename A>
    friend bool operator==(const dynamic_bitset<B, A>& a, 
                           const dynamic_bitset<B, A>& b);
    template <typename B, typename A>
    friend bool operator<(const dynamic_bitset<B, A>& a, 
                          const dynamic_bitset<B, A>& b);
    template <typename B, typename A>
    friend bool operator>(const dynamic_bitset<B, A>& a, 
                          const dynamic_bitset<B, A>& b);

    template <typename B, typename A, typename BlockOutputIterator>
    friend void to_block_range(const dynamic_bitset<B, A>& b, 
                               BlockOutputIterator result);

    template <typename B, typename A, typename CharT, typename Alloc>
    friend void 
    dump_to_string(const dynamic_bitset<B, A>& b, 
                   std::basic_string<CharT, Alloc>& s);
private:

    void cleanup();
    void set_(size_type bit);
    bool set_(size_type bit, bool val);
    void reset_(size_type bit);
    bool test_(size_type bit) const;
    void set_block_(size_type blocknum, Block b);
  
public:// would be protected if friends were more portable

    // This is templated on the whole String instead of just CharT,
    // Traits, Alloc to avoid compiler bugs.
    template <typename String>
    void from_string(const String& s, typename String::size_type pos,
                     typename String::size_type rlen)
    {
        // Assumes string contains only 0's and 1's
        for (size_type i = 0; i < rlen; ++i) {
            if (s[pos + this->m_num_bits - i - 1] == '1')
                set_(i);
            else if (s[pos + this->m_num_bits - i - 1] != '0')
                throw std::invalid_argument("invalid argument, characters in s must be 0 or 1, dynamic_bitset::dynamic_bitset(const std::string&,...)");
        }       
    }

    template <typename BlockIterator>
    void from_block_range(BlockIterator first, BlockIterator last)
    {
        // PRE: distance(first, last) == size() / block_size
        for (size_type i = 0; first != last; ++first, ++i)
            this->m_bits[i] = *first;
    }
};

// Global Functions:

// comparison
template <typename Block, typename Allocator>
bool operator!=(const dynamic_bitset<Block, Allocator>& a, 
                const dynamic_bitset<Block, Allocator>& b);

template <typename Block, typename Allocator>
bool operator<=(const dynamic_bitset<Block, Allocator>& a, 
                const dynamic_bitset<Block, Allocator>& b);

template <typename Block, typename Allocator>
bool operator>(const dynamic_bitset<Block, Allocator>& a, 
               const dynamic_bitset<Block, Allocator>& b);

template <typename Block, typename Allocator>
bool operator>=(const dynamic_bitset<Block, Allocator>& a, 
                const dynamic_bitset<Block, Allocator>& b);

// stream operators
#ifdef BOOST_OLD_IOSTREAMS
template <typename Block, typename Allocator>
std::ostream& operator<<(std::ostream& os, 
                         const dynamic_bitset<Block, Allocator>& b);

template <typename Block, typename Allocator>
std::istream& operator>>(std::istream& is, dynamic_bitset<Block,Allocator>& b);
#else
template <typename CharT, typename Traits, typename Block, typename Allocator>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, 
           const dynamic_bitset<Block, Allocator>& b);

template <typename CharT, typename Traits, typename Block, typename Allocator>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, 
           dynamic_bitset<Block, Allocator>& b);
#endif

// bitset operations
template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator&(const dynamic_bitset<Block, Allocator>& b1, 
          const dynamic_bitset<Block, Allocator>& b2);

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator|(const dynamic_bitset<Block, Allocator>& b1, 
          const dynamic_bitset<Block, Allocator>& b2);

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator^(const dynamic_bitset<Block, Allocator>& b1,
          const dynamic_bitset<Block, Allocator>& b2);

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator-(const dynamic_bitset<Block, Allocator>& b1,
          const dynamic_bitset<Block, Allocator>& b2);


template <typename Block, typename Allocator, typename CharT, typename Alloc>
void 
to_string(const dynamic_bitset<Block, Allocator>& b, 
          std::basic_string<CharT, Alloc>& s);

template <typename Block, typename Allocator, typename BlockOutputIterator>
void
to_block_range(const dynamic_bitset<Block, Allocator>& b, 
               BlockOutputIterator result);

//=============================================================================
// dynamic_bitset implementation

#ifdef BOOST_OLD_IOSTREAMS
template <typename Block, typename Allocator>
inline std::ostream&
operator<<(std::ostream& os, 
           const typename dynamic_bitset<Block, Allocator>::reference& br)
{
    return os << (bool)br;
}
#else
template <typename CharT, typename Traits, typename Block, typename Allocator>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, 
           const typename dynamic_bitset<Block, Allocator>::reference& br)
{
    return os << (bool)br;
}
#endif

//-----------------------------------------------------------------------------
// constructors, etc.

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>::dynamic_bitset(const Allocator& alloc)
  : detail::dynamic_bitset_base<Block, Allocator>(0, alloc) { }

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>::
dynamic_bitset(size_type num_bits, unsigned long value, const Allocator& alloc)
  : detail::dynamic_bitset_base<Block, Allocator>(num_bits, alloc)
{
  const size_type M = std::min(sizeof(unsigned long) * CHAR_BIT, num_bits);
  for(size_type i = 0; i < M; ++i, value >>= 1)
    if ( value & 0x1 )
      set_(i);
}

namespace detail {

  template <typename BlockInputIterator>
  std::size_t initial_num_blocks(BlockInputIterator first,
                                 BlockInputIterator last,
                                 std::input_iterator_tag)
  {
    return 0;
  }

  template <typename BlockForwardIterator>
  std::size_t initial_num_blocks(BlockForwardIterator first,
                                 BlockForwardIterator last,
                                 std::forward_iterator_tag)
  {
    std::size_t n = 0;
    while (first != last)
      ++first, ++n;
    return n;
  }

} // namespace detail


// copy constructor
template <typename Block, typename Allocator>
inline dynamic_bitset<Block, Allocator>::
dynamic_bitset(const dynamic_bitset& b)
  : detail::dynamic_bitset_base<Block, Allocator>(b.size(), b.m_alloc)
{
    using namespace std;
    memcpy(this->m_bits, b.m_bits, this->m_num_blocks * sizeof(Block));
}

template <typename Block, typename Allocator>
inline void dynamic_bitset<Block, Allocator>::
swap(dynamic_bitset<Block, Allocator>& b)
{
    std::swap(this->m_bits, b.m_bits);
    std::swap(this->m_num_bits, b.m_num_bits);
    std::swap(this->m_num_blocks, b.m_num_blocks);
    std::swap(this->m_alloc, b.m_alloc);
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>& dynamic_bitset<Block, Allocator>::
operator=(const dynamic_bitset<Block, Allocator>& b)
{
    dynamic_bitset<Block, Allocator> tmp(b);
    this->swap(tmp);
    return *this;
}

//-----------------------------------------------------------------------------
// size changing operations

template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
resize(size_type num_bits, bool value)
{
  if (num_bits == size())
    return;
  size_type new_nblocks = this->num_blocks(num_bits);
  Block* d = this->m_alloc.allocate(new_nblocks);
  if (num_bits < size()) { // shrink
    std::copy(this->m_bits, this->m_bits + new_nblocks, d);
    std::swap(d, this->m_bits);
    this->m_alloc.deallocate(d, this->m_num_blocks);
  } else { // grow
    std::copy(this->m_bits, this->m_bits + this->m_num_blocks, d);
    Block val = value? ~static_cast<Block>(0) : static_cast<Block>(0);
    std::fill(d + this->m_num_blocks, d + new_nblocks, val);
    std::swap(d, this->m_bits);
    for (std::size_t i = this->m_num_bits;
         i < this->m_num_blocks * block_size; ++i)
      set_(i, value);
    if (d != 0)
      this->m_alloc.deallocate(d, this->m_num_blocks);
  }
  this->m_num_bits = num_bits;
  this->m_num_blocks = this->num_blocks(num_bits);
  cleanup();
}

template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
clear()
{
  if (this->m_bits != 0) {
    this->m_alloc.deallocate(this->m_bits, this->m_num_blocks);
    this->m_bits = 0;
    this->m_num_bits = 0;
    this->m_num_blocks = 0;
  }
}


template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
push_back(bool bit)
{
  this->resize(this->size() + 1);
  set_(this->size() - 1, bit);
}

template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
append(Block value)
{
  std::size_t old_size = size();
  resize(old_size + block_size);
  if (size() % block_size == 0)
    set_block_(this->m_num_blocks - 1, value);
  else {
    for (std::size_t i = old_size; i < size(); ++i, value >>= 1)
      set_(i, value & 1);
  }
}


//-----------------------------------------------------------------------------
// bitset operations
template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator&=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < this->m_num_blocks; ++i)
        this->m_bits[i] &= rhs.m_bits[i];
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator|=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < this->m_num_blocks; ++i)
        this->m_bits[i] |= rhs.m_bits[i];
    cleanup();
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator^=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < this->m_num_blocks; ++i)
        this->m_bits[i] ^= rhs.m_bits[i];
    cleanup();
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator-=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < this->m_num_blocks; ++i)
        this->m_bits[i] = this->m_bits[i] & ~rhs.m_bits[i];
    cleanup();
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator<<=(size_type n)
{
    if (n >= this->m_num_bits)
        reset();
    else
    {
        size_type i;
        for (i = this->m_num_bits - 1; i > n; --i)
            set_(i,test_(i-n));
        if (i == n) // careful, unsigned can't go negative!
            set_(i,test_(i-n));
        for (i = 0; i < n; ++i)
            reset_(i);
    }
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator>>=(size_type n)
{
    if (n >= this->m_num_bits)
        reset();
    else
    {
        size_type i;
        for (i = 0; i < this->m_num_bits - n; ++i)
            set_(i,test_(i+n));
        for (i = this->m_num_bits - n; i < this->m_num_bits; ++i)
            reset_(i);
    }
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
dynamic_bitset<Block, Allocator>::operator<<(size_type n) const
{
    dynamic_bitset r(*this);
    return r <<= n;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
dynamic_bitset<Block, Allocator>::operator>>(size_type n) const
{
    dynamic_bitset r(*this);
    return r >>= n;
}


//-----------------------------------------------------------------------------
// basic bit operations

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::set(size_type pos, bool val)
{
    if (pos >= this->m_num_bits)
        throw std::out_of_range("invalid position, dynamic_bitset::set(size_type, bool)");
    set_(pos, val);
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::set()
{
  if (this->m_num_bits > 0) {
    using namespace std;
    memset(this->m_bits, ~0u, this->m_num_blocks * sizeof(this->m_bits[0]));
    cleanup();
  }
  return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::reset(size_type pos)
{
    if (pos >= this->m_num_bits)
        throw std::out_of_range("invalid position, dynamic_bitset::reset(size_type, bool)");
    reset_(pos);
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::reset()
{
  if (this->m_num_bits > 0) {
    using namespace std;
    memset(this->m_bits, 0, this->m_num_blocks * sizeof(this->m_bits[0]));
  }
  return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::flip(size_type pos)
{
    if (pos >= this->m_num_bits)
        throw std::out_of_range("invalid position, dynamic_bitset::toggle(size_type)");
    this->m_bits[this->word(pos)] ^= this->mask1(pos);
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::flip()
{
    for (size_type i = 0; i < this->m_num_blocks; ++i)
        this->m_bits[i] = ~this->m_bits[i];
    cleanup();
    return *this;
}

template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::test(size_type pos) const
{
    if (pos >= this->m_num_bits)
        throw std::out_of_range("invalid position, dynamic_bitset::test(size_type)");
    return test_(pos);
}

template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::any() const
{
    for (size_type i = 0; i < this->m_num_blocks; ++i)
        if (this->m_bits[i])
            return 1;
    return 0;
}

template <typename Block, typename Allocator>
inline bool dynamic_bitset<Block, Allocator>::none() const
{
    return !any();
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
dynamic_bitset<Block, Allocator>::operator~() const
{
    dynamic_bitset b(*this);
    b.flip();
    return b;
}

template <typename Block, typename Allocator>
typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::count() const
{
    size_type sum = 0;
    for (size_type i = 0; i != this->m_num_bits; ++i)
        if (test_(i))
            ++sum;
    return sum;
}

//-----------------------------------------------------------------------------
// conversions

// take as ref param instead?
template <typename Block, typename Allocator, typename CharT, typename Alloc>
void 
to_string(const dynamic_bitset<Block, Allocator>& b, 
          std::basic_string<CharT, Alloc>& s)
{
    s.assign(b.size(), '0');
    for (std::size_t i = 0; i < b.size(); ++i)
        if (b.test(i))
            s[b.size() - 1 - i] = '1';
}

template <typename Block, typename Allocator, typename CharT, typename Alloc>
void 
dump_to_string(const dynamic_bitset<Block, Allocator>& b, 
               std::basic_string<CharT, Alloc>& s)
{
    std::size_t block_size = dynamic_bitset<Block, Allocator>::block_size;
    std::size_t len = b.m_num_blocks * block_size;
    s.assign(len, '0');
    for (std::size_t i = 0; i != len; ++i)
        if (b.test_(i))
            s[len - 1 - i] = '1';
}

template <typename Block, typename Allocator, typename BlockOutputIterator>
void
to_block_range(const dynamic_bitset<Block, Allocator>& b, 
               BlockOutputIterator result)
{
  std::copy(m.m_bits, m.m_num_bits, result);
}

template <typename Block, typename Allocator>
unsigned long dynamic_bitset<Block, Allocator>::
to_ulong() const 
{
  const std::overflow_error
    overflow("boost::bit_set::operator unsigned long()");

  if (this->m_num_blocks == 0)
    return 0;
  
  if (sizeof(Block) >= sizeof(unsigned long)) {
    for (size_type i = 1; i < this->m_num_blocks; ++i)
      if (this->m_bits[i])
        throw overflow;
    const Block mask = static_cast<Block>(static_cast<unsigned long>(-1));
    if (this->m_bits[0] & ~mask)
      throw overflow;
    size_type N = std::min(sizeof(unsigned long) * CHAR_BIT, this->size());
    unsigned long num = 0;
    for (size_type i = 0; i < N; ++i)
      if (this->test(i))
        num |= (1 << i);
    return num;
  }
  else { // sizeof(Block) < sizeof(unsigned long).
    const size_type nwords =
      (sizeof(unsigned long) + sizeof(Block) - 1) / sizeof(Block);

    size_type min_nwords = nwords;
    if (this->m_num_blocks > nwords) {
      for (size_type i = nwords; i < this->m_num_blocks; ++i)
        if (this->m_bits[i])
          throw overflow;
    }
    else
      min_nwords = this->m_num_blocks;

    unsigned long result = 0;
    size_type N = std::min(sizeof(unsigned long) * CHAR_BIT, this->size());
    for (size_type i = 0; i < N; ++i)
      if (this->test(i))
        result |= (1 << i);
    return result;
  }
}


template <typename Block, typename Allocator>
inline typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::size() const
{
    return this->m_num_bits;
}


template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::
is_subset_of(const dynamic_bitset<Block, Allocator>& a) const
{
    assert(this->size() == a.size());
    for (size_type i = 0; i < this->m_num_blocks; ++i)
        if (this->m_bits[i] & ~a.m_bits[i])
            return false;
    return true;
}

template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::
is_proper_subset_of(const dynamic_bitset<Block, Allocator>& a) const
{
    assert(this->size() == a.size());
    bool proper = false;
    for (size_type i = 0; i < this->m_num_blocks; ++i) {
        Block bt = this->m_bits[i], ba = a.m_bits[i];
        if (ba & ~bt)
            proper = true;
        if (bt & ~ba)
            return false;
    }
    return proper;
}

//-----------------------------------------------------------------------------
// comparison

template <typename Block, typename Allocator>
bool operator==(const dynamic_bitset<Block, Allocator>& a, 
                const dynamic_bitset<Block, Allocator>& b)
{
    using namespace std;
    return (a.m_num_bits == b.m_num_bits) &&
      ((a.m_num_bits == 0 && b.m_num_bits == 0) ||
        !memcmp(a.m_bits, b.m_bits, a.m_num_blocks * sizeof(a.m_bits[0])));
}

template <typename Block, typename Allocator>
inline bool operator!=(const dynamic_bitset<Block, Allocator>& a, 
                       const dynamic_bitset<Block, Allocator>& b)
{
    return !(a == b);
}

template <typename Block, typename Allocator>
bool operator<(const dynamic_bitset<Block, Allocator>& a,
               const dynamic_bitset<Block, Allocator>& b)
{
    assert(a.size() == b.size());
    typedef typename dynamic_bitset<Block, Allocator>::size_type size_type;

    if (a.size() == 0)
      return false;

    // Since we are storing the most significant bit
    // at pos == size() - 1, we need to do the memcmp in reverse.

    // Compare a block at a time
    for (size_type i = a.m_num_blocks - 1; i > 0; --i)
      if (a.m_bits[i] < b.m_bits[i])
        return true;
      else if (a.m_bits[i] > b.m_bits[i])
        return false;

    if (a.m_bits[0] < b.m_bits[0])
      return true;
    else
      return false;
}

template <typename Block, typename Allocator>
inline bool operator<=(const dynamic_bitset<Block, Allocator>& a, 
                       const dynamic_bitset<Block, Allocator>& b)
{
    return !(a > b);
}

template <typename Block, typename Allocator>
inline bool operator>(const dynamic_bitset<Block, Allocator>& a, 
                      const dynamic_bitset<Block, Allocator>& b)
{
    assert(a.size() == b.size());
    typedef typename dynamic_bitset<Block, Allocator>::size_type size_type;

    if (a.size() == 0)
      return false;

    // Since we are storing the most significant bit
    // at pos == size() - 1, we need to do the memcmp in reverse.

    // Compare a block at a time
    for (size_type i = a.m_num_blocks - 1; i > 0; --i)
      if (a.m_bits[i] < b.m_bits[i])
        return false;
      else if (a.m_bits[i] > b.m_bits[i])
        return true;

    if (a.m_bits[0] > b.m_bits[0])
      return true;
    else
      return false;
}

template <typename Block, typename Allocator>
inline bool operator>=(const dynamic_bitset<Block, Allocator>& a, 
                       const dynamic_bitset<Block, Allocator>& b)
{
    return !(a < b);
}

//-----------------------------------------------------------------------------
// stream operations

#ifdef BOOST_OLD_IOSTREAMS
template < typename Block, typename Allocator>
std::ostream&
operator<<(std::ostream& os, const dynamic_bitset<Block, Allocator>& b)
{
    std::string s;
    to_string(b, s);
    os << s.c_str();
    return os;
}
#else
template <typename CharT, typename Traits, typename Block, typename Allocator>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os,
           const dynamic_bitset<Block, Allocator>& b)
{
    std::basic_string<CharT, Traits> s;
    to_string(b, s);
    os << s;
    return os;
}
#endif

#ifdef BOOST_OLD_IOSTREAMS
template <typename Block, typename Allocator>
std::istream&
operator>>(std::istream& is, dynamic_bitset<Block, Allocator>& b)
{
    typedef char CharT;
    std::string buf;
    typedef typename std::string::size_type size_type;
    const size_type N = b.size();
    buf.reserve(N);

    // skip whitespace
    if (is.flags() & std::ios::skipws) {
        char c;
        do
            is.get(c);
#if defined(__GNUC__) && !defined(__SGI_STL_PORT)
        while (is && isspace(c));
#else
        while (is && std::isspace(c));
#endif
        if (is)
            is.putback(c);
    }

    size_type i;
    for (i = 0; i < N; ++i)
    {
        CharT c;
        is.get(c);
        if (c == '0' || c == '1')
            buf += c;
        else
        {
            is.putback(c);
            break;
        }
    }

    if (i == 0)
        is.clear(is.rdstate() | std::ios::failbit);
    else
    {
        dynamic_bitset<Block, Allocator> tmp(buf);
        b.swap(tmp);
    }
    return is;
}
#else
template <typename CharT, typename Traits, typename Block, typename Allocator>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& in_stream,
           dynamic_bitset<Block, Allocator>& b)
{
    std::basic_string<CharT,Traits> tmp;
    typedef typename std::basic_string<CharT,Traits>::size_type size_type;
    const size_type N = b.size();
    tmp.reserve(N);

    // skip whitespace
    typename std::basic_istream<CharT, Traits>::sentry sentry(in_stream);
    if (sentry) {
      std::basic_streambuf<CharT, Traits>* read_buf = in_stream.rdbuf();

      for (size_type i = 0; i < N; ++i) {
        typename Traits::int_type c1 = read_buf->sbumpc();
        if (Traits::eq_int_type(c1, Traits::eof())) {
          in_stream.setstate(std::ios_base::eofbit);
          break;
        } else {
          char c2 = Traits::to_char_type(c1);
          char c  = in_stream.narrow(c2, '*');
          
          if (c == '0' || c == '1')
            tmp.push_back(c);
          else if (Traits::eq_int_type(read_buf->sputbackc(c2), Traits::eof()))
          {
            in_stream.setstate(std::ios_base::failbit);
            break;
          }
        }
      } // for
      
      if (tmp.empty()) // did not read in enough bits
        in_stream.setstate(std::ios_base::failbit);
      else
        b.from_string(tmp, static_cast<size_type>(0), N);
    } // if (sentry)
    return in_stream;
}
#endif


//-----------------------------------------------------------------------------
// bitset operations

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator&(const dynamic_bitset<Block, Allocator>& x,
          const dynamic_bitset<Block, Allocator>& y)
{
    dynamic_bitset<Block, Allocator> b(x);
    return b &= y;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator|(const dynamic_bitset<Block, Allocator>& x,
          const dynamic_bitset<Block, Allocator>& y)
{
    dynamic_bitset<Block, Allocator> b(x);
    return b |= y;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator^(const dynamic_bitset<Block, Allocator>& x,
          const dynamic_bitset<Block, Allocator>& y)
{
    dynamic_bitset<Block, Allocator> b(x);
    return b ^= y;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
operator-(const dynamic_bitset<Block, Allocator>& x,
          const dynamic_bitset<Block, Allocator>& y)
{
    dynamic_bitset<Block, Allocator> b(x);
    return b -= y;
}


//-----------------------------------------------------------------------------
// private member functions

template <typename Block, typename Allocator>
inline void dynamic_bitset<Block, Allocator>::
set_(size_type bit)
{
    this->m_bits[this->word(bit)] |= this->mask1(bit);
}

template <typename Block, typename Allocator>
inline void dynamic_bitset<Block, Allocator>::
set_block_(size_type blocknum, Block value)
{
  for (std::size_t i = 0; i < block_size; ++i, value >>= 1)
    if (value & 0x1) {
      size_type bit = blocknum * block_size + i;
      set_(bit);
    }
}

template <typename Block, typename Allocator>
inline void dynamic_bitset<Block, Allocator>::
reset_(size_type b)
{
    this->m_bits[this->word(b)] &= this->mask0(b);
}

template <typename Block, typename Allocator>
inline bool dynamic_bitset<Block, Allocator>::test_(size_type b) const
{
    return (this->m_bits[this->word(b)] & this->mask1(b)) != static_cast<Block>(0);
}

template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::set_(size_type n, bool value)
{
    if (value)
        set_(n);
    else
        reset_(n);
    return value != static_cast<Block>(0);
}

template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::cleanup()
{
    const std::size_t extrabits
      = this->m_num_blocks * block_size - this->m_num_bits;
    const Block clean_mask = ~static_cast<Block>(0) << extrabits;
    // Make sure unused bits don't get set
    if (this->m_num_bits % block_size)
        this->m_bits[this->m_num_blocks - 1] &= clean_mask;
}

} // namespace boost

#endif // BOOST_DYNAMIC_BITSET_HPP
