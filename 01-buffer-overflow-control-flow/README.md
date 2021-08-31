# Control flow buffer overflow exploit

There is a bug where we read `sizeof(s)` bytes instead of `sizeof(s.nbytes)`. Therefore, we are able to overflow the struct member and overwrite the function pointer of `s`.

```c
  ...
   char *p, *q;
   struct {
     unsigned nbytes; // Number of bytes that will be received from client
     void (*fp) (char*); // Function pointer
   } s;
   s.fp = proc_buf; // Set s.fp to function proc_buf
   read(fd, &(s.nbytes), sizeof(s)); // Step 1
   ...
```

The server program reads a byte stream from the socket and stores it in heap. This allows us to write an arbitrary function to the heap, and execute it by using the overwritten function pointer.

To generate the bytes required for the function, we use `msfvenom`.

For the function pointer to reach the injected function in spite of address randomization, we use a NOP sled.

