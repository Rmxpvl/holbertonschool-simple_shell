# Simple Shell

A simple UNIX command line interpreter written in C.

## Description

This project is a minimal shell that reads and executes commands entered by the user. It handles interactive and non-interactive modes.

## Usage

### Compile

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Interactive mode

```bash
$ ./hsh
($) /bin/ls
($) /bin/pwd
($) exit
```

### Non-interactive mode

```bash
$ echo "/bin/ls" | ./hsh
$ echo "/bin/pwd" | ./hsh
```

## Features

- Displays a prompt in interactive mode
- Executes commands using their full path
- Prints an error message if the command is not found
- Handles end-of-file (Ctrl+D)

## Authors

- Remy Pinville
- Ilann Camelin
