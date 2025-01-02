#!/bin/bash

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
all_tests_passed=true

for input_file in *.in; do
    if [[ "$input_file" =~ [0-9] ]]; then
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
            all_tests_passed=false
        fi
    
        rm "$output_file"
        
        ((test_number++))
    fi
done

index=1

if [ "$all_tests_passed" == true ]; then
    echo -e "\033[32mAll pre-existing tests passed! Proceeding with stress testing...\033[0m"
    
    while true; do
        g++ -o generator generator.cpp
        ./generator > stress_test.in

        g++ -o solutie solutie.cpp
        ./solutie < stress_test.in > stress_test.ok

        ./"$basename" < stress_test.in > stress_test.out

        actual_output=$(cat stress_test.out | sed 's/[[:space:]]*$//')
        expected_output=$(cat stress_test.ok | sed 's/[[:space:]]*$//')

        if [ "$actual_output" == "$expected_output" ]; then
            echo -e "\033[32mStress Test $index: OK\033[0m"
        else
            echo -e "\033[31mStress Test $index: WRONG_ANSWER\033[0m"
            compare_lines "stress_test.out" "stress_test.ok"
            exit
        fi

        ((index++))
        rm generator solutie
    done
else
    echo -e "\033[31mSome pre-existing tests failed. Stress test skipped.\033[0m"
fi

rm "$basename"
