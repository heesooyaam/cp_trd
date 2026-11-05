/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * License: CC0
 * Source: me
 * Description: Арена для множества объектов без индивидуального освобождения памяти. Уменьшает расходы обычного new.

 * Status: tested
 */
#pragma once

// Глобально либо внутри класса:
static char buf[450 << 20];
void *operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void *)&buf[i -= s];
}
void operator delete(void *) {
}
