#!/usr/bin/perl
# usage:
# log_parse <trace_pattern>
#   i.e., log_parse 0x04600000

$checkline = 0;
while ($line = <STDIN>) {
    if ($line =~ /@ARGV[0]/) {
        $checkline = 1;
    }
    elsif ($checkline == 1){
        if ($line =~ /0xbaaaaaad/){
            print "halted";
            exit 0;
        }
        elsif ($line =~ /0xec000001/){
            print "exception";
            exit 0;
        }
        elsif ($line =~ /0xaaaaaaaa/){
            print "success";
            exit 0;
        }
        $checkline = 0;
    }
}
print "unknown\n";

