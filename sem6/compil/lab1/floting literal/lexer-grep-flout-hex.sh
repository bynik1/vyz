#!/bin/sh

DIR="../folly"

#REGEXP="[0-9]*[.]?[0-9]+[e|E]?-?[0-9]+(f|l|F|L|f16|f32|f64|f128|F16|F32|F64|F128|bf16|BF16|)?"
REGEXP="0x[0-9|a-f|A-F]*.('[0-9|a-f|A-F]+)*[p|P]?(-|+)?[0-9|a-f|A-F]+(f|l|F|L|f16|f32|f64|f128|F16|F32|F64|F128|bf16|BF16|)?"

for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    grep -E -o "$REGEXP" $f
done
