#!/bin/bash

generator_path=$1
my_src_path=$2
their_src_path=$3

generator_noext="${generator_path%.*}"
my_src_noext="${my_src_path%.*}"
their_src_noext="${their_src_path%.*}"

## build
~/Dropbox/bin/perf_build ${generator_path} ..
~/Dropbox/bin/perf_build ${my_src_path} ..
~/Dropbox/bin/perf_build ${their_src_path} ..

rm in.txt
rm mine.txt
rm theirs.txt

## run
while [[ ! -f mine.txt ]] || cmp -s mine.txt theirs.txt
do
./${generator_noext} > in.txt
./${my_src_noext} < in.txt > mine.txt
./${their_src_noext} < in.txt > theirs.txt
#java ${their_src_noext} < in.txt > theirs.txt
done
