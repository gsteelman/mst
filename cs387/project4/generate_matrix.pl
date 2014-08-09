#!/usr/local/bin/perl

use strict;

use Math::Trig;
use Cwd;

#Ask for input if not provided via command line
my $size = 0;
if( $#ARGV < 0 )
{
    print "\nScript to generate an N x N matrix into file \"matrix.N\". What's N? ";
    $size = <STDIN>;
}
#Otherwise, get it from the command line
else { $size = $ARGV[0]; }

chomp( $size );
if( $size <= 0 ) { exit; }

### END OF VARIABLE INITIALIZATIONS

open( OUTMATRIX, ">matrix.$size") || die "Can't open matrix.$size\n";

print OUTMATRIX "$size\n";

$size *= $size;
while( $size )
{
    printf OUTMATRIX "%.6f\n", rand();
    --$size;
}

close( OUTMATRIX );

