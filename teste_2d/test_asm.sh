#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <program.s>"
    exit 1
fi

program="$1"
basename=$(basename "$program" .s)

echo "Compiling assembly program..."
gcc -m32 "$program" -o "$basename" 

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

test_number=1


for input_file in *.in; do
    expected_output="${input_file%.in}.ok"
    output_file="${basename}_output.txt"
    
    if [ ! -f "$expected_output" ]; then
        echo "Missing expected output file: $expected_output"
        continue
    fi

    ./"$basename" < "$input_file" > "$output_file"

    actual_output=$(cat "$output_file" | sed 's/[[:space:]]*$//')
    expected_output_cleaned=$(cat "$expected_output" | sed 's/[[:space:]]*$//')

    if [ "$actual_output" == "$expected_output_cleaned" ]; then
        echo "Test $test_number: OK"
    else
        echo "Test $test_number: WRONG_ANSWER"
    fi

    rm "$output_file"
    
    ((test_number++))
done

rm "$basename"
