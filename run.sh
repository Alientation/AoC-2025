#!/usr/bin/env bash

set -e  # exit on error

if [ $# -ne 2 ]; then
    echo "Usage: $0 <day> <part>"
    exit 1
fi

DAY_NUM=$1
PART=$2

# Zero-pad the day so "1" -> "01"
DAY=$(printf "%02d" "$DAY_NUM")

SRC="day${DAY}/day${DAY}.cpp"
OUT="build/day${DAY}"

# Check if file exists
if [ ! -f "$SRC" ]; then
    echo "Error: source file '$SRC' not found."
    exit 1
fi

echo "Compiling $SRC"
g++ -std=c++20 -O2 -Wall "$SRC" -o "$OUT"


# Function to check and fallback input
get_input() {
    local TYPE=$1
    local FILE="day${DAY}/${TYPE}/day${DAY}-p${PART}.txt"

    # If part 2 input is empty or missing, copy part 1 input
    if [ "$PART" -eq 2 ]; then
        if [ ! -s "$FILE" ]; then
            FILE="day${DAY}/${TYPE}/day${DAY}-p1.txt"
        fi
    fi

    echo "$FILE"
}

# Run sample
SAMPLE_FILE=$(get_input "sample")
echo "Running sample on day $DAY p$PART"
./"$OUT" "$PART" < "$SAMPLE_FILE"
echo ""
echo ""

# Run test
TEST_FILE=$(get_input "test")
echo "Running test on day $DAY p$PART"
./"$OUT" "$PART" < "$TEST_FILE"
echo ""