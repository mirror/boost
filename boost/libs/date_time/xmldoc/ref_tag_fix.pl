#!/usr/bin/perl -w
# simply updates the id attribute of the library-reference tag in
# the generated *.boostbook files. It will NOT update a file that already
# has an id attribute set for library-reference.
#
# Bart Garst - 7/1/2004

use strict;

# key-value of file name and id attribute
# if the attributes are changed here it would be a good idea to
# also change the links in doxy.xml
my %files = (
  'date_time_autodoc.boostbook'  => 'date_time_reference',
  'gregorian_autodoc.boostbook'  => 'gregorian_reference',
  'posix_time_autodoc.boostbook' => 'posix_time_reference'
);


foreach my $key(keys %files) {
  fix_id($key, $files{$key});
}

exit;

### subroutines ###

sub fix_id {
  my $filename = shift || die "Error: argument 1 missing to sub $!";
  my $id_tag = shift || die "Error: argument 2 missing to sub $!";
  my ($line, @new_file);
  
  print "...processing $filename...\n";
  
  # open & read file and change appropriate line
  open(INP, "<$filename") || die "File open (read) failed: $!";
  while($line = <INP>){
    if($line =~ /<library-reference>/) {
      push(@new_file, "<library-reference id=\"$id_tag\">\n");
    }
    else{
      push(@new_file, $line);
    }
  }
  close(INP);
  
  # open & write new file w/ same name
  open(OTP, ">$filename") || die "File open (write) failed: $!";
  foreach(@new_file){
    print OTP "$_";
  }
  close(OTP);
}

__END__
