#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Usage: ./test-samples.sh <solution-file>"
    exit 2
fi

src_path=$1
src_noext="${src_path%.*}"

cpp-build/perf_build "$src_path" .

echo
failed=false
for input_file in samples/input*;
do
  output_file="${input_file/input/output}"
  expected_output_file="${input_file/input/expected-output}"

  # trim expected output
  cp "$expected_output_file" "${expected_output_file}_copy"
  xargs < "${expected_output_file}_copy" > "$expected_output_file"
  rm "${expected_output_file}_copy"

  # run program, produce output file
  (./"$src_noext" < "$input_file") | xargs > "$output_file"

  if ! cmp -s "$output_file" "$expected_output_file"; then
    failed=true
    echo Incorrect result for input:
    cat "$input_file"
    echo
    echo Expected:
    cat "$expected_output_file"
    echo
    echo Got:
    cat "$output_file"
    echo
    break
  fi
done

if ! "$failed"; then
  echo All samples passed
fi

rm "${src_noext}"
rm -rf "${src_noext}.dSYM"
