#!/usr/bin/perl
# Splits the list of files and outputs for makefile type files 
# wrapped at 80 chars 
@a = split(" ", $ARGV[1]);
$b = "$ARGV[0]=";
$len = length($b);
print $b;
foreach my $obj (@a) {
   $len = $len + length($obj);
   $obj =~ s/\*/\$/;
   if ($len > 100) {
      printf "\\\n";
      $len = length($obj);
   }
   print "$obj ";
}
#if ($ARGV[0] eq "HEADERS") { print "testprof/tomcrypt_test.h"; }
print "\n\n";
# $Source: /cvs/libtom/tomsfastmath/parsenames.pl,v $   
# $Revision: 1.1 $   
# $Date: 2006/12/31 21:31:40 $ 
