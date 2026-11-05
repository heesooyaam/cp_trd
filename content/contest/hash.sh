#!/bin/sh
# Хеш кода без пробелов и комментариев; нужен GNU cpp.
# Для macOS: brew install gcc.
compiler=cpp
if [ "$(uname -s)" = Darwin ]; then
    for candidate in cpp-16 cpp-15 cpp-14 cpp-13; do
        if command -v "$candidate" >/dev/null 2>&1; then
            compiler=$candidate
            break
        fi
    done
fi
if command -v md5sum >/dev/null 2>&1; then
    "$compiler" -dD -P -fpreprocessed |
        tr -d '[:space:]' | md5sum | cut -c-6
else
    "$compiler" -dD -P -fpreprocessed |
        tr -d '[:space:]' | md5 -q | cut -c-6
fi
