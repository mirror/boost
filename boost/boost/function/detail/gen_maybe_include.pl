#!/usr/bin/perl -w
use English;

$max_args = $ARGV[0];

open (OUT, ">maybe_include.hpp") or die("Cannot write to maybe_include.hpp");
for($on_arg = 0; $on_arg <= $max_args; ++$on_arg) {
    if ($on_arg == 0) {
	print OUT "#if";
    }
    else {
	print OUT "#elif";
    }
    print OUT " BOOST_FUNCTION_NUM_ARGS == $on_arg\n";
    print OUT "#  ifndef BOOST_FUNCTION_$on_arg\n";
    print OUT "#    define BOOST_FUNCTION_$on_arg\n";
    print OUT "#    include <boost/function/function_template.hpp>\n";
    print OUT "#  endif\n";
}
print OUT "#else\n";
print OUT "#  error Cannot handle Boost.Function objects that accept more than $max_args arguments!\n";
print OUT "#endif\n";
