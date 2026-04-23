# 🐚 Simple Shell (`hsh`)

A minimalist UNIX command line interpreter strictly written in standard C89 (GNU89). This project is a major milestone within the curriculum of **Holberton School**, challenging students to program a functional shell from scratch. It heavily relies on an in-depth understanding of the Linux environment, system calls, and process management.

---

## 📋 Table of Contents
- [📖 Description](#-description)
- [🎯 Learning Objectives](#-learning-objectives)
- [⚙️ Requirements](#️-requirements)
- [🛠️ Compilation & Installation](#️-compilation--installation)
- [🚀 Usage](#-usage)
  - [Interactive Mode](#interactive-mode)
  - [Non-Interactive Mode](#non-interactive-mode)
- [🧩 Features & Built-ins](#-features--built-ins)
- [📂 Architecture & File Structure](#-architecture--file-structure)
- [Authors](#authors)

---

## 📖 Description
The `hsh` program is a custom shell that mirrors the core functionalities of `/bin/sh` (Bourne standard shell). It continuously reads user inputs, parses them into executable tokens, searches for legitimate binaries resolving via the `$PATH` environment variable, and creates discrete child processes to execute these binaries securely.

## 🎯 Learning Objectives
By designing this shell, we master:
- How a shell works under the hood.
- **Process Creation & Execution:** Mastery of `fork()`, `execve()`, and `waitpid()`.
- **System Calls:** Direct kernel instructions like `stat`, `access`, `read`, and `write`.
- **Memory Management:** Zero memory leaks strategy, ensuring all allocations (`malloc`, `getline`) are cleanly freed (`free`).
- **Data Parsing:** Efficient manipulation of pointers, strings, and tokenization using `strtok()`.

## ⚙️ Requirements
- Ensure you are working on an **Ubuntu 20.04 LTS** environment.
- Code meticulously follows the **Betty linter** coding standard (max 40 lines/function, max 5 functions/file).
- Strict compiler constraints (no warnings or errors allowed).

## 🛠️ Compilation & Installation
Clone the repository and compile using the following mandatory Holberton `gcc` flags:

```bash
$ git clone https://github.com/Rmxpvl/holbertonschool-simple_shell.git
$ cd holbertonschool-simple_shell
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## 🚀 Usage

The shell supports both forms of standard input readings beautifully.

### Interactive Mode
Launch the executable. You will be greeted by the `($)` prompt waiting for commands.
```bash
$ ./hsh
($) pwd
/home/user/holbertonschool-simple_shell
($) ls -l
total 72
-rw-r--r-- 1 user user   142 Apr 21 00:00 Makefile
-rwxr-xr-x 1 user user 18048 Apr 21 00:00 hsh
-rw-r--r-- 1 user user  1203 Apr 21 00:00 execute.c
($) exit
$
```

### Non-Interactive Mode
Can be used effectively via pipes and scripts.
```bash
$ echo "ls -l" | ./hsh
total 72
-rw-r--r-- 1 user user   142 Apr 21 00:00 Makefile
-rwxr-xr-x 1 user user 18048 Apr 21 00:00 hsh
-rw-r--r-- 1 user user  1203 Apr 21 00:00 execute.c
$

$ cat init_script.txt | ./hsh
```

## 🧩 Features & Built-ins
**Command Execution:**
- Executes programs securely using absolute routes (`/bin/ls`).
- Executes programs via variable path resolution (`ls` automatically expands to `/bin/ls`).
- Mirrors exact Error Outputs corresponding to `/bin/sh` (Error 127: Not found, Error 126: Permission denied).

**Supported Built-ins:**
- `exit` : Simply terminates the shell loop with the last command status.
- `env` : Traverses and prints the current system environment variables seamlessly (`$ environ`).

## 📂 Architecture & File Structure
All source functions strictly reside at the repository root, maximizing compilation interoperability while remaining fully modularized:

| File | Description & Functions |
|------|-------------|
| **`shell.h`** | Main header file. Holds standard libraries, structs, `#define` macros, and prototyping for all files. Exposes `extern char **environ;`. |
| **`shell.c`** | Contains the infinite entry loop (`run_shell`). Captures input strings, trims carriage returns, and triggers command arrays. |
| **`execute.c`** | The execution pipeline. Forks the core process and applies `execve()`. Encompasses edge-error handling identical to `sh`. |
| **`path.c`** | PATH resolver. Splits `$PATH` values via `:` delimiters and concatenates user commands to check for binary `access()`. |
| **`_getenv.c`** | A robust localized utility acting exactly like `getenv()` mapping OS-provided env arrays autonomously. |
| **`VERSION`** | Safe-tracker file indicating shell version progress (Currently v1.0). |

---
## Authors
Remy Pinville https://github.com/Rmxpvl
Ilyan Camelin https://github.com/kaiserr999
