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

compare_lines() {
    local actual="$1"
    local expected="$2"
    local line_number=1
    local actual_line=""
    local expected_line=""
    
    while IFS= read -r actual_line && IFS= read -r expected_line <&3; do
        actual_line=$(echo "$actual_line" | sed 's/[[:space:]]*$//')
        expected_line=$(echo "$expected_line" | sed 's/[[:space:]]*$//')
        
        if [ "$actual_line" != "$expected_line" ]; then
            echo "Difference found at line $line_number:"
            echo "Expected: $expected_line"
            echo "Actual:   $actual_line"
            return
        fi
        ((line_number++))
    done < "$actual" 3< "$expected"
}

for input_file in *.in; do
    expected_output="${input_file%.in}.ok"
    output_file="${basename}_output.txt"
    
    if [ ! -f "$expected_output" ]; then
        echo "Missing expected output file: $expected_output"
        continue
    fi
	cat $input_file > input.txt
    ./"$basename" > "$output_file"

    actual_output=$(cat "$output_file" | sed 's/[[:space:]]*$//')
    expected_output_cleaned=$(cat "$expected_output" | sed 's/[[:space:]]*$//')

    if [ "$actual_output" == "$expected_output_cleaned" ]; then
        echo "Test $test_number: OK"
    else
        echo "Test $test_number: WRONG_ANSWER"
        compare_lines "$output_file" "$expected_output"
    fi

    rm "$output_file"
    
    ((test_number++))
done

rm "$basename"
