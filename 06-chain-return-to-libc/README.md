# Chaining return to libc functions

## Single return to libc

For a single return to libc function call, this is sufficient.

```
|      buffer      |
|       ...        |
|     old ebp      |
|   return addr    | <- &libc
|      arg0        | <- fake return addr
|      arg1        | <- arg0
```

To chain multiple libc function calls, we have to modify the old ebp to create enough space for the stack frames of function 1 `f1` and function 2 `f2`.

## Instructions used

A stack frame is defined by the memory below `%esp` and above `%ebp`.

### push

`push` decrements `%esp`, then writes the value being pushed to the memory pointed to by `%esp`.

### pop

`pop` reads the value to pop from the memory pointed to by `%esp`, then increments `%esp`.

### leave

`leave` first copies `%ebp` to `%esp` or "shifts" `%esp` to `%ebp`. This effectively squashes the stack frame down.

Then, `leave` pops the stack into `%ebp`.

### ret

`ret` pops the stack into `%ebp`.


## Creating the stack frame for multiple libc calls

### For two calls

```
|      buffer      | <- %esp
|       ...        |
| &last arg of f1  | <- %ebp
|       &f1        |
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

### For general chain of calls

```
|      buffer      |     <- %esp
|       ...        |
|                  |+   <- %ebp
|       &f1        | \
|   &leave; ret;   |  |
|    ...f1_args    |  |
|                  |<-+
|       &f2        | \
|   &leave; ret;   |  |
|    ...f2_args    |  |
|                  |<-+
|       ...        | \
|                  |<=+
|       &fn        |
|   &leave; ret;   |
|    ...fn_args    |
|     ...data      |
```

Place `&next_fn - 4` before each `fn`. The last address can be arbitrary, saving us 4 bytes if needed.

## Demonstration

When the original function returns, `leave` and `ret` is called.

### leave 1

Shift `%esp` to `%ebp`:

```
%eip = ret;

|      buffer      |
|       ...        |
| &last arg of f1  | <- %esp <- %ebp
|       &f1        |
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

Pop into `%ebp`:

```
%eip = ret;

|      buffer      |
|       ...        |
| &last arg of f1  |
|       &f1        | <- %esp
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    | <- %ebp
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

### ret 1

Pop into `%eip`:

```
%eip = &f1;

|      buffer      |
|       ...        |
| &last arg of f1  |
|       &f1        |
|   &leave; ret;   | <- %esp
|    arg0 of f1    |
|    arg1 of f1    | <- %ebp
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

### f1

Execute f1, which pushes `%ebp` onto the stack and shifts `%ebp` to `%esp`.

```
%eip = ...;

|      buffer      |
|       ...        |
| &last arg of f1  |
|   &arg1 of f1    | <- %esp <- %ebp
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```


Then, `%esp` is used to define the stack for f1.

* Note that the address of the last argument of f1 sits right above the address of f2.
* Arguments are properly placed at %ebp + 2.

```
%eip = ...;

|      buffer      | <- %esp
|       ...        |
|   &arg1 of f1    | <- %ebp
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

### leave 2

At the end of f1, f1 calls `leave` which shifts `%esp` back to `%ebp`

```
%eip = ...;

|      buffer      |
|       ...        |
|   &arg1 of f1    | <- %ebp <- %esp
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

Pop into `%ebp`:

```
%eip = ...;

|      buffer      |
|       ...        |
|   &arg1 of f1    |
|   &leave; ret;   | <- %esp
|    arg0 of f1    |
|    arg1 of f1    | <- %ebp
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

### ret 2

Pop into `%eip`:

```
%eip = &leave; ret;

|      buffer      |
|       ...        |
|   &arg1 of f1    |
|   &leave; ret;   |
|    arg0 of f1    | <- %esp
|    arg1 of f1    | <- %ebp
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

### leave 3

Shift `%esp` to `%ebp`:

```
%eip = &leave; ret;

|      buffer      |
|       ...        |
|   &arg1 of f1    |
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    | <- %ebp <- %esp
|       &f2        |
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
```

Pop into %ebp:

```
%eip = &leave; ret;

|      buffer      |
|       ...        |
|   &arg1 of f1    |
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        | <- %esp
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
|       ...        | <- %ebp
```

### ret 3

Pop into `%eip`:

```
%eip = &f2;

|      buffer      |
|       ...        |
|   &arg1 of f1    |
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        |
| fake return addr | <- %esp
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
|       ...        | <- %ebp
```

### f2

Execute f1, which pushes `%ebp` onto the stack and shifts `%ebp` to `%esp`.

```
%eip = &f2;

|      buffer      |
|       ...        |
|   &arg1 of f1    |
|   &leave; ret;   |
|    arg0 of f1    |
|    arg1 of f1    |
|       &f2        | <- %esp <- %ebp
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
|       ...        |
```

Then, `%esp` is used to define the stack for f2.

```
%eip = &f2;

|      buffer      | <- %esp
|       ...        |
|       &f2        | <- %ebp
| fake return addr |
|    arg0 of f2    |
|    arg1 of f2    |
|       ...        |
|       ...        |
```

## Common patterns

When a function is called:

* `$esp` is effectively poppsed into `$eip` without affecting `$ebp`; and
* we need to ensure that `$esp` is right above the arguments of the function such that `$ebp` will be called to the right memory address.
  * `$ebp` needs to be 2 above the arg list. When `$ebp` is pushed onto the stack, `$esp` moves 1 position up, then `$ebp` is shifted to `$esp`, effectively putting it 2 above the arg list.
