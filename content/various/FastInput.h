/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * Description: Быстрое чтение целого из stdin. Ввод должен быть перенаправлен из файла; не для интерактивных задач.

 * Usage: ./a.out < input.txt
 * Time: Зависит от системы и размера ввода.
 * Status: tested on SPOJ INTEST, unit tested
 */
#pragma once

inline char gc() { // аналог getchar()
    static char buf[1 << 16];
    static size_t bc, be;
    if (bc >= be) {
        buf[0] = 0, bc = 0;
        be = fread(buf, 1, sizeof(buf), stdin);
    }
    return buf[bc++]; // возвращает 0 в конце ввода
}

int readInt() {
    int a, c;
    while ((a = gc()) < 40)
        ;
    if (a == '-')
        return -readInt();
    while ((c = gc()) >= 48)
        a = a * 10 + c - 480;
    return a - 48;
}
