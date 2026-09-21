# c-learning

Learning C from the ground up, with a focus on embedded systems.

The goal is to write C confidently without AI assistance and to understand
what happens at the machine level. Exercises are done by hand; AI is used
only for reviewing already-written code.

## Main book

K. N. King, *C Programming: A Modern Approach*, 2nd edition (C89/C99).

## Repository structure

```
c-learning/
├── notes.md      # learning journal
├── ch02/         # programs and exercises for chapter 2
├── ch03/
└── ...
```

Each `chNN/` folder contains programs for the corresponding chapter of the book.

## Build

All programs are built with strict warnings and runtime sanitizers:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined file.c -o file
./file
```

## Environment

Ubuntu LTS, gcc, gdb, VS Code (clangd, AI features disabled), git.

## Progress

- [x] Chapter 1 — Introducing C
- [ ] Chapter 2 — C Fundamentals
- [ ] Chapter 3 — Formatted Input/Output
- [ ] Chapter 4 — Expressions
- [ ] Chapter 5 — Selection Statements
- [ ] Chapter 6 — Loops
- [ ] Chapter 7 — Basic Types
- [ ] Chapter 8 — Arrays
- [ ] Chapter 9 — Functions
- [ ] Chapter 10 — Program Organization
