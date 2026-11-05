/**
 * Author: Simon Lindholm, Andrew-A-13, cp_trd
 * Source: GNU libstdc++ PBDS; see doc/ordered-containers.md
 * Description: Ordered set/map with ranks. GNU extension.
 *  Use a.swap(b), NOT std::swap(a,b): the generic swap can
 *  copy entire PBDS trees. Never use less\_equal for duplicates:
 *  the comparator must be a strict weak ordering.
 *  See examples below for multiset, bounds and split/join.
 * Time: O(\log n) insert/erase/search/rank/kth; member swap O(1)
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
    s.insert(9);           // duplicate insert is ignored
    auto it = s.find(5);   // end() if missing
    it = s.lower_bound(6); // first >= 6
    it = s.upper_bound(9); // first > 9; here end()
    auto rank = s.order_of_key(9); // 1: keys strictly < 9
    it = s.find_by_order(0);       // 5, ranks are 0-based
    assert(s.find_by_order(s.size()) == s.end());
    s.erase(it);
    s.erase(9);    // iterator / key; don't erase(end)
    s.swap(other); // ALWAYS member swap for PBDS
    s.insert(1);
    s.insert(3);
    s.insert(7);
    s.split(3, other); // s: <=3; other: >3 (overwritten)
    s.join(other);     // other becomes empty
    // join requires all keys of one tree < all of the other.
    // Arbitrary union: insert elements, NOT join.
    s.clear(); // also: size(), empty(), begin/end

    ordered_multiset<int> ms;
    int uid = 0; // unique IDs in [0,INT_MAX)
    ms.insert({5, uid++});
    ms.insert({5, uid++});
    auto lo = ms.order_of_key({5, 0});       // count <5
    auto hi = ms.order_of_key({5, INT_MAX}); // count <=5
    assert(hi - lo == 2);                    // count ==5
    auto first = ms.lower_bound({5, 0});
    if (first != ms.end() && first->first == 5)
        ms.erase(first); // erase ONE copy
    auto kth = ms.find_by_order(0);
    assert(kth != ms.end() && kth->first == 5);
    // Save the inserted pair to erase that exact occurrence.
    // Count [l,r): order_of_key({r,0})-order_of_key({l,0}).

    ordered_map<int, ll> mp;
    mp[7] = 42;          // [] inserts missing key
    mp.insert({2, 100}); // existing value is not overwritten
    auto entry = mp.find_by_order(0); // key=2, value=100
    entry->second = 101; // value is mutable, key is not
    assert(mp.order_of_key(7) == 1); // ranks KEYS, not values
    (void)rank;
}
