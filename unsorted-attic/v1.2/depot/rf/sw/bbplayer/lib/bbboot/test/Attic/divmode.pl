#!/usr/bin/perl
#
# script to test if a divmode reset occurred. If so
# returns 0. If not, returns 1.
#
# usage:
#  divmode.pl <logfile> <trace_reg>

open(logfile, "@ARGV[0]") || die "Cannot open log file.\n";
while ($line = <logfile>) {
    if ($line =~ /@ARGV[1]/) {
	$checkline = 1;
    }
    elsif ($checkline == 1){
	if ($line =~ /0x00000002/){
	    close(logfile);
	    exit(0);
	}
	$checkline = 0;
    }
}
close(logfile);

exit(1);
