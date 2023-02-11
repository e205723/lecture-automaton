use strict;
use warnings;

my $target = "Brouhaha";
my $regex = 'haha';

while ($target =~ m/$regex/g) {
  my $match = $&;
  my $start = $-[0];
  my $end = $+[0];
  print "pattern match succeeded\n";
  print "Match: $match\n";
}

