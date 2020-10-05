
Notes by pmateti@wright.edu
oct 2013

See Makefile also.

This dir contains C src code files extracted from AlephOne's Phrack
article p49-14.txt.  The code is now sanitized so that all files
compile without errors in a modern (2013) gcc setting.  Ignore the
format string based warnings.  Try to cleanse other warnings.  The
get_sp() does produce a warning, and revising this code is part of an
exercise for you.

Modern C requires the return type of main to be int.

Some stylistic changes (renaming variables etc) have also happened.

To see the actual effects compile and run these in an old (around
2005) Linux distro.

The C-flag std=c99 will not work within Auditor*.iso.

./exploit2 600 1564 does not work in contrast to the article.
% ./exploit2.prg 600 1564
Using address: 0xbfffeedc
begin running /home/pmateti/.bashrc-done
[pmateti@prabha AlephOne]$ ./vulnerable.prg $EGG
bffff070
Segmentation fault

% ./exploit2.prg 650 1256
Using address: 0xbffff010
begin running /home/pmateti/.bashrc-done
[pmateti@prabha AlephOne]$ ./vulnerable.prg $EGG
bffff010
sh-2.05b$ 

See video for a successful ./exploit3.prg.

-eof-
