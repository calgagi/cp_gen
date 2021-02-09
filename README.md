# cp\_gen

A modular and robust application to create competitive programming templates.

## Install
* You must be using Linux since this program uses a syscall (`readlink`) that is only available on Linux. WSL should work as well.
* Run `make` to compile the program. It should produce a binary called `gen`. 
* If you want to use `gen` from anywhere, add the directory `cp_gen` to your path. Please make sure that `gen` is in the root directory of this repo since it requires reading/writing library files to templates.

## Usage
* Simply enter `gen $FILENAME` to generate a C++ file. `$FILENAME` is required.
* Everything above the `cp` namespace is unchangeable unless you modify `main.cpp` (feel free to).
* Everything after the `cp` namespace is outputted from `user.cpp` in this repo. You can freely modify this file to your liking. <b>Make sure it includes a main function!</b>
* Everything in the `cp` namespace is outputted from `./lib/$DS.hpp` where you can specify which `$DS`s you want to be included.
* Example: `gen A.cpp -$DS1 -$DS2` will include everything from `./lib/DS1.hpp` and `./lib/DS2.hpp` in the `cp` namespace.

## Examples
* `gen X.cpp -dsu` will include the Disjoint Set Union data structure and generate a file called `X.cpp` in the current working directory.
* `gen ..\above.cpp` will generate a file called `above.cpp` in the directory above the current working directory.
* `gen A.cpp -segtree -num` will include everything from `./lib/segtree.hpp` and `./lib/num.hpp` into `A.cpp`.

## Data Structures
#### dsu: Disjoint Set Union (Union Find)
| Function | Description | Runtime |
| --------------------- | -------------------- | ------ |
| `dsu(int size)` | creates a dsu data structure with size `size` | O(size) |
| `int find(int node)` | returns the connected component that `node` belongs to | O(log(size)) |
| `void unite(int node1, int node2)` | if not already united, connects `node1` and `node2` so that the connected components that they are a part of form a single connected component | O(log(size)) |

#### avl: Multi-set using AVL tree
| Function | Description | Runtime |
| --------------------- | -------------------- | ------ |
| `avl<type>()` | creates an empty avl tree that holds data of type `type`; `type` must have `operator<` defined | O(1) |
| `int before(type val)` | finds the amount of items in the set that have strictly less-than value than `val` | O(log(size)) |
| `int size()` | returns the amount of items in the set | O(1) |
| `void insert(type val)` | inserts `val` into the set | O(log(size)) |
| `void remove(type val)` | removes a single instance of `val` in the set | O(log(size)) |
| `int count(type val)` | returns the number of instances of `val` in the set | O(log(size)) |
| `type* closestlt(type val)` | returns a pointer to an instance of the closest strictly less-than value than `val`, or `null` if no such value exists | O(log(size)) |
| `type* closestgt(type val)` | returns a pointer to an instance of the closest strictly greater-than value than `val`, or `null` if no such value exists | O(log(size)) |

#### segtree: Policy-based Segment Tree
| Function | Description | Runtime |
| --------------------- | -------------------- | ------ |
| `segtree<type>(int size, type identity, function<type(type, type)>) combine)` | creates a tree of size `4*size` of which all elements are equal to `identity`; `combine` is the function used to combine two tree nodes (your `combine(identity, x) = x` for all `x`) | O(size) |
| `void update(int pos, type val)` | updates the value at `pos` to `val` | O(log(size)) |
| `type query(int left, int right)` | returns the range query defined by `combine` in the range [`left`, `right`] | O(log(size)) |

## Tests 
* To run tests, run `make tests`.
* If you're interested in adding your own templates and tests, check out `./tests/README.md`.
