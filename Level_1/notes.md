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
```c
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[argc+1]){
    puts("Hello World");
    if(argc>1){
        while(true){
            puts("some program never stop");
        }
    } else {
        do{
            puts("but this one does");
        }while(false);
    }
    return EXIT_SUCCESS;
}
```

> The feature int main(int argc, char* argv[argc+1]) is a special case.
> 

🔑 **Yes** — this is special to `main`.

- Normally in C, **function parameters** can't use *other parameters* in their type declarations.
- But **C99** introduced a feature called **"Variable Length Arrays" (VLA)** that makes this legal **only in some cases**, like with `main()`.

`char* argv[argc+1];`  instead of argc=null, we say argc+1=null  

### `char* argv[]` is an Array of Strings

> a collection of characters is a string, and since we have no string type in C, we use char* to emulate it.
> 

```c
gcc -Wall -o style style.c -lm

./style  
// Hello World
// but this one does
./style hello world  
// here argc=3 argv[0]=./style argv[1]=hello argv[2]=world argv[3]=null
// some program never stop
// some program never stop 
// some program never stop...

```

Use puts to get a newline+printing but if we were to cmbine string and integers we use printf

🔥 Summary

| Statement | Is it True? |
| --- | --- |
| `argv[argc]` is `NULL` | ✅ Yes, always (required by the standard) |
| `argv[argc+1]` is valid to access | ❌ No — it's out-of-bounds |
| Writing `argv[argc+1]` changes the behavior | ❌ No — it's just a declaration style, not a functional change |
| `argv[argc+1]` is a C99 feature | ✅ Yes — depends on support for VLAs |
