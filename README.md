# Tertium
Tertium is a general-purpose library for C that aims to provide a simple and secure environment that produces more reliable software.

[How to build](https://eltaninos.org/?docs/build)

## Modules
* adt: abstract data types
* arr: generic static array
* cal: calendar dates
* cdb: constant database
* dir: directory recursion
* dyn: generic dynamic array
* err: formatted error messages
* exc: external binaries execution
* fmt: user-defined formattation
* gen: pattern matching
* hsh: checksum and cryptographic hashes
* ioq: buffered i/o
* mem: operations on memory
* nix: \*nix routines and utilities
* rand: random data, numbers and strings
* std: general routines
* str: operations on C string
* sys: typed syscalls
* tai: tai time
* taia: atto-second precision tai time
* uint: portable unsigned integer storage

## Credits
Part of the API and code is inspired/copied from the public domain libraries written by Daniel J. Bernstein.
https://cr.yp.to/

The hsh cryptographic routines uses code from the public domain library tomcrypt.
https://www.libtom.net/LibTomCrypt/
