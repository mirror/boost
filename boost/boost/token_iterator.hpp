// Boost token_iterator.hpp  -------------------------------------------------//

// Copyright John R. Bandela 2001
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// See http://www.boost.org/libs/tokenizer for documentation.

// Revision History:
// 03 Jul 2003   John Bandela
//      Converted to new iterator adapter



#ifndef BOOST_TOKENIZER_POLICY_JRB070303_HPP_
#define BOOST_TOKENIZER_POLICY_JRB070303_HPP_

#include<boost/iterator/iterator_adaptor.hpp>
#include<boost/token_functions.hpp>
#include<utility>
#include<cassert>


namespace boost {
  
 namespace detail
  {
    template <class Iterator>
    struct token_iterator_category
    {
       typedef iterator_tag<
           readable_iterator_tag
         , typename minimum_category<
               forward_traversal_tag
             , typename traversal_category<Iterator>::type
           >::type 
       > type;
    };

  } 

  template <class TokenizerFunc, class Iterator, class Type>
  class token_iterator
      : public iterator_facade<
            token_iterator<TokenizerFunc, Iterator, Type>
          , Type
          , readable_iterator_tag, typename detail::minimum_category<
               forward_traversal_tag
             , typename traversal_category<Iterator>::type
           >::type 
          , const Type&
        >
  {

      friend class iterator_core_access;

      TokenizerFunc f_;
      Iterator begin_;
      Iterator end_;
      bool valid_;
      Type tok_;

      void increment(){
          assert(valid_);
          valid_ = f_(begin_,end_,tok_);
      }

      const Type&  dereference() const {
          assert(valid_);
          return tok_;
      }
      template<class Other>
      bool equal(const Other& a) const{
          return (a.valid_ && valid_)
              ?( (a.begin_==begin_) && (a.end_ == end_) )
              :(a.valid_==valid_);

      }

      void initialize(){
          if(valid_) return;
          f_.reset();
          valid_ = (begin_ != end_)?
              f_(begin_,end_,tok_):false;
      }
  public:
      token_iterator():valid_(false),begin_(),end_(),tok_() { }

      token_iterator(TokenizerFunc f, Iterator begin, Iterator end = Iterator())
          : begin_(begin), f_(f), end_(end),valid_(false),tok_(){ initialize(); }

      token_iterator(Iterator begin, Iterator end = Iterator())
            : begin_(begin), f_(), end_(end),valid_(false),tok_() {initialize();}

      Iterator base(){return begin_;}




  };
    template <
        class TokenizerFunc = char_delimiters_separator<char>, 
        class Iterator = std::string::const_iterator,
        class Type = std::string
    >
    class token_iterator_generator {

    private: 
    public:
        typedef token_iterator<TokenizerFunc,Iterator,Type> type;
    };
    
    
    // Type has to be first because it needs to be explicitly specified
    // because there is no way the function can deduce it.
    template<class Type, class Iterator, class TokenizerFunc>
        typename token_iterator_generator<TokenizerFunc,Iterator,Type>::type 
    make_token_iterator(Iterator begin, Iterator end,const TokenizerFunc& fun){
        typedef typename 
            token_iterator_generator<TokenizerFunc,Iterator,Type>::type ret_type;
        return ret_type(fun,begin,end);
    }

} // namespace boost

#endif
