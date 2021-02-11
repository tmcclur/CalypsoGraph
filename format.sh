#!/bin/sh

if ! [ -x "`which clang-format`" ]; then
    exit
fi

find `pwd` -regex ".*\.[ch]$" | while read file; do
    clang-format -i -style='{ "BasedOnStyle": "google", "IndentWidth": 4, "DerivePointerAlignment": false, "PointerAlignment": "Right" }' "$file"
done

