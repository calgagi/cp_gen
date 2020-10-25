# cp\_gen

A modular and robust application to create competitive programming templates.

## Install
* Note: must be using Linux since this program uses a syscall (`readlink`) that is only available on Linux.
* Run `make` to compile the program. It should produce a binary called `./gen`. 
* Add `cp_gen` to your path. Please make sure that `gen` is in the root directory of this repo since reading/writing library files to templates requires that.

## Data Structures
#### dsu: Disjoint Set Union (Union Find)
* `dsu(int size)`: creates a dsu data structure with size `size`
* `int find(int node)`: returns the connected component that `node` belongs to in O(log(size)) time
* `void unite(int node1, int node2)`: if not already united, connects `node1` and `node2` so that the connected components that they are a part of form a single connected component

#### avl: AVL Tree Multi-set
* `avl<type>()`: creates an empty avl tree that holds data of type `type`; `type` must have `operator<` defined
* `int before(type val)`: finds the amount of items in the set that are of lesser than or equal value to `val` in O(log(size))
* `int size()`: returns the amount of items in the set 
* `void insert(type val)`: inserts `val` into the set in O(log(size))
* `void remove(type val)`: removes a single instance of `val` in the set in O(log(size))
* `int count(type val)`: returns the number of instances of `val` in the set in O(log(size))

#### segtree: Policy-based Segment Tree
* `segtree<type>(int size, type identity, function<type(type, type)>) combine)`: creates a tree of size `4*size` of which all elements are equal to `identity`; `combine` is the function used to combine two tree nodes (your `combine(identity, x) = x` for all `x`)
* `void update(int pos, type val)`: updates the value at `pos` to `val` in O(log(size))
* `type query(int left, int right)`: returns the range query defined by `combine` in the range [`left`, `right`] in O(log(size))

## Testing
* To run tests, run `make tests`.
* If you're interested in adding your own templates and tests, check out `./tests/README.md`.

## Arguments
* `filename.cpp` (<b>REQUIRED</b>): Creates file in current working directory called `filename.cpp` with template contents outputted to it.

* `-c`: Adds printing each test case number.
* `-u`: Adds USACO things. Expects `username` directly afterwards. For example, `-u calgagi`.
* `-<ds>`: Adds contents from `lib/<ds>.hpp` to top of file.

## Examples

* `gen A.cpp`: Creates a generic template named `A.cpp`
* `gen -c -avl B.cpp`: Creates a template that prints each test case number and has `./lib/avl.hpp` pasted at the top of the file (after includes).
