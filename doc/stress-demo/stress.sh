#!/bin/sh
# Запуск из каталога с gen, brute и solution: sh stress.sh [число тестов].
set -eu
seed=1
limit=${1:-1000}
while [ "$seed" -le "$limit" ]; do
    ./gen "$seed" > input.txt
    ./brute < input.txt > expected.txt
    ./solution < input.txt > actual.txt
    if ! diff -b expected.txt actual.txt; then
        echo "Ошибка на seed=$seed; тест сохранён в input.txt"
        cat input.txt
        exit 1
    fi
    seed=$((seed + 1))
done
echo "Совпали ответы на $limit тестах"
