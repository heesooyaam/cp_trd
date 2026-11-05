#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#ifndef all
#define all(x) begin(x), end(x)
#endif
#ifndef eb
#define eb(...) emplace_back(__VA_ARGS__)
#endif

using ll=long long;
#include "../../content/data-structures/OrderStatisticTree.h"
int main() {
    ordered_examples();
    ordered_multiset<int> ms;
    multiset<int> ref;
    mt19937 rng(337);
    int uid=0;
    for(int q=0;q<20000;++q) {
        int x=int(rng()%100)-50;
        if(rng()%2) {
            ms.insert({x,uid++});
            ref.insert(x);
        } else {
            auto it=ms.lower_bound({x,0});
            if(it!=ms.end()&&it->first==x)ms.erase(it);
            auto jt=ref.find(x);
            if(jt!=ref.end())ref.erase(jt);
        }
        assert(ms.size()==ref.size());
        auto a=ms.order_of_key({x,0}),b=ms.order_of_key({x,INT_MAX});
        assert(a==size_t(distance(ref.begin(),ref.lower_bound(x))));
        assert(b-a==ref.count(x));
        if(!ref.empty()) {
            int k=int(rng()%ref.size());
            assert(ms.find_by_order(k)->first==*next(ref.begin(),k));
        }
    }
    ordered_set<int> a,b;
    for(int x:{1,2,3,4,5})a.insert(x);
    b.insert(100);
    a.split(3,b);
    assert(vector<int>(all(a))==vector<int>({1,2,3}));
    assert(vector<int>(all(b))==vector<int>({4,5}));
    a.join(b);
    assert(a.size()==5&&b.empty());
    a.swap(b);
    assert(a.empty()&&b.size()==5);
    ordered_map<int,ll> mp;
    mp[3]=1;mp[1]=4;mp.insert({3,9});
    assert(mp[3]==1&&mp.find_by_order(0)->second==4);
    assert(mp.order_of_key(3)==1);
    cout<<"Ordered containers: all tests passed\n";
}
