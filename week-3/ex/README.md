# Reading arbitrary memory values with format strings

If a user-controlled format string is passed into `printf`, then it is possible to create a mismatch between the number of arguments provided to `printf` by the caller, and the number of arguments read from the stack by `printf`.

If the user-controlled format string is stored on the stack, then this allows us to write arbitrary memory addresses to the stack for access later.

## Attack structure

Usually, there are 4 parts to reading arbitrary memory with a format string attack.

`"000\x4a\xd5\xff\xff %x %x %x %x %s"`

### Alignment of injected memory address

`"000"`

We want to align injected values to the stack frame width. This makes it possible to read the injected value as a **word**. Otherwise, parts of the injected value will fall into one word and the other parts will cross the boundary into another word.

### Injection of memory address

`"\x4a\xd5\xff\xff"`

This writes the memory address to the stack.

### Argument padding

`%x %x %x %x`

This causes `printf` to continue searching down the stack for more values to read. Since our injected value is aligned to the stack frame, we will eventually be aligned with the memory address to read.

### Dereferencing the pointer

Unlike most other format parameters, `%s` is passed by reference. Therefore, the argument is **dereferenced** before printing. When we are aligned with the injected memory address to read, `%s` allows us to dereference the address and print the value as a string.

## vul1

`printf` is called with `buf`, which is read from a file `abc`. To get the memory address `&pwd`, we use gdb to debug the program.

1. Run `disas main` to reveal the assembly instructions at main.
2. Find the instruction address of the call to `printf`, and set a breakpoint right before the call with `break *0x<instr addr>`.
3. Find the memory address of the secret `&pwd` and `&buf`. We will need this later to find the alignment and padding offsets required.
4. At this point, the arguments to `printf` should be prepared on the stack. `x/24wx $esp` to read 24 words in hexadecimal format at the top of the stack.
5. Determine the alignment offset of `&buf` from the stack frame. Add characters to the attack string to align.
6. Write the memory address `&pwd` to the attack string. Remember to write in little endian.
7. Determine the number of stack frame rows there are between `%esp` and the injected value. Note that the value directly at `%esp` is a pointer to the format string itself. Add the appropriate `%x` offset padding to the attack string.
8. Finish the attack string with `%s`.

Note that the memory addresses during debugging is different from regular execution. The random addresses used are seeded by environment variables set during the debugging session.

To execute the attack, write the attack string to the file `abc` and re-run the program in gdb. The value of `pwd` should be exposed.

