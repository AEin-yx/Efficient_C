### What are Toolchains?

Compile it on your machine **using a toolchain for the target machine**

```cpp
arm-linux-gnueabi-gcc program.c -o program
```

Then **transfer the binary** to the target device and run it.

| Task | Where? | Tool |
| --- | --- | --- |
| Write C code | Anywhere | Text editor |
| Compile for PC | On PC | `gcc` / `clang` |
| Compile for Raspberry Pi | On Pi or with cross-compiler | `gcc` or `arm-linux-gnueabi-gcc` |
| Compile for embedded chip | On PC with toolchain | `arm-none-eabi-gcc` |
| Run binary | Only on the system it was compiled for | Depends on binary format & CPU |

---

### Run a C file using 
### `gcc -Wall -lm -o main get-start.c`
-Wall,-lm
Show/ warn if there are any errors or something unusual
lm means add if required necessary math functions


Format, Format Specifiers: "element␣%zu␣is␣%g,␣\tits␣square␣is␣%g\n”,"%zu %g, \t %g\n”

---

✅ **What Is a Literal in C?**

A **literal** is a **fixed value** directly written into the source code. It doesn't change at runtime and is not stored in a variable (though it can be assigned to one).

### Examples of **C literals**:

- **Integer literals**: `0`, `1`, `42`
- **Floating-point literals**: `2.9`, `3.E+25`, `.00007`
- **Character literals**: `'a'`, `'\n'`
- **String literals**: `"Hello, world!"`

Even though it's used as a **format string** in `printf()`, it’s still a **string literal** in the C language.

- It’s a **fixed string value** written directly in the source code.
- It is not computed or modified — it’s stored **as-is** in memory by the compiler.
- The fact that it contains *format specifiers* (`%zu`, `%g`, `\t`, etc.) doesn't change that — it's still a literal string value in C.
They are *constant character arrays*, which the compiler puts into a read-only section of memory.

---

✅ **What are Identifiers in C?**
Names given to some entities. We may refer it to Data Objects (A,i), Function (main,printf),constants(EXIT_SUCCESS)

`A` and `i` are **variables** (also called **data objects**).

`size_t` is a **type alias** — usually for `unsigned int` — used for size-related values.

The `_t` suffix just tells you: **“Hey, this is a type.” Not a Function,def not variable**

---

- C is like a language: it has words (tokens), grammar (syntax), and meaning (semantics).
- The **meaning** in C is split into:
    1. **Declarations** (introduce things) `size_t i ;`
    2. **Definitions** (create things) `size_t i = 0;`
    3. **Statements** (do things)

### 📘 **Cleaned-Up Explanation**

> Just like in natural languages (like English), C programs have:
> 
> - **Lexical elements** (keywords, symbols, numbers, etc.)
> - **Grammar** (rules about how those elements are put together)

But here’s the difference:

> In C, the meaning of these elements — called semantics — is strictly defined. There's almost no ambiguity, unlike human languages.
> 

---

### **What Is Scope in C?**

**Scope** means: *Where in your program a variable or function is visible (accessible).*

| Scope Type | Where It's Declared | Accessible From | Lifetime |
| --- | --- | --- | --- |
| Block Scope | Inside `{ ... }` | Only inside that block | Ends with block |
| File Scope | Outside any `{}` block | From declaration to end of file | Entire program |
| Function Scope | `goto` labels | Inside the function only | Entire function |

---

### Designated

Initialization of type [4]=3.E+25sets the last item of the array A to the value 3.E+25

Missing items like [2] is set to 0

---

### Difference between Declaration and Definition.

```cpp
// File A
extern int counter;      // declaration (no memory allocated)

// File B
int counter = 0;         // definition (memory allocated)
```

```cpp
int counter = 0;   // ✅ okay, one definition
int counter = 5;   // ❌ error: redefinition
```

### What is Tentative Declaration?

```cpp
int counter;       // ✅ Tentative definition → becomes: int counter = 0;

int counter = 0;   // ❌ Error: Redefinition
```

### 📄 **counter.h**

```c
extern int counter;  // Declaration only (no memory)
```

### 📄 **file_a.c**

```c
#include "counter.h"

int counter = 0;     // One and only definition
```

### 📄 **file_b.c**

```c
#include "counter.h"

void use_counter() {
    counter++;       // Valid use of the global
}
```

---

### Domain iteration

0,1,2,3,4 is the domain over which loop variable i iterates.

---

### How printf works, control flow, function call return

![lvl0](https://github.com/user-attachments/assets/506ba240-d46e-4301-8fc4-5d29d1d7da53)


### Call by value and Call by Reference

`printf` will never be able to change `i` itself.

This is called **call by value** — the function gets a copy of the variable, not the variable itself.

Some other languages (like C++, Python*) support **call by reference**, where a function can directly modify the original variable.

C does **not support pass-by-reference**, but it has a workaround:

**You can pass the address of a variable** using a pointer, allowing the function to change the original value.

```cpp
void change(int *x) {
    *x = 100;  // change the value at the address
}

int main() {
    int i = 42;
    change(&i);   // pass the address of i
    printf("%d\n", i);  // Output: 100
}
```
