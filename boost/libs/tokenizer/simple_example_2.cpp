// simple_example_2.cpp
#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   string s = "Field 1,\"putting quotes around fields, allows commas\",Field 3";
   tokenizer<escaped_list_separator<char> > tok(s);
   for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
       cout << *beg << "\n";
   }
}

