// simple_example_4.cpp
#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   string s = "This is,  a test";
   tokenizer<char_delimiters_separator<char> > tok(s);
   for(tokenizer<char_delimiters_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
       cout << *beg << "\n";
   }
}

