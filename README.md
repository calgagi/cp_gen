# cp\_gen

My program to create competitive programming templates.

Just run `make` to compile the program. Add `gen` to your path, and *boom* you can generate files.

To run tests, run `make tests`. You can check out how to create tests for your own classes under `tests/Makefile` (TODO: make `tests` README)

### Arguments
* `filename.cpp` (<b>REQUIRED</b>): Creates file in current working directory called `filename.cpp` with template contents outputted to it.
* `-c`: Adds printing each test case number.
* `-u`: Adds USACO things.

### Example

`gen A.cpp`