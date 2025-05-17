### Style Considerations to be careful of  
✅Rule 1:  Bind type modifiers and qualifiers to the left

```c
char* name / read as name is a pointer to type char

char const* const name; / read as name is a constant pointer which points to a constant char
```

✅Rule 2:  Donot use continued declaration

```c
unsigned const* const a, b; / a is a const pointer which points to constant unsigned int |const* const a| while b is a unsigned int |unsigned b|
```

✅ Rule 3: Use **array notation** for pointer parameters **when null is not allowed**

```c
size_t strlen(char const string[static 1]); ✅
size_t strlen(const char *string); ❌
```

### What it means:

- This is not just any pointer — it’s a **pointer to an array that must contain at least 1 element**.
- The keyword `static 1` tells the compiler:
    
    👉 "**Hey, the function assumes `string` is not null and has at least one character** (like a valid C string)."
    
```c
int main(int argc, char* argv[argc + 1]); ✅
int main(int argc, char **argv); ❌
```
main receives an array of pointers to char(because C don't have string and we use pointers to emulate strings) and 
It must have `argc + 1` elements — the last one being `NULL`.

✅ Rule 4: Use **function notation** when passing function pointers that must not be null

```c
int atexit(void handler(void));
```

- This looks like `handler` is just a regular function argument.
- But under the hood, C rewrites this into a function **pointer**.
- Because it looks like a real function, you're saying:
    
    👉 “The caller **must pass a valid function** — not NULL.”
    

Compare with:

```c
int atexit(void (*handler)(void));
```

- This is more traditional but neutral — it doesn’t say whether `handler` can be `NULL`.

✅ The first version gives **extra meaning**: it tells the reader and compiler **this function pointer is guaranteed to be valid**.
