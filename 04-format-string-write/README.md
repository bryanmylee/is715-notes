# Writing to arbitrary memory locations with format strings

The format specifier `%n` writes the number of bytes written so far from the start of the string to the address specified by the argument. Using the same format string vulnerability, this allows us to write data to a user-controlled memory location.

## Attack structure

The initial structure is similar to arbitrary memory read with format strings. However, we replace the last format specifier with `%n`.

`"000\x4a\xd5\xff\xff %x %x %x %x %n"`

### Writing values

Instead of reading from the address `0xffffd54a`, the format string will write the number of bytes to `0xfffd5fa` instead.

## Controlling the exact value written

The number of bytes written is difficult to control, as the output of the padding `%x` depends on the dynamic values during runtime.

* `0x00000001` would be printed with 1 byte `1`
* `0x10000000` would be printed with 8 bytes `10000000`

There are a few strategies available to control the value written

### Run, check, and increment

One strategy is to run the program under gdb and determine the number of bytes so far by replacing `%n` with `%d`. Then, as long as the number of bytes so far is smaller than the target value, we can pad the output by adding zero-padding to one of the `%x` format specifiers.

`"000\x4a\xd5\xff\xff %x %x %x %0108x %n"`

### Write to the `&target_addr - 1` for small values

If a small target value `n` is required, we can write `n * 256` to `&target_addr - 1`.

Since it is highly unlikely for more than 256 bytes to be written by the format string, the arbitrary number of bytes written will only affect the byte at `&target_addr - 1`. `&target_addr` will then receive the value `(n * 256) >> 8 = n`.

## Controlling the number of bytes written

`%n` can be prefixed with `h` to write 2 bytes only or `hh` to write 1 byte only. This can be useful if it is critical that no other memory is overwritten.

## Multiple writes

It is possible to write multiple values if and only if the values are increasing in order.

Create the attack string as per normal, with the second target address injected **4 bytes after the first address**.

Write the smaller value to the target address with `%n`, then add a `%x` specifier to increment the number of bytes written so far to the second target value. This specifier will read the 4 injected bytes.

Lastly, use a second `%n` to write to the second target address.

## Caveats

One common mistake I've made so far is that my attack string is larger than the buffer can hold.
