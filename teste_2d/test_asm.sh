#!/bin/bash

generate_random_number() {
    local num1=$((RANDOM % 2890 + 92))
    local num2=$((RANDOM % 2890 + 92))
    echo $((num1 * num2))
}
generate_random_string() {
    local length=$1
    tr -dc 'a-zA-Z' </dev/urandom | head -c "$length"
}

folder_paths=()

current_dir=$(pwd)

for i in $(seq 1 10); do
    folder_name=$(generate_random_string 10)
  
    mkdir "$folder_name"

    folder_paths+=("$current_dir/$folder_name")

    num_files=$((2 + RANDOM % 49))

    for j in $(seq 1 "$num_files"); do
        file_name=$(generate_random_string 10).txt
    
        file_size=$(generate_random_number)

        if [ "$file_size" -lt 9216 ]; then
            file_size=9216
        fi

        if [ "$file_size" -gt 8388608 ]; then
            file_size=8388608
        fi

        truncate -s "$file_size" "$folder_name/$file_name"
    done
done

g++ -o generator generator.cpp
g++ -o solutie solutie.cpp

./generator "${folder_paths[@]}"
./solutie < 7.in > 7.ok

if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
    echo "Usage: $0 <program.s> [test_number]"
    exit 1
fi

program="$1"
basename=$(basename "$program" .s)

if [ "$#" -eq 2 ]; then
    test_number_to_run="$2"
else
    test_number_to_run=-1
fi

echo "Compiling assembly program..."
gcc -m32 "$program" -o "$basename" 

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

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

test_number=1
for input_file in *.in; do
    if [ "$test_number_to_run" -ne -1 ] && [ "$test_number" -ne "$test_number_to_run" ]; then
        ((test_number++))
        continue
    fi
    
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
        echo -e "\033[32mTest $test_number: OK\033[0m"
    else
        echo -e "\033[31mTest $test_number: WRONG_ANSWER\033[0m"
        compare_lines "$output_file" "$expected_output"
    fi

    rm "$output_file"
    
    ((test_number++))
done

rm -rf "${folder_paths[@]}"
rm "$basename"
