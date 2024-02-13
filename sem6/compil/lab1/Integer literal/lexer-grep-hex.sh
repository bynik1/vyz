#!/bin/sh

DIR="../folly"

REGEXP="0x[0-9|A-F|a-f]+('[0-9|A-F|a-f]+)*(u|l|z|ll|U|L|Z|LL|ul|UL|ull|ULL|uLL|zu|zU|Zu|ZU|UZ|Uz|uz|uZ)?"


for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    grep -E -o "$REGEXP" $f
done
