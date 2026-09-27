# c-learning

Learning C from the ground up, with a focus on embedded systems.

The goal is to write C confidently without AI assistance and to understand
what happens at the machine level. Exercises are done by hand; AI is used
only for reviewing already-written code.

## Main book

K. N. King, *C Programming: A Modern Approach*, 2nd edition (C89/C99).

Code is compiled as C17: it is closer to embedded practice (STM32CubeIDE
defaults to gnu11), and the book's C99 code compiles without changes.

## Repository structure

```
c-learning/
├── notes.md      # learning journal
├── ch02/         # programs and exercises for chapter 2
├── ch03/
├── ...
└── mini_projects/  # small hands-on projects outside the book
    └── traffic_light/
```

Each `chNN/` folder contains programs for the corresponding chapter of the book.
Each `mini_projects/<name>/` folder is a self-contained project with its own
notes file; the main journal only links to it.

## Build

All chapter programs are built with strict warnings and runtime sanitizers:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Og -g -fsanitize=address,undefined file.c -o file
./file
```

`-Og` enables the optimizer's data-flow analysis (needed for some warnings,
e.g. `-Wmaybe-uninitialized`) while keeping the program debuggable in gdb.

## Environment

Ubuntu LTS, gcc, gdb, VS Code (clangd, AI features disabled), git.

## Progress

- [x] Chapter 1 — Introducing C
- [x] Chapter 2 — C Fundamentals
- [ ] Chapter 3 — Formatted Input/Output
- [ ] Chapter 4 — Expressions
- [ ] Chapter 5 — Selection Statements
- [ ] Chapter 6 — Loops
- [ ] Chapter 7 — Basic Types
- [ ] Chapter 8 — Arrays
- [ ] Chapter 9 — Functions
- [ ] Chapter 10 — Program Organization

## Mini projects

Hands-on projects that apply C to real (or simulated) hardware. They are not
built with the `gcc` command above: each project describes its own toolchain.

- [ ] `traffic_light/` — traffic light with a pedestrian phase on request
  (STM32 Nucleo-C031C6, simulated in Wokwi). Bare-register C via CMSIS:
  GPIO, timers, ADC. University lab assignment.
  - [x] Circuit and pin mapping
  - [x] GPIO: clocks, pin modes, LEDs
  - [x] Timer: TIM3, polling the update flag
  - [ ] Timer interrupt and 1 ms tick
  - [ ] ADC (potentiometer)
  - [ ] Button with debouncing
  - [ ] Traffic light state machine
  - [ ] Buzzer
