# 🐚 Simple Shell (`hsh`)

A simple UNIX command interpreter written in C. This project is a major milestone at Holberton School designed to understand the inner workings of a shell, including process creation, system calls, and environment variable manipulation.

## 📋 Table of Contents
- [Description](#-description)
- [Compilation & Installation](#-compilation--installation)
- [Architecture & File Structure](#-architecture--file-structure)
- [Usage Examples](#-usage-examples)
- [Supported Built-ins](#-supported-built-ins)

---

## 📖 Description
`hsh` is a minimalist shell that mimics the basic core functionalities of `/bin/sh` (Bourne Shell). It features an essential command execution loop: reading user input, parsing it into valid tokens, resolving the binary from the `$PATH`, and safely executing commands via child processes.

## 🛠️ Compilation & Installation
The shell is built to be strictly compiled on Ubuntu 20.04 LTS using `gcc` with standard Holberton School flags to ensure 0 memory leaks and strict C89 standard compliance.

```bash
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## 📂 Architecture & File Structure
To satisfy the automatic checker compilation constraint (`gcc *.c`), all source codes remain at the repository root but are highly modularized:

* **`shell.h`** : The central header file. Contains all function prototypes, necessary standard headers, macro definitions, and the global `environ` declaration.
* **`shell.c`** : The core loop. Reads inputs via `getline()`, handles tokenization via `strtok()`, and intercepts built-in commands.
* **`execute.c`** : The process factory. Manages `fork()`, runs binaries with `execve()`, and strictly mimics `/bin/sh` standard error messages.
* **`path.c`** : The pathfinder. Parses the `$PATH` variable and locates executable binaries using the `access()` and `stat()` system calls.
* **`_getenv.c`** : Custom utility to safely retrieve values from the environment variables without relying on the libc `getenv()`.

## 🚀 Usage Examples

The Simple Shell handles both interactive and non-interactive modes seamlessly.

### Interactive Mode
```bash
$ ./hsh
($) /bin/ls -l
total 64
-rw-r--r-- 1 user user   142 Apr 21 00:00 Makefile
-rwxr-xr-x 1 user user 18048 Apr 21 00:00 hsh
-rw-r--r-- 1 user user  1203 Apr 21 00:00 execute.c
($) exit
$
```

### Non-Interactive Mode
```bash
$ echo "ls -l" | ./hsh
total 64
-rw-r--r-- 1 user user   142 Apr 21 00:00 Makefile
-rwxr-xr-x 1 user user 18048 Apr 21 00:00 hsh
-rw-r--r-- 1 user user  1203 Apr 21 00:00 execute.c
$
```

## ⚙️ Supported Built-ins
Currently, `hsh` supports the following internal commands:
* **`exit`** : Terminates the shell immediately.
* **`env`** : Prints the current environment variables to standard output.

---
*Authored with precision for Holberton School.*
