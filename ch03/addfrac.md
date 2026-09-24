# Exercise 6 + PP6

## Part A — book version, format "%d/%d", sentinel -999

Predictions were made in chat before writing the code (case 2 predicted wrong:
expected 5, 6, 7, 1 in the variables).

| # | Input                  | scanf #1 | scanf #2 | num1 | denom1 | num2 | denom2 | Sum            | Left in buffer |
|---|------------------------|----------|----------|------|--------|------|--------|----------------|----------------|
| 1 | `5/6`, then `3 /4`     | 2        | 1        | 5    | 6      | 3    | -999   | -4977/-5994    | ` /4\n`        |
| 2 | `5/6/7`, then `1/2`    | 2        | 0        | 5    | 6      | -999 | -999   | -10989/-5994   | `/7\n`         |
| 3 | `-5/-6`, then `3/4`    | 2        | 2        | -5   | -6     | 3    | 4      | -38/-24        | `\n`           |
| 4 | `5/6 3/4` in one line  | 2        | 2        | 5    | 6      | 3    | 4      | 38/24          | `\n`           |

Cases 1 and 2 must be re-run with the -999 version (first run used 0 as the
initial value, so "not written" and "read 0" looked the same).

### Observations

- Case 2: the second scanf did not wait for input. The program exited, and the
  `1/2` I typed went to bash (`bash: 1/2: No such file or directory`).
- Case 4: the prompt "Enter second fraction:" appeared and passed without a pause.
- Case 3: `%d` accepts a sign, so -5 and -6 are ordinary numbers.
  The sum -38/-24 is mathematically correct, just not normalized.

### Conclusions

- Every scanf call reads from the same input buffer. What one call does not
  consume stays there for the next call.
- scanf follows the format left to right and stops in two cases:
  a mismatch (case 1: format wants `/`, input has a space)
  or the end of the format (case 2: `/7` is left over after `%d/%d`).
- `%d` skips leading whitespace (spaces, `\n`) on its own; an ordinary character
  such as `/` must match exactly. That is why a space is fine before a number
  (case 4) but breaks the input before `/` (case 1).
- If the buffer holds only whitespace, the next `%d` skips it and waits for
  input. If anything else is left, the next scanf starts on it immediately.
- The return value counts assigned VARIABLES, not characters:
  `-56` for `%d` is one item.
- A variable scanf did not write keeps its old value. Without an obvious sentinel
  (-999) a failed read looks like valid data.


## Part B — exercise 6, format "%d /%d"

No predictions: the format was chosen as "the only logical one", the reason
why it works was understood only after the runs.

| # | Input                  | scanf #3 | scanf #4 | num3 | denom3 | num4 | denom4 | Sum   |
|---|------------------------|----------|----------|------|--------|------|--------|-------|
| 1 | `5 / 6`, then `3/4`    | 2        | 2        | 5    | 6      | 3    | 4      | 38/24 |
| 2 | `5/6`, then `3 / 4`    | 2        | 2        | 5    | 6      | 3    | 4      | 38/24 |
| 3 | `5/ 6`, then `3 /4`    | 2        | 2        | 5    | 6      | 3    | 4      | 38/24 |

### Conclusions

- A format string has three kinds of elements:
  - `%d` skips leading whitespace by itself, then reads a number;
  - a space skips ANY amount of whitespace in the input, including zero;
  - an ordinary character (`/`) must match exactly, otherwise scanf stops.
- A space in the format is not "a space must be here", it is
  "skip whitespace here if there is any".
- The space is needed only BEFORE `/`: `/` skips nothing on its own.
  After `/` it is not needed: the next `%d` skips whitespace itself.
  So `"%d /%d"` and `"%d / %d"` behave the same, `"%d/ %d"` breaks on `5 /6`.
- Exception to remember: `%c` does NOT skip whitespace, it reads any next
  character, including a space or `\n`.


## Part C — PP6, format "%d/%d +%d/%d", one scanf call

| # | Input         | scanf #5 | num5 | denom5 | num6 | denom6 | Sum   |
|---|---------------|----------|------|--------|------|--------|-------|
| 1 | `5/6+3/4`     | 4        | 5    | 6      | 3    | 4      | 38/24 |
| 2 | `5/6 + 3/4`   | 4        | 5    | 6      | 3    | 4      | 38/24 |
| 3 | `5/6+-3/4`    | 4        | 5    | 6      | -3   | 4      | 2/24  |

- The space before `+` in the format lets `5/6 + 3/4` work (same rule as in Part B).
- Case 3: the format's `+` matches the plus, then `%d` reads `-3` as a signed number.

### Bug found

The first runs printed 24/38 and 24/2: the names of the numerator and the
denominator were swapped when the variables were renamed (in Parts B and C).
Not noticed at first, although:
- 5/6 + 3/4 > 1, so the numerator must be larger than the denominator
  (sanity check);
- Part A computed the same sum as 38/24 — two versions of one calculation
  disagreed.

### Prediction: format "%d/%d%d/%d" (no '+'), input 5/6+3/4

My prediction: scanf reads 5/6, `+3/4` stays in the buffer because `+` is not
in the format.
Actual: <fill in after the run>
Why: `+` is a valid sign for `%d`, so the third `%d` reads `+3`.
Without `+` in the format, `5/6-3/4` is also accepted: the minus becomes
the sign of the number.
