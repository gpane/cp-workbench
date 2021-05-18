Extension of the [AtCoder Library](https://github.com/atcoder/ac-library)

Added some additional library code under atcoder/. Also added tester/, to facilitate testing of solutions.

AtCoder Library Usage: Include the desired library, e.g. `#include <atcoder/segtree.hpp>`. When ready to submit, run `./copy-full-src <solution_file>.cpp` to copy the full source to the clipboard.

`testing/test.sh` takes 3 arguments:
1. Path to generator (cpp file that produces random problem inputs), probably `gen.cpp`.
2. Path to solution file.
3. Path to validation file (could be a naive implementation).
It will run until a discrepancy is found and produces in.txt, mine.txt, and theirs.txt for the problem input, solution output, and validation output, respectively.

Libraries used:
- [AtCoder Library](https://github.com/atcoder/ac-library)
- [Testlib](https://github.com/MikeMirzayanov/testlib)
