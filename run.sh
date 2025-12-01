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

echo "Running sample on day $DAY p$PART"
./"$OUT" "$PART" < "day${DAY}/sample/day${DAY}-sample-p${PART}.txt"
echo ""
echo ""

echo "Running test on day $DAY p$PART"
./"$OUT" "$PART" < "day${DAY}/test/day${DAY}-p${PART}.txt"
echo ""