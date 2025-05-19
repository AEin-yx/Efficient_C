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
