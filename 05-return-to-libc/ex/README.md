# ex/vul.c

The goal is to create an exploit to reduce `account.balance` by 256 and print out `account.balance`.

$ebp = 0xffffd2b8
&buf = 0xffffd260

$ebp - &buf = 88
$ebp + 5w = 0xffffd2cc
$ebp + 6w = 0xffffd2d0

&printf = 0xf7e39c60
&exit = 0xf7e19060

&account.balance = 0xffffd350

# Method

We can use a format string exploit to write 0 to &account.balance + 1, which will zero out the 8th bit.

We simply call printf with "%n%s", &account.balance + 1, $account.balance.

Although a string is printed out, we can find the 1-to-1 mapping of the char to get the balance.

We should expect to get 113 = 'q'

