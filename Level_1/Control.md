# Everything is about control  
`if for do while switch` 

switch is a multiple selection based on “integer value”

ternary operator, denoted by an expression in the form `cond ? A : B`

compile-time preprocessor conditionals `#if/#ifdef/#ifndef/#elif/#else/#endif` 

 type generic expressions denoted with the keyword `_Generic`

---

```c
 if (i > 25)//controlling expression 
 {          //
 j = i- 25; //  -> dependent block or block
 }          //
```

This is a general form and also called as selection statement

```c
if (condition) statement0-or-block0
 else statement1-or-block1
```

---

## ✅ `stdbool.h` and the `bool` Type in C

### 🔹 What It Gives You

When you `#include <stdbool.h>`, you get:

```c
#include <stdbool.h>
```

Now you can use:

```c
bool flag = true;
```

Under the hood:

```c
typedef _Bool bool;
#define true 1
#define false 0
```

So `bool` is just an alias for `_Bool`, a type added in C99.

---

## 🔹 Why Use `bool`, `true`, and `false` Instead of 0 and 1?

### ✅ Clarity & Intent

Compare:

```c
int valid = 1;
if (valid) { ... }
```

vs.

```c
bool valid = true;
if (valid) { ... }
```

The second one tells the **reader and the compiler**:

- “This value is a condition — not a number or a count”
- This makes the code **more self-documenting and expressive**

---

## 🔹 But Aren’t `0` and `1` the Same?

Yes, technically:

- In C, **any non-zero value is `true`**
- `0` is always `false`
- But it’s a **best practice** to write `true` and `false` to show intent

---

## 🔹 Historical Note

Before C99, C didn’t have a built-in boolean type. So people used:

```c
#define TRUE 1
#define FALSE 0
```

But this was unsafe and could conflict with other definitions.

Why is 

considered unsafe meanwhile 

```c
#define TRUE 1
#define FALSE 0

```

is considered safe?

```c
#include <stdbool.h>
typedef _Bool bool;
#define true 1
#define false 0
```

🔍 1. `#define` Creates **Unscoped** Macros (Problem: Name Collisions)
You're creating **textual replacements** in the preprocessor — *not* real typed values.
`if (my_func(TRUE))  // becomes → if (my_func(1))`

### ✅ Problem:

- These names (`TRUE`, `FALSE`) are **global**, and they **pollute the namespace**.
- If a library or header you include *also* defines `TRUE` and `FALSE` (with slightly different meanings), you'll get **redefinition warnings** or even **subtle bugs**.

---

🔍 2. `#define` Has **No Type Safety**

`#define TRUE 1` 

doesn’t tell the compiler *what type* `TRUE` is. Is it: `int`?`char`?`enum`? Used in a pointer context?

but with `typedef _Bool bool;`  you’re creating a **real type**, which can: Trigger type-checking,Work better with debuggers and IDEs,Avoid misuse (e.g. assigning a struct to a bool)

---

Avoid Styles like

```c
bool b = ...;

if ((b != false) == true) {
    // do something
}
// because its verbose and redundant
```

Follow the table below to see the preffered design choice for a clean C code that
Reflect **C’s control philosophy**: treat values as conditions directly

| Pattern | Verdict | Why |
| --- | --- | --- |
| `if (b == true)` | ❌ Avoid | Redundant, harder to read |
| `if (b != false)` | ❌ Avoid | Verbose, same logic as `if (b)` |
| `if (b)` | ✅ Preferred | Clean, idiomatic, clear intent |
| `if (i != 0)` | ⚠️ Acceptable | But `if (i)` is better for bool use |

---

> ✅ All scalar values in C can be interpreted as having a "truth value".
> 

This means:

Even if a variable is **not** of type `bool`, **you can still use it in a condition** (like an `if` or `while`) — and C will treat:

- **0** or **NULL** as `false`
- **Anything non-zero** as `true`
### 🔍 What's a *Scalar* Type?

The author defines "scalar types" as:

- **Numerical types** (like `int`, `unsigned`, `size_t`, `double`)
- **Pointer types** (like `void*`, `char*`)

These types are **not complex structures or arrays**, but rather **single values** that can fit in a register — which is why they can be directly evaluated in conditionals.

```c
char* s = NULL;

if (s) {
    printf("Pointer is valid\n");
}
```

```c
int x = 5;

if (x) {
    printf("x is non-zero!\n");
}
```

---

Table Scalar Types

| Level | Name | Category | Other  | Where | `printf` format |
| --- | --- | --- | --- | --- | --- |
| 0 | `size_t` | Unsigned | Built-in | `<stddef.h>` | `"%zu"`, `"%zx"` |
| 0 | `double` | Floating |  | Built-in | `"%e"`, `"%f"` |
| 0 | `signed`  | Signed | `int` | Built-in | `"%d"` |
| 0 | `unsigned` | Unsigned |  | Built-in | `"%u"`, `"%x"` |
| 0 | `bool`  | Unsigned | `_Bool` | `<stdbool.h>` | `"%d"` (prints 0 or 1) |
| 1 | `ptrdiff_t` | Signed |  | `<stddef.h>` | `"%td"` |
| 1 | `char const*` | String |  | Built-in | `"%s"` |
| 1 | `char` | Character |  | Built-in | `"%c"` |
| 1 | `void*` | Pointer |  | Built-in | `"%p"` |
| 2 | `unsigned char` | Unsigned |  | Built-in | `"%hhu"`, `"%02hhx"` |

---

✅ **Level 0** — Core scalar types

| Name | Meaning |
| --- | --- |
| `size_t` | An **unsigned type** used to store sizes (like from `strlen()`, memory sizes). Defined in `<stddef.h>`. Often used in loops and memory functions. Scalar because any non-zero size is "true".🖨️ Print with: `"%zu"` (decimal), `"%zx"` (hex). |
| `double` | A **floating-point number** (like `3.14`, `-0.001`). Scalar because `0.0` is false; non-zero is true.🖨️ Print with: `"%f"` (fixed-point), `"%e"` (scientific notation). |
| `signed` (int) | A **signed integer** — can be negative, zero, or positive. Scalar: `0` is false, everything else is true.🖨️ Print with: `"%d"`. |
| `unsigned` | An **unsigned integer** — like `0`, `1`, `2`, but **never negative**. Scalar: `0` is false.🖨️ Print with: `"%u"` (decimal), `"%x"` (hex). |
| `bool` (`_Bool`) | A **boolean value**: either `true` (1) or `false` (0). Comes from `<stdbool.h>`. This is the **correct way** to represent truth values in modern C.🖨️ Print with: `"%d"` — prints as `0` or `1`. |

✅ **Level 1** — Pointers and character types

| Name | Meaning |
| --- | --- |
| `ptrdiff_t` | A signed integer that holds the **difference between two pointers** (e.g., `p2 - p1`). From `<stddef.h>`. Scalar: `0` = false.🖨️ Print with: `"%td"`. |
| `char const*` | A **string pointer**. Scalar: `NULL` (0) is false, any valid pointer is true.🖨️ Print with: `"%s"` (prints the pointed-to string). |
| `char` | A single character like `'a'`, `'Z'`, or `'\n'`. Scalar: `0` is false.🖨️ Print with: `"%c"` (as a character). |
| `void*` | A **generic pointer** to "any type". Scalar: `NULL` is false. Often used in low-level code.🖨️ Print with: `"%p"` (prints memory address). |

✅ **Level 2** — Raw bytes and low-level data

| Name | Meaning |
| --- | --- |
| `unsigned char` | A **byte-sized integer** (0–255). Often used for binary data, raw buffers, or flags. Scalar: `0` is false.🖨️ Print with: `"%hhu"` (decimal byte), `"%02hhx"` (2-digit hex with leading zero, e.g. `0a`, `ff`). |

Signed Unsigned: When there is a sign like + - its signed but when its unsigned its just a positive range

3.2 Iterations

For loop general form :  `for (clause1; condition2; expression3) statement-or-block` 
When writing a for loop, the **initialization clause (clause1)** should, **in most cases**, be a **variable definition** like `int i = 0` instead of just reusing a variable declared earlier.

Why? Because:

1. **Scoping** – The variable (`i`) only exists inside the `for` loop, which **prevents bugs** and keeps things tidy.
2. **Encapsulation** – This makes it clear that the variable is **only used for iteration**.
3. **Readability and maintainability** – It’s easier to see that the loop is self-contained and that `i` isn’t accidentally reused elsewhere.

### Ways to Write a for loop

```c
for (size_t i = 10; i; --i) {
    something(i);
}
```

This is a great pattern in embedded systems:

- Clear intent: iterate over something in reverse.
- Works well in **tight loops** for things like DMA buffers, timers, or polling loops.
- No extra comparisons → **slightly more efficient**.

### ✅ Why it’s elegant:

- Concise and idiomatic.
- `size_t` is unsigned, so we avoid issues with negative numbers.
- It avoids redundant comparisons like `i > 0`

💡 **Design Choice**: Use when you want to loop backward cleanly **without needing to access index 0**.

```c
for (size_t i = 0, stop = upper_bound(); i < stop; ++i) {
    something_else(i);
}
```

You’ll often see this when:

- `upper_bound()` is a **function call** or **expensive expression** (e.g., reading from hardware).
- You want to **cache a boundary** for speed or consistency.

### ✅ Why it’s elegant:

- Declaring `stop` inside the loop keeps its scope **local**.
- Prevents recomputing `upper_bound()` every iteration (which could be costly or side-effecty).
- Makes code **self-contained** and **readable**.

💡 **Design Choice**: Use this when your **loop bound is dynamic**, but you want to **optimize performance** and **isolate scope**.

```c
for (size_t i = 9; i <= 9; --i) {
    something_else(i);
}

```

   When its used?

### ⚠️ Why it's risky:

- This is a **clever hack**, but not obvious to readers.
- It depends on **unsigned integer wraparound**, which is **well-defined in C** — but not always good for clarity.
- This might be used in **low-level performance-critical** code (e.g., a loop unrolling trick or bit manipulation).
- But it’s also **hard to read**, and **easy to mess up**.
### Heron approximation to find inverse of x $(1/x)$

### **How You *Can* Build Intuition for It**

### **Step 1: Realize Division is Equivalent to Reciprocal + Multiplication**

Instead of computing **`1/a`** directly, think:

- *"What number **`x`** makes **`a * x = 1`**?"*
- Now it’s a **root-finding problem**: solve **`f(x) = a * x - 1 = 0`**.

### **Step 2: Newton’s Method for Root-Finding**

Newton’s method says:

- Start with a guess **`x₀`**.
- Improve the guess using: $x_{n+1}=x_n+\frac{f(x_n)}{f'(x_n)}$
- For **`f(x) = a * x - 1`**, the derivative is **`f'(x) = a`**.
- Plugging in: $x_{n+1}=x_n-\frac{ax_n-1}{a}=1/a$
    
    **Wait, this gives the exact solution immediately!** That’s no good—it still requires division by **`a`** (which we’re trying to avoid).
    

### **Step 3: Smarter Choice of `f(x)`**

Instead, use:

$f(x) = \frac{1}{x} - a$

- Now, the derivative is **`f'(x) = -1/x²`**.
- Newton’s update becomes:  
   $x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)} = x_n - \frac{\frac{1}{x_n} - a}{-\frac{1}{x_n^2}}$ $= x_n + x_n \left(1 - a x_n \right) = x_n (2 - a x_n)$
    
    **This is the Heron update rule!**
    
No division needed, just multiplications and subtractions.

### **Step 4: Why This Works**

- Each iteration **squares the error**, so convergence is **extremely fast**.
- Example: Computing **`1/34`** (from the code):
    - Start with **`x₀ = 0.5`** (guess).
    - Next guess: **`x₁ = 0.5 * (2 - 34 * 0.5) = 0.5 * (2 - 17) = -7.5`** (Oops, overshoot!)
    - But subsequent iterations stabilize quickly:
        - **`x₂ = -7.5 * (2 - 34 * -7.5) ≈ -7.5 * 257 ≈ -1927.5`** (diverges!)
    - **Problem:** The initial guess was bad. A better guess (like **`x₀ = 0.02`**) works:
        - **`x₁ = 0.02 * (2 - 34 * 0.02) ≈ 0.02 * (2 - 0.68) ≈ 0.0264`**
        - **`x₂ ≈ 0.0264 * (2 - 34 * 0.0264) ≈ 0.0292`**
        - Converges to **`~0.02941176`** (which is **`1/34`**).
### Heron Approximation using a while loop with a condition
```
# include <stdlib.h>
# include <stdio.h>
# include <tgmath.h>

int main(void){
    double eps=1E-9;
    double a=3.1415;
    double x=0.2414;
    while(fabs(1.0-a*x)>=eps){
        x*=2.0-a*x;
    }
    printf("The Approximation of %f is %.10f",a,x);
    return EXIT_SUCCESS;
}
```
