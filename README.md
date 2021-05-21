Extension of the [AtCoder Library](https://github.com/atcoder/ac-library).

### Library '#include's

Include the desired library, e.g. `#include <atcoder/segtree.hpp>` (do not use quotes). When ready to submit, run `./copy-full-src <solution_file>.cpp` to copy the full source to the clipboard.

### Testing against samples

This relies on the Competitive Companion chrome extension and [this app](https://github.com/gpane/cp-parser) to produce sample input and expected output files under `samples/`.

When the files are created, run `./test-samples.sh <solution-file>` to run the solution file against the samples.

### Brute force testing

`brute-testing/test.sh` takes 3 arguments:
1. Path to generator (cpp file that produces random problem inputs), probably `gen.cpp`.
2. Path to solution file.
3. Path to validation file (could be a naive implementation).
It will run until a discrepancy is found and produces in.txt, mine.txt, and theirs.txt for the problem input, solution output, and validation output, respectively.

### Clean slate

Run `./clean-slate` to reset problem and generator files.

### Libraries used
- [AtCoder Library](https://github.com/atcoder/ac-library)
- [Testlib](https://github.com/MikeMirzayanov/testlib)
