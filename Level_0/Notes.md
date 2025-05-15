### What are Toolchains?

Compile it on your machine **using a toolchain for the target machine**

```cpp
arm-linux-gnueabi-gcc program.c -o program
```

Then **transfer the binary** to the target device and run it.

Run a C file using `gcc -Wall -lm -o main get-start.c`  
Use of -Wall (warn any unusual things) and -lm (add necessary math functions if required)
