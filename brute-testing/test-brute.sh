#!/bin/bash

# run from within brute-testing directory -- TODO allow other dirs

if [[ $# -ne 3 ]]; then
  echo "Usage ./test-brute.sh <gen-file> <solution-file> <validation-file>"
  exit 2
fi

generator_path=$1
my_src_path=$2
their_src_path=$3

generator_noext="${generator_path%.*}"
my_src_noext="${my_src_path%.*}"
their_src_noext="${their_src_path%.*}"

## build
../cpp-build/perf_build "${generator_path}" ..
../cpp-build/perf_build "${my_src_path}" ..
../cpp-build/perf_build "${their_src_path}" ..

# don't report if it doesn't exist - a bit overkill but it works
rm -f in.txt
rm -f mine.txt
rm -f theirs.txt

## run
iters=0
while [[ ! -f mine.txt ]] || cmp -s mine.txt theirs.txt
do
  if ((iters > 0)) && ((iters % 100 == 0)); then
    echo Passed "$iters tests"
  fi
  ((iters++))

  ./"${generator_noext}" > in.txt
  (./"${my_src_noext}" < in.txt) | xargs > mine.txt
  (./"${their_src_noext}" < in.txt) | xargs > theirs.txt
  #java ${their_src_noext} < in.txt > theirs.txt
done

rm "${generator_noext}"
rm -rf "${generator_noext}.dSYM"
rm "${my_src_noext}"
rm -rf "${my_src_noext}.dSYM"
rm "${their_src_noext}"
rm "${their_src_noext}.dSYM"
