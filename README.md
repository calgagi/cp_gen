# cp\_gen

A modular and robust application to create competitive programming templates.

## Install
* You must be using Linux since this program uses a syscall (`readlink`) that is only available on Linux. WSL should work as well.
* Run `make` to compile the program. It should produce a binary called `gen`. 
* If you want to use `gen` from anywhere, add the directory `cp_gen` to your path. Please make sure that `gen` is in the root directory of this repo since it requires reading/writing library files to templates.

## Usage
* Simply enter `gen $FILENAME` to generate a C++ file. `$FILENAME` is required.
* The header for generated files is unchangeable unless you modify `main.cpp` (feel free to).
* Everything after the `BEGIN USER CODE` line in the generated file is outputted from `user.cpp` in this repo. You can freely modify this file to your liking. <b>Make sure it includes a main function!</b>
* Everything after the headers and before `BEGIN USER CODE` is outputted from `./lib/$DS.hpp` where you can specify which `$DS`s you want to be included.

## Examples
* `gen X.cpp -dsu` will include the Disjoint Set Union data structure and generate a file called `X.cpp` in the current working directory.
* `gen ..\above.cpp` will generate a file called `above.cpp` in the directory above the current working directory.
* `gen A.cpp -segtree -num` will include everything from `./lib/segtree.hpp` and `./lib/num.hpp` into `A.cpp`.
* `gen my_program.cpp -num` will include everything from `./lib/num.hpp` in `my_program.cpp`.

## Tests 
* To run tests, run `make tests`.
* If you're interested in adding your own templates and tests, check out `./tests/README.md`.
