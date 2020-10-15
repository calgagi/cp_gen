# cp\_gen

A modular and robust application to create competitive programming templates.

## Install
* Note: must be using Linux since this program uses a syscall (`readlink`) that is only available on Linux.
* Run `make` to compile the program. It should produce a binary called `.\gen`. 
* Add `gen` to your path.

## Testing
* To run tests, run `make tests`.
* If you're interested in adding your own templates and tests, check out `.\tests\README.md`.

### Arguments
* `filename.cpp` (<b>REQUIRED</b>): Creates file in current working directory called `filename.cpp` with template contents outputted to it.

* `-c`: Adds printing each test case number.
* `-u`: Adds USACO things.
* `-<ds>`: Adds contents from `lib/<ds>.hpp` to top of file.

### Examples

* `gen A.cpp`: Creates a generic template named `A.cpp`
* `gen -c -pbavl B.cpp`: Creates a template that prints each test case number and has `./lib/pbavl.hpp` pasted at the top of the file (after includes).