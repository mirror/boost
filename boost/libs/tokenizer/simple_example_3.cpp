// simple_example_3.cpp
#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   string s = "12252001";
   int offsets[] = {2,2,4};
   offset_separator f(offsets, offsets+3);
   tokenizer<offset_separator> tok(s,f);
   for(tokenizer<offset_separator>::iterator beg=tok.begin(); beg!=tok.end();++beg){
       cout << *beg << "\n";
   }
}