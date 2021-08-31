# Buffer overflow

## `account1.c`

Data is written from `argv[1]` to `account.name` until a `\0` character is reached. We can overwrite the other fields of the struct.

## `account2.c`

The same principle as `account1.c`, but with `scanf`.

## Writing specific values

Ths most important thing to take note of is the size of a `word` and `endianness`.

On a 32-bit Intel system, each word is 4 bytes long and bytes are arranged in little endian. When reading a word, bytes are arranged with the MSB at the larger address and the LSB at the smaller address. Therefore, when reading an `int`, we treat a sequence of 4 bytes as read from left to right.

However, arrays will still sequence from smaller to larger addresses. Therefore, when overwriting an `int` with a byte stream, we need to write each byte in reverse order. We write the LSB first and the MSB last, similar to reading an `int` backwards.

The memory diagram is arranged as such to coincide with how memory is laid out when reading words from gdb.

```
       0x03 0x02 0x01 0x00
0x00: |    |    |    |    |
       0x07 0x06 0x05 0x04
0x04: |    |    |    |    |
```

Writing `"ABC" = {0x41, 0x42, 0x43, 0x00}` to address `0x00` results in

```
       0x03 0x02 0x01 0x00
0x00: | 00 | 43 | 42 | 41 |
       0x07 0x06 0x05 0x04
0x04: |    |    |    |    |
```
Writing `0x41424300` to address `0x04` results in

```
       0x03 0x02 0x01 0x00
0x00: | 00 | 43 | 42 | 41 |
       0x07 0x06 0x05 0x04
0x04: | 41 | 42 | 43 | 00 |
```

