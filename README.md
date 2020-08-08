# nokia_csv
CSV solver for Nokia internship

# About
The program reads an arbitrary CSV form from a file (the number of rows and columns can be any), calculates cell values, and outputs the resulting table as a CSV representation to the console.

# Tests
* example.csv - Nokia's test
* fib.csv - Fibonacci numbers
* degrees.csv - table of degrees
* crash_nested.csv - error using a nested cell (the order of operations is not being built, so cells with nested formulas will not be counted)
* div_zero.csv - error dividing by zero

# Results
* example.csv

| | A  | B | Cell
| ------------- | ------------- | ------------- | ------------- |
| 1 | 1 | 0 | 1 |
| 2 | 2 | 6 | 0 |
| 30 | 0 | 1 | 5 |

* fib.csv

|   | A | B | C | D | E | F | G | H  | I  | J  | K  | L  | M   | N   | O   | P   | Q   | R    | S    | T    | U    | V     | W     | X     | Y     | Z     |
|---|---|---|---|---|---|---|---|----|----|----|----|----|-----|-----|-----|-----|-----|------|------|------|------|-------|-------|-------|-------|-------|
| 1 | 0 | 1 | 1 | 2 | 3 | 5 | 8 | 13 | 21 | 34 | 55 | 89 | 144 | 233 | 377 | 610 | 987 | 1597 | 2584 | 4181 | 6765 | 10946 | 17711 | 28657 | 46368 | 75025 |

* degrees.csv

|   | A | B   | C     | D      | E       | F        | G        | H         | I         | J          |
|---|---|-----|-------|--------|---------|----------|----------|-----------|-----------|------------|
| 1 | 1 | 2   | 3     | 4      | 5       | 6        | 7        | 8         | 9         | 10         |
| 2 | 1 | 4   | 9     | 16     | 25      | 36       | 49       | 64        | 81        | 100        |
| 3 | 1 | 8   | 27    | 64     | 125     | 216      | 343      | 512       | 729       | 1000       |
| 4 | 1 | 16  | 81    | 256    | 625     | 1296     | 2401     | 4096      | 6561      | 10000      |
| 5 | 1 | 32  | 243   | 1024   | 3125    | 7776     | 16807    | 32768     | 59049     | 100000     |
| 6 | 1 | 64  | 729   | 4096   | 15625   | 46656    | 117649   | 262144    | 531441    | 1000000    |
| 7 | 1 | 128 | 2187  | 16384  | 78125   | 279936   | 823543   | 2097152   | 4782969   | 10000000   |
| 8 | 1 | 256 | 6561  | 65536  | 390625  | 1679616  | 5764801  | 16777216  | 43046721  | 100000000  |
| 9 | 1 | 512 | 19683 | 262144 | 1953125 | 10077696 | 40353607 | 134217728 | 387420489 | 1000000000 |


* crash_nested.csv - returns error **Nested cell contain symbols**

Cells are counted sequentially, so the value **B2** cannot be used in **B1**. This can be fixed by defining the order of operations (for example, building a suffix tree).

|   | A     | B     | C | D |
|---|-------|-------|---|---|
| 1 | 1     | 2     | 3 | 4 |
| 2 | **=B2+1** | **=B3+2** | 3 | 4 |
| 3 | 1     | 2     | 3 | 4 |

* div_zero.csv — returns error **Dividing by zero**

|   | A      | B | C |
|---|--------|---|---|
| 1 | 0      | 1 | 1 |
| 2 | **=B1/A1** | 1 | 1 |
