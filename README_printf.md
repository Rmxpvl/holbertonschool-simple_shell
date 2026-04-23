# 🖨️ _printf

A custom implementation of the standard C library function `printf`. This project is a foundational milestone at **Holberton School**, designed to teach students the intricacies of variadic functions, string manipulation, and formatted output in C.

---

## 📋 Table of Contents
- [📖 Description](#-description)
- [🎯 Learning Objectives](#-learning-objectives)
- [⚙️ Requirements](#️-requirements)
- [🛠️ Compilation & Installation](#️-compilation--installation)
- [⚙️ Supported Specifiers](#️-supported-specifiers)
- [🚀 Usage Examples](#-usage-examples)

---

## 📖 Description
The `_printf` function writes output to standard output (the console) under the control of a `format` string that specifies how subsequent arguments are converted for output. 

**Prototype:**
```c
int _printf(const char *format, ...);
```
**Return Value:**
Upon successful return, this function returns the number of characters printed (excluding the null byte used to end output to strings). If an output error is encountered, a negative value is returned.

## 🎯 Learning Objectives
- Understanding and using **variadic functions** (using `stdarg.h`).
- Deep diving into memory allocation and string manipulation without standard library shortcuts.
- Replicating the behavior of one of the most widely used C functions.

## ⚙️ Requirements
- Environment: **Ubuntu 20.04 LTS**
- Compiler: `gcc` with strict flags (`-Wall -Werror -Wextra -pedantic -std=gnu89`)
- Coding Style: Strict adherence to the **Betty linter** (maximum of 40 lines per function, maximum 5 functions per file).
- No global variables.
- Allowed standard functions: `write`, `malloc`, `free`, `va_start`, `va_end`, `va_copy`, `va_arg`.

## 🛠️ Compilation & Installation
To use the `_printf` function in your programs, include the main header file (`main.h` or `holberton.h`) and compile all `.c` files together.

```bash
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o my_printf
```

## ⚙️ Supported Specifiers
Our `_printf` securely handles the following conversion specifiers:

| Specifier | Description | Example Output |
|-----------|-------------|----------------|
| **`%c`**  | Prints a single character | `A` |
| **`%s`**  | Prints a string of characters | `Holberton` |
| **`%%`**  | Prints a literal percent sign | `%` |
| **`%d`**  | Prints a base 10 decimal integer | `1024` |
| **`%i`**  | Prints an integer | `-42` |

*(Note: Advanced formatting like width, precision, or flags might be present depending on the specific project milestone).*

## 🚀 Usage Examples

**Code:**
```c
#include "main.h"

int main(void)
{
    int len;

    _printf("Let's print a simple sentence.\n");
    
    _printf("Character: %c\n", 'H');
    
    _printf("String: %s\n", "Hello Holberton!");
    
    len = _printf("Numbers: %d, %i\n", 98, -1024);
    _printf("Length of the previous string: %d\n", len);

    return (0);
}
```

**Output:**
```text
Let's print a simple sentence.
Character: H
String: Hello Holberton!
Numbers: 98, -1024
Length of the previous string: 18
```

---
*Authored with precision for Holberton School.*
