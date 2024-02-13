#!/bin/sh

DIR="../folly"

REGEXP="[1-9]+('[0-9]+)*(u|l|z|ll|U|L|Z|LL|ul|UL|ull|ULL|uLL|zu|zU|Zu|ZU|UZ|Uz|uz|uZ)?"


for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    grep -E -o "$REGEXP" $f
done
