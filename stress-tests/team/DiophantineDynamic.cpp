#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
#define all(x) std::begin(x), std::end(x)
#define eb(...) emplace_back(__VA_ARGS__)
#define sz(x) int((x).size())
#include "../../content/number-theory/Diophantine.h"
#include "../../content/strings/DynamicSuffixAutomaton.h"
#include "../../content/graph/CompressTree.h"
#include "../../content/graph/Kuhn.h"
mt19937 gen(346731);
int rnd(int n) { return int(gen() % unsigned(n)); }
void diophantine_tests() {
    for (int a=-30;a<=30;++a) for(int b=-10;b<=10;++b) if(b) {
        assert(floor_div(a,b)==ll(floor(double(a)/b)));
        assert(ceil_div(a,b)==ll(ceil(double(a)/b)));
    }
    for(int a=-5;a<=5;++a) for(int b=-5;b<=5;++b) for(int c=-15;c<=15;++c) {
        diophantine d(a,b,c);
        bool possible = (a||b) ? c%gcd(a,b)==0 : c==0;
        auto any=d.minimum(0,0);
        assert((any.status==1)==possible);
        if(possible)assert(a*any.x+b*any.y==c);
        assert(possible ? !d.count() : d.count()==optional<i128>(0));
        for(int it=0;it<8;++it) {
            int lx=rnd(13)-6,rx=rnd(13)-6,ly=rnd(13)-6,ry=rnd(13)-6;
            auto bounded=d;bounded.bounds(lx,rx,ly,ry);
            vector<pair<int,int>>sol;
            for(int x=lx;x<=rx;++x)for(int y=ly;y<=ry;++y)if(a*x+b*y==c)sol.eb(x,y);
            assert(bounded.count()==optional<i128>(sol.size()));
            for(int p=-2;p<=2;++p)for(int q=-2;q<=2;++q) {
                auto ans=bounded.minimum(p,q);
                if(sol.empty()){assert(ans.status==-1);continue;}
                ll want=LLONG_MAX;
                for(auto[x,y]:sol)want=min(want,ll(p*x+q*y));
                assert(ans.status==1&&a*ans.x+b*ans.y==c);
                assert(lx<=ans.x&&ans.x<=rx&&ly<=ans.y&&ans.y<=ry);
                assert(p*ans.x+q*ans.y==want);
            }
        }
    }
    // Half-infinite bounds and unbounded objectives, including a=b=0.
    diophantine d(2,-3,1);d.bounds(0,nullopt,0,nullopt);
    assert(!d.count());auto m=d.minimum(1,1);assert(m.status==1&&m.x==2&&m.y==1);
    assert(d.minimum(-1,-1).status==0);
    assert(d.minimum(2,-3).status==1); // constant objective
    diophantine line(0,-3,6);assert(line.minimum(1,0).status==0);
    line.bounds(-5,5,nullopt,nullopt);assert(line.count()==optional<i128>(11));
    assert(line.minimum(1,0).x==-5);line.bounds(nullopt,nullopt,0,nullopt);assert(line.count()==optional<i128>(0));
    diophantine plane(0,0,0);plane.bounds(2,nullopt,3,nullopt);
    auto ans=plane.minimum(1,1);assert(ans.status==1&&ans.x==2&&ans.y==3);
    assert(plane.minimum(-1,1).status==0);
    plane.bounds(nullopt,5,nullopt,6);assert(plane.count()==optional<i128>(16));
    diophantine bad(0,0,1);bad.bounds(2,nullopt,3,nullopt);assert(bad.count()==optional<i128>(0));
    ll big=1000000000000000000LL;
    diophantine huge(0,0,0);huge.bounds(-big,big,-big,big);
    assert(huge.count()==optional<i128>((i128(2)*big+1)*(i128(2)*big+1)));
    for(int it=0;it<10000;++it) {
        ll a=ll(gen()%1000000000)*gen()%big,b=ll(gen()%1000000000)*gen()%big;
        if(it%2)a=-a;
        if(it%3)b=-b;
        ll c=ll(gen())-2000000000LL;
        diophantine large(a,b,c);large.bounds(-big,big,-big,big);auto v=large.minimum(0,0);
        if(v.status==1)assert(i128(a)*v.x+i128(b)*v.y==c);
    }
}
ll naive(const vector<string>&text,string_view p) {
    ll ans=0;
    for(const auto&s:text)for(size_t i=0;i+p.size()<=s.size();++i)ans+=s.compare(i,p.size(),p)==0;
    return ans;
}
string word(int n){string s(n,'a');for(char&c:s)c+=rnd(3);return s;}
void dynamic_tests() {
    dynamic_sam_example();
    dynamic_suffix_automaton crossing;crossing.add("ab");crossing.add("cd");assert(crossing.count("bc")==0);
    for(int run=0;run<40;++run) {
        dynamic_suffix_automaton added,removed;vector<string> current;
        for(int it=0;it<180;++it) {
            if(!current.empty()&&rnd(4)==0){int i=rnd(int(current.size()));removed.add(current[i]);current.erase(current.begin()+i);}
            else{current.eb(word(rnd(15)));added.add(current.back());}
            for(int q=0;q<12;++q){string p=word(1+rnd(6));assert(added.count(p)-removed.count(p)==naive(current,p));}
        }
    }
    dynamic_suffix_automaton skew;vector<string>texts{string(3000,'a')};skew.add(texts[0]);
    for(int i=0;i<1000;++i){texts.eb(i%2?"":"a");skew.add(texts.back());}
    assert(skew.count("aaa")==2998);assert(skew.count("a")==naive(texts,"a"));
}
void virtual_tests() {
    for(int n=1;n<=70;++n) {
        vector<vector<int>>g(n);vector<int>par(n),depth(n);
        for(int v=1;v<n;++v){par[v]=rnd(v);depth[v]=depth[par[v]]+1;g[v].eb(par[v]);g[par[v]].eb(v);}
        LCA lca(g);
        for(int it=0;it<100;++it) {
            vector<int>s;for(int v=0;v<n;++v)if(rnd(4)==0)s.eb(v);
            if(!s.empty()&&it%3==0)s.eb(s[0]);
            auto vt=compressTree(lca,s);set<int>want(all(s));
            for(int u:s)for(int v:s)want.emplace(lca.lca(u,v));
            set<int>actual;for(auto[p,v]:vt)actual.emplace(v);assert(actual==want);
            if(vt.empty())continue;
            assert(vt[0].first==0);
            for(int i=1;i<int(vt.size());++i){auto[p,v]=vt[i];assert(p<i);int u=par[v];while(!want.count(u))u=par[u];assert(vt[p].second==u);}
            // Example DP: sum of distances over unordered pairs of marked vertices.
            vector<ll>cnt(vt.size());ll answer=0;set<int>marked(all(s));
            for(int i=int(vt.size())-1;i>=0;--i){auto[p,v]=vt[i];cnt[i]+=marked.count(v);if(i){answer+=cnt[i]*(ll(marked.size())-cnt[i])*(depth[v]-depth[vt[p].second]);cnt[p]+=cnt[i];}}
            ll expected=0;for(int u:marked)for(int v:marked)if(u<v)expected+=depth[u]+depth[v]-2*depth[lca.lca(u,v)];
            assert(answer==expected);
        }
    }
}
int main(){diophantine_tests();dynamic_tests();virtual_tests();cout<<"Diophantine, dynamic SAM and virtual tree tests passed\n";}
