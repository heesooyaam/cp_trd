/**
 * Author: Simon Lindholm, Andrew-A-13, cp_trd
 * Source: GNU libstdc++ PBDS; see doc/ordered-containers.md
 * Description: Множество/словарь с порядковыми статистиками, расширение GNU PBDS. Для обмена использовать a.swap(b), НЕ std::swap(a,b): общий swap может копировать деревья целиком. Для повторов нужны пары (ключ,id); less\_equal запрещён, сравнение должно быть строгим. Методы и мультисет показаны ниже.

 * Time: O(\log n) вставка/удаление/поиск/rank/kth; метод swap O(1)
 * Status: Methods and multiset ranks tested against STL.
 */
#pragma once
#include <ext/pb_ds/assoc_container.hpp> /// keep-include
#include <ext/pb_ds/tree_policy.hpp>     /// keep-include
namespace pbds = __gnu_pbds;
template <class K, class V = pbds::null_type>
using ordered_tree =
    pbds::tree<K, V, less<K>, pbds::rb_tree_tag,
               pbds::tree_order_statistics_node_update>;
template <class K> using ordered_set = ordered_tree<K>;
template <class K, class V>
using ordered_map = ordered_tree<K, V>;
template <class K>
using ordered_multiset = ordered_set<pair<K, int>>;
template <class T> using Tree = ordered_set<T>; /// exclude-line

void ordered_examples() {
    ordered_set<int> s, other;
    s.insert(5);
    s.insert(9);           // повторная вставка игнорируется
    auto it = s.find(5);   // end(), если ключа нет
    it = s.lower_bound(6); // первый >= 6
    it = s.upper_bound(9); // первый > 9; здесь end()
    auto rank = s.order_of_key(9); // 1: число ключей строго < 9
    it = s.find_by_order(0);       // 5, нумерация с нуля
    assert(s.find_by_order(s.size()) == s.end());
    s.erase(it);
    s.erase(9);    // итератор / ключ; нельзя erase(end)
    s.swap(other); // для PBDS только метод swap
    s.insert(1);
    s.insert(3);
    s.insert(7);
    s.split(3, other); // s: <=3; other: >3 (перезаписывается)
    s.join(other);     // other становится пустым
    // join: все ключи одного дерева меньше всех ключей другого.
    // Общее объединение: вставлять поэлементно, НЕ join.
    s.clear(); // также: size(), empty(), begin/end

    ordered_multiset<int> ms;
    int uid = 0; // уникальные id в [0,INT_MAX)
    ms.insert({5, uid++});
    ms.insert({5, uid++});
    auto lo = ms.order_of_key({5, 0});       // число <5
    auto hi = ms.order_of_key({5, INT_MAX}); // число <=5
    assert(hi - lo == 2);                    // число ==5
    auto first = ms.lower_bound({5, 0});
    if (first != ms.end() && first->first == 5)
        ms.erase(first); // удалить ОДНУ копию
    auto kth = ms.find_by_order(0);
    assert(kth != ms.end() && kth->first == 5);
    // Для удаления конкретной копии сохранить вставленную пару.
    // Число на [l,r): order_of_key({r,0})-order_of_key({l,0}).

    ordered_map<int, ll> mp;
    mp[7] = 42;          // [] вставляет отсутствующий ключ
    mp.insert({2, 100}); // старое значение не перезаписывается
    auto entry = mp.find_by_order(0); // ключ=2, значение=100
    entry->second = 101; // значение менять можно, ключ нельзя
    assert(mp.order_of_key(7) == 1); // порядок КЛЮЧЕЙ, не значений
    (void)rank;
}
