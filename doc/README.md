# Custom Implementation of `popen` and `pclose`

This project provides a custom implementation of the `popen` and `pclose` functions commonly found in UNIX-based systems. These functions allow the execution of shell commands from within a C program and handle inter-process communication through pipes.

## Files

- **main.c**: Demonstrates the usage of `mypopen` and `mypclose`.
- **mypopen.c**: Contains the implementation of the `mypopen` function.
- **mypclose.c**: Contains the implementation of the `mypclose` function.
- **mypopen_mypclose.h**: Header file declaring `mypopen` and `mypclose`.

## Usage

### Compilation

To compile the project, use the following command:

```sh
gcc main.c mypopen.c mypclose.c -o myprogram