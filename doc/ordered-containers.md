# Ordered set / multiset / map

Типы из content/data-structures/OrderStatisticTree.h используют GNU PBDS с rb_tree_tag. Нужен GCC/libstdc++; одного C++20 без GNU-библиотеки недостаточно.

| Тип | Содержимое |
|---|---|
| ordered_set<K> | Уникальные ключи |
| ordered_multiset<K> | Пары (ключ, уникальный id), дубликаты ключа допустимы |
| ordered_map<K,V> | Уникальный ключ и изменяемое значение |

| Метод | Смысл |
|---|---|
| insert(x) | Повтор уникального ключа не меняет дерево |
| find(x) | Итератор либо end() |
| lower_bound(x) / upper_bound(x) | Первый ключ >= x / > x |
| order_of_key(x) | Число ключей строго меньше x |
| find_by_order(k) | k-й элемент с 0; end() вне диапазона |
| erase(key) / erase(iterator) | Удалить ключ / элемент; второй возвращает следующий итератор |
| clear(), size(), empty() | Обычные операции контейнера |
| begin()/end(), rbegin()/rend() | Обход; не random-access итераторы |
| a.swap(b) | Обмен без копирования всех элементов |
| a.split(x,b) | В a остаются <= x, в b переходят > x; старое b очищается |
| a.join(b) | Перенос b в a; все ключи одного дерева строго меньше всех ключей другого |

Не используйте **std::swap(a,b)**: общий алгоритм может копировать PBDS, и small-to-large становится медленным. Это не запрет компилятора: опасность в сложности. Используйте **a.swap(b)**. Не рассчитывайте, что std::move автоматически обеспечит дешёвое перемещение. [Пример на CF](https://codeforces.com/blog/entry/90392), [интерфейс tree в GCC](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/classpb__ds_1_1tree.html).

Для multiset id должны быть уникальны и лежать в [0,INT_MAX):

~~~cpp
ms.order_of_key({x,0});       // число < x
ms.order_of_key({x,INT_MAX}); // число <= x
// Разность = число копий x.
// Число элементов [l,r):
ms.order_of_key({r,0}) - ms.order_of_key({l,0});
~~~

Удаление одной копии: lower_bound({x,0}), проверка end() и первого компонента, затем erase(it). Для конкретной копии сохраните её пару. Все копии удаляйте последовательным erase итераторов; диапазонный erase как у std::set не предполагается. Для объединения независимо созданных multisets id не должны сталкиваться.

Не используйте less_equal: компаратор обязан быть строгим, иначе поиск и удаление некорректны.

Для ordered_map ранги считаются **по ключу**. find_by_order(k)->first — ключ, ->second — изменяемое значение. operator[] вставляет отсутствующий ключ с default-значением; insert не перезаписывает существующий. [Пример GNU ordered map с find_by_order и join](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/testsuite/ext/pb_ds/example/tree_order_statistics_join.cc).
