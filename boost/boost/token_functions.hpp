// Boost token_functions.hpp  ------------------------------------------------//

// Copyright John R. Bandela 2001. 

// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_TOKEN_FUNCTIONS_JRB051801_HPP_
#define BOOST_TOKEN_FUNCTIONS_JRB051801_HPP_

#include <vector>
#include <stdexcept>
#include <cassert>
#include <string>
#include <cctype>

namespace boost{

  //===========================================================================
  // The escaped_list_separator class. Which is a model of TokenizerFunction
  // An escaped list is a super-set of what is commonly known as a comma 
  // separated value (csv) list.It is separated into fields by a comma or 
  // other character. If the delimiting character is inside quotes, then it is
  // counted as a regular character.To allow for embedded quotes in a field,
  // there can be escape sequences using the \ much like C. 
  // The role of the comma, the quotation mark, and the escape 
  // character (backslash \), can be assigned to other characters.

  struct escaped_list_error : public std::runtime_error{
    escaped_list_error(const std::string& what):std::runtime_error(what){}
  };
  

// The out of the box GCC 2.95 on cygwin does not have a char_traits class.
// MSVC does not like the following typename
#ifndef BOOST_MSVC
  template <class Char, 
	  class Traits = typename std::basic_string<Char>::traits_type >
#else
  template <class Char, 
	  class Traits = std::basic_string<Char>::traits_type >
#endif
  class escaped_list_separator{

  private:
    typedef std::basic_string<Char,Traits> string_type;
    struct char_eq{
      Char e_;
      char_eq(Char e):e_(e){}
      bool operator()(Char c){
	return Traits::eq(e_,c);
      }
    };
    string_type  escape_;
    string_type  c_;
    string_type  quote_;		  
    bool last_;

    bool is_escape(Char e){
      char_eq f(e);
      return std::find_if(escape_.begin(),escape_.end(),f)!=escape_.end();
    }
    bool is_c(Char e){
      char_eq f(e);
      return std::find_if(c_.begin(),c_.end(),f)!=c_.end();
    }
    bool is_quote(Char e){
      char_eq f(e);
      return std::find_if(quote_.begin(),quote_.end(),f)!=quote_.end();
    }
	  template<class iterator,class Token>
	  void do_escape(iterator& next,iterator end,Token& tok){
				
			if(++next==end)
			  throw escaped_list_error(
			  std::string("cannot end with escape"));
			if(Traits::eq(*next,'n')){
			  tok+='\n';
			  return;
			}
			else if(is_quote(*next)){
			  tok+=*next;
			  return;
			}
			else if(is_c(*next)){
			  tok+=*next;
			  return;
			}
			else if(is_escape(*next)){
			  tok+=*next;
			  return;
			}
			else
			  throw escaped_list_error(
			  std::string("unknown escape sequence"));
			
		  
		  }

	  public:
	  
    explicit escaped_list_separator(Char  e = '\\',
      Char c = ',',Char  q = '\"')
      :escape_(1,e),c_(1,c),quote_(1,q),last_(false){}
    escaped_list_separator(string_type e, string_type c, string_type q):
      escape_(e),c_(c),quote_(q),last_(false){}
    
    void reset(){last_=false;}

	  
	  

    template<class InputIterator,class Token>
    bool operator()(InputIterator& next,InputIterator end,Token& tok){
      
      bool bInQuote = false;
      tok = Token();
      
      if(next==end){
	if(last_){
	  last_ = false;
	  return true;
	}
	else
	  return false;
      }
      last_ = false;
      for(;next != end;++next){
	
	if(is_escape(*next)){
	  do_escape(next,end,tok);
	}
	
	else if(is_c(*next)){
	  if(!bInQuote) {
	    // If we are not in quote, then we are done
	    ++next;
	    // The last character was a c, that means there is
	    // 1 more blank field
	    last_ = true; 
	    return true;
	  }
	  else tok+=*next;
	}
	
	else if(is_quote(*next)){
	  bInQuote=!bInQuote;
	}
	  
	
	else{
	  tok += *next;
	}
      }
      return true;
      
      
    }
  };

   
  //===========================================================================
  // The offset_separator class, which is a model of TokenizerFunction.
  // Offset breaks a string into tokens based on a range of offsets

  class offset_separator{
  private:

     std::vector<int> offsets_;
     unsigned int curoffset_;
	 bool bwrapoffsets_;
	 bool breturnpartiallast_;

  public:
     template<typename Iter>
     offset_separator(Iter begin,Iter end,bool bwrapoffsets = true,
		bool breturnpartiallast = true)
		:offsets_(begin,end),curoffset_(0),
		bwrapoffsets_(bwrapoffsets),breturnpartiallast_(breturnpartiallast){}
	 
	 offset_separator()
		:offsets_(1,1),curoffset_(),
		bwrapoffsets_(true),breturnpartiallast_(true){}

	  
	 void reset(){
		  curoffset_ = 0;
	 }


     template<typename InputIterator, typename Token>
     bool operator()(InputIterator& next, InputIterator end, Token& tok)
	  {
        assert(!offsets_.empty());
		
		tok = Token();

		if(next==end)
			return false;


        if(curoffset_==offsets_.size())
			if(bwrapoffsets_)
				curoffset_=0;
			else
				return false;
        
        int c = offsets_[curoffset_];
		int i = 0;
        for(; i < c; ++i){
           if(next==end)break;
		   tok+=*next++;
		}
		
		if(!breturnpartiallast_)
			if(i < (c-1) )
				return false;

        ++curoffset_;
        return true;
     }
  };

  //===========================================================================
  // The char_delimiters_separator class, which is a model of TokenizerFunction.
  // char_delimiters_separator breaks a string into tokens based on character
  // delimiters. There are 2 types of delimiters. returnable delimiters can
  // be returned as tokens. These are often punctuation. nonreturnable
  // delimiters cannot be returned as tokens. These are often whitespace

// The out of the box GCC 2.95 on cygwin does not have a char_traits class.
#ifndef BOOST_MSVC
  template <class Char, 
	  class Traits = typename std::basic_string<Char>::traits_type >
#else
  template <class Char, 
	  class Traits = std::basic_string<Char>::traits_type >
#endif
  class char_delimiters_separator{


  private:	

     typedef std::basic_string<Char,Traits> string_type;
     string_type returnable_;
     string_type nonreturnable_;
     bool return_delims_;
	 bool no_ispunct_;
	 bool no_isspace_;
		
     bool is_ret(Char E)const
     {	
		 if(returnable_.length())
			 return  returnable_.find(E) != string_type::npos;
		 else{
			 if(no_ispunct_){return false;}
			 else{
			 	using namespace std;
				int r = ispunct(E);
				return r != 0;
			}
		 }
	 }
     bool is_nonret(Char E)const
     {
		 if(nonreturnable_.length())
			 return  nonreturnable_.find(E) != string_type::npos;
		 else{
			 if(no_isspace_){return false;}
			 else{
			 	using namespace std; 
				int r = isspace(E);
				return r != 0;
			}
		 }
	 }

  public:

     explicit char_delimiters_separator(bool return_delims = false, 
		 const Char * returnable = 0,const Char * nonreturnable = 0)
		 :returnable_(returnable?returnable:string_type().c_str()),
		 nonreturnable_(nonreturnable?nonreturnable:string_type().c_str()),
		 return_delims_(return_delims),no_ispunct_(returnable!=0),
		 no_isspace_(nonreturnable!=0){}

     void reset(){}

  public:

     template<class InputIterator,class Token>
     bool operator()(InputIterator& next, InputIterator end,Token& tok){
		 tok = Token();
		 
		 // skip past all nonreturnable delims
		 // skip past the returnable only if we are not returning delims
		 for(;next!=end && ( is_nonret(*next) || (is_ret(*next) 
			 && !return_delims_ ) );++next){}
		 
		 if(next == end){
			 return false;
		 }
		 
		 // if we are to return delims and we are one a returnable one
		 // move past it and stop
		 if(is_ret(*next) && return_delims_){
			 tok+=*next;
			 ++next;
		 }
		 else
			 // append all the non delim characters
			 for(;next!=end && !is_nonret(*next) && !is_ret(*next);++next)
				 tok+=*next;
			 
			 
		 return true;
	 }
  };



} //namespace boost


#endif 





