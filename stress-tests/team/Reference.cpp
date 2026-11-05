#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#ifndef all
#define all(x) std::begin(x), std::end(x)
#endif
#ifndef eb
#define eb(...) emplace_back(__VA_ARGS__)
#endif

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;
#define sz(x) int((x).size())
#include "../../content/number-theory/FastMint.h"
#include "../../content/number-theory/FastGcdLcm.h"
#include "../../content/number-theory/FactorizationSieve.h"
#include "../../content/number-theory/DivisorsSieve.h"
#include "../../content/combinatorial/FastCombinatorics.h"
#include "../../content/numerical/ModularFFT.h"
#include "../../content/strings/SuffixAutomaton.h"
#include "../../content/strings/TeamSuffixArray.h"
#include "../../content/strings/TeamHash.h"
#include "../../content/data-structures/PersistentSegmentTree.h"
#include "../../content/data-structures/TreapSet.h"
#include "../../content/data-structures/VectorHash.h"
#include "../../content/geometry/CircleTree.h"
#include "../../content/graph/TeamDinic.h"
#include "../../content/graph/TeamMinCostFlow.h"
#include "../../content/graph/Kuhn.h"
#include "../../content/graph/CentroidDecomposition.h"
#include "../../content/various/SimulatedAnnealing.h"

mt19937_64 gen(20261105);
int rnd(int n) { return int(gen() % uint64_t(n)); }
template<uint32_t M> void test_mint() {
    using T = LazyMontgomeryModInt<M>;
    auto norm = [](ll x) { return (x % M + M) % M; };
    for (ll x : {LLONG_MIN, LLONG_MAX, -1LL, 0LL, 1LL})
        assert(T(x).get() == norm(x));
    for (int it = 0; it < 20000; ++it) {
        ll a = ll(gen()), b = ll(gen()), x = norm(a), y = norm(b);
        T u(a), v(b);
        assert(u.get() == x && v.get() == y);
        assert((u+v).get() == (x+y)%M);
        assert((u-v).get() == (x-y+M)%M);
        assert((u*v).get() == x*y%M);
        assert((-u).get() == (M-x)%M);
        assert((u == v) == (x == y));
        if (gcd(y,ll(M)) == 1) assert(((u/v)*v) == u);
        int k = rnd(40);
        ll expected = 1;
        for (int i=0;i<k;++i) expected=expected*x%M;
        assert(u.pow(k).get() == expected);
        // Keep the redundant Montgomery residue through long chains.
        for(int i=0;i<10;++i) {
            u += v; u *= v; u -= v;
            x = ((x+y)%M*y%M-y+M)%M;
        }
        assert(u.get() == x);
    }
}
void math_tests() {
    test_mint<998244353>(); test_mint<1000000007>();
    test_mint<15>(); test_mint<1073741823>();
    for (int it=0;it<100000;++it) {
        uint64_t a=gen(), b=gen();
        assert(binary_gcd(a,b) == gcd(a,b));
        assert(binary_gcd(a,0) == a);
        assert(binary_gcd(a,a) == a);
        a %= 1000000000; b %= 1000000000;
        uint64_t expect = a && b ? a/gcd(a,b)*b : 0;
        assert(binary_lcm(a,b) == expect);
    }
    assert(binary_gcd(0,0)==0 && binary_lcm(0,0)==0);
    factorization_sieve_t f(3000);
    divisors_sieve_t d(3000), empty(0);
    for (int x=1;x<=3000;++x) {
        vi divisors;
        for(int y=1;y<=x;++y) if(x%y==0) divisors.eb(y);
        auto range=d.get(x);
        assert(vi(all(range)) == divisors);
        ll product=1;
        for(auto [p,e]:f.factor(x)) {
            assert(f.is_prime(p));
            while(e--) product*=p;
        }
        assert(product==x);
        assert(f.is_prime(x)==(divisors.size()==2));
    }
    combinations cb(100);
    vector<vector<ll>> pascal(101, vector<ll>(101));
    for(int n=0;n<=100;++n) {
        pascal[n][0]=pascal[n][n]=1;
        for(int k=1;k<n;++k)
            pascal[n][k]=(pascal[n-1][k]+pascal[n-1][k-1])%998244353;
        for(int k=-1;k<=n+1;++k)
            assert(cb.C(n,k).get()==(k<0||k>n ? 0 : pascal[n][k]));
    }
}
void fft_tests() {
    for(int it=0;it<1500;++it) {
        int n=rnd(70), m=rnd(70);
        vi a(n),b(m);
        for(int& x:a) x=int(gen());
        for(int& x:b) x=int(gen());
        vi expected(n&&m ? n+m-1 : 0);
        constexpr ll mod=modular_fft::mod;
        for(int i=0;i<n;++i) for(int j=0;j<m;++j) {
            ll x=(a[i]%mod+mod)%mod, y=(b[j]%mod+mod)%mod;
            expected[i+j]=int((expected[i+j]+x*y)%mod);
        }
        assert(modular_fft::multiply(a,b)==expected);
    }
    for(int log=0;log<=16;++log) {
        vi a(1<<log);
        for(auto& x:a) x=rnd(modular_fft::mod);
        vi copy=a;
        modular_fft::fft(a); modular_fft::fft(a,true);
        assert(a==copy);
    }
    assert(modular_fft::multiply({0},{0}) == vi{0});
    assert(modular_fft::multiply({INT_MIN},{1}) ==
        vi{int((ll(INT_MIN)%modular_fft::mod+modular_fft::mod)%modular_fft::mod)});
}
void string_tests() {
    for(int n=0;n<=8;++n) for(int mask=0;mask<(1<<n);++mask) {
        string s(n,'a');
        for(int i=0;i<n;++i) s[i]+=((mask>>i)&1);
        suffix_automaton sa(s);
        map<string,int> count;
        for(int l=0;l<n;++l) for(int r=l+1;r<=n;++r) ++count[s.substr(l,r-l)];
        for(int repeat=0;repeat<2;++repeat) {
            sa.count_occurrences();
            ll distinct=0;
            for(int v=2;v<int(sa.st.size());++v)
                distinct+=sa.st[v].len-sa.sufflink(v).len;
            assert(distinct==ll(count.size()));
            for(auto& [pattern,occ]:count) {
                traverser tr(sa);
                for(char c:pattern) tr.move_by_char(c);
                assert(tr.get_current_state().occ==occ);
                for(int len=int(pattern.size());len>=0;--len) {
                    tr.move_to_suffix(len);
                    if(len) assert(tr.get_current_state().occ ==
                        count[pattern.substr(pattern.size()-len)]);
                    else assert(tr.cur==sa.root);
                }
            }
        }
        sa.add("aba"); sa.count_occurrences();
        suffix_automaton other(s+"aba");
        assert(sa.st.size()==other.st.size());
        for(int i=0;i<int(sa.st.size());++i) assert(sa.st[i].occ==other.st[i].occ);
        string t="bbababa";
        int lcs=0;
        for(auto& [p,c]:count) if(t.find(p)!=string::npos) lcs=max(lcs,int(p.size()));
        suffix_automaton initial(s);
        assert(longest_common_substring(initial,t)==lcs);
    }
    for(int it=0;it<2000;++it) {
        int n=rnd(60);
        string s(n,'\0');
        for(char& c:s) c=char(rnd(it%2 ? 256 : 4));
        vi expect(n); iota(all(expect),0);
        sort(all(expect),[&](int a,int b) {return s.substr(a)<s.substr(b);});
        vi sa=suffix_array(s);
        assert(sa==expect);
        auto lcp=suffix_lcp(s,sa);
        assert(int(lcp.size())==max(0,n-1));
        for(int i=0;i<n-1;++i) {
            int k=0;
            while(sa[i]+k<n&&sa[i+1]+k<n&&s[sa[i]+k]==s[sa[i+1]+k]) ++k;
            assert(lcp[i]==k);
        }
        string_hasher h(s,true,false);
        string padded=" "+s;
        string_hasher hp(padded,true);
        for(int q=0;q<30;++q) {
            int l=rnd(n+1), r=l+rnd(n-l+1);
            string p=s.substr(l,r-l), rev=p; reverse(all(rev));
            string_hasher local(p,true,false);
            assert(h.get_rev_hash(l+1,r)==local.get_rev_hash(1,int(p.size())));
            assert(h.get_dir_hash(l+1,r)==local.get_dir_hash(1,int(p.size())));
            assert(h.get_rev_hash(l+1,r)==hp.get_rev_hash(l+1,r));
            assert(h.is_palindrome(l+1,r)==(p==rev));
        }
    }
    vector<ll> a={LLONG_MIN,-4,0,7,LLONG_MAX,-4,0,7};
    arr_hasher<ll> h(a,true,false);
    assert(h.get_rev_hash(2,4)==h.get_rev_hash(6,8));
    assert(h.get_dir_hash(2,4)==h.get_dir_hash(6,8));
    assert(!(h.get_rev_hash(2,3)==h.get_rev_hash(2,4)));
}
void structure_tests() {
    for(int it=0;it<50;++it) {
        int n=1+rnd(50);
        SumTree<ll> pst(n);
        vector<vector<ll>> data(1,vector<ll>(n));
        vi roots{0};
        for(int q=0;q<200;++q) {
            int version=rnd(int(roots.size())), pos=rnd(n), delta=rnd(100)-50;
            auto next=data[version]; next[pos]=delta;
            int root=pst.update(pos,delta,roots[version]);
            data.eb(next); roots.eb(root);
            for(int j=0;j<10;++j) {
                int v=rnd(int(roots.size())),l=rnd(n+1),r=rnd(n+1);
                if(l>r) swap(l,r);
                assert(pst.get_sum(l,r,roots[v])==accumulate(data[v].begin()+l,data[v].begin()+r,0LL));
            }
        }
    }
    treap_set tr;
    multiset<ll> ms;
    for(int it=0;it<20000;++it) {
        ll x = it%13==0 ? LLONG_MIN : it%17==0 ? LLONG_MAX : rnd(201)-100;
        if(rnd(2)) {tr.insert(x); ms.insert(x);}
        else {tr.erase(x); auto p=ms.find(x); if(p!=ms.end())ms.erase(p);}
        assert(tr.size(tr.root)==int(ms.size()));
        assert(tr.order_of_key(x)==distance(ms.begin(),ms.lower_bound(x)));
        if(!ms.empty()) {
            int k=rnd(int(ms.size()));
            assert(tr.kth(k)==*next(ms.begin(),k));
        }
    }
    unordered_map<vi,int,vector_hash> map;
    map[{}]=1; map[{INT_MIN,0,INT_MAX}]=2; map[{-1}]=3;
    assert((map[{}]==1 && map[vi{INT_MIN,0,INT_MAX}]==2 && map[{-1}]==3));
}
void circle_tests() {
    using C=circle_tree::circle;
    auto check=[](vector<C> a) {
        circle_tree tree(a);
        int n=int(a.size());
        vector<int> expected(n,-1);
        for(int i=0;i<n;++i) for(int j=0;j<n;++j) if(a[j].r>a[i].r) {
            auto dx=a[i].x-a[j].x,dy=a[i].y-a[j].y,dr=a[j].r-a[i].r;
            if(dx*dx+dy*dy<dr*dr && (expected[i]==-1||a[j].r<a[expected[i]].r)) expected[i]=j;
        }
        assert(tree.parent==expected);
        vi seen(n);
        for(int r:tree.roots) {assert(expected[r]==-1); ++seen[r];}
        for(int p=0;p<n;++p) for(int c:tree.children[p]) {assert(expected[c]==p);++seen[c];}
        assert(all_of(all(seen),[](int x){return x==1;}));
    };
    check({}); check({{0,0,1}});
    check({{0,0,10},{0,0,5},{0,0,1},{30,0,3}});
    check({{0,0,2},{0,5,2},{4,9,2}}); // equal enter/exit x events
    for(int it=0;it<1000;++it) {
        vector<C> a;
        function<void(long double,long double,long double,int)> generate =
            [&](long double x,long double y,long double r,int depth) {
                a.push_back({x,y,r});
                if(depth==0) return;
                int child=1+rnd(3);
                for(int j=0;j<child;++j) {
                    long double ang=(j+0.2L)*2*acosl(-1.L)/child;
                    generate(x+0.55L*r*cosl(ang),y+0.55L*r*sinl(ang),r*0.2L,depth-1);
                }
            };
        generate(0,0,1000,4);
        generate(3000,2000,500,2);
        shuffle(all(a),gen);
        check(a);
    }
}
ll brute_cut(int n, const vector<tuple<int,int,ll>>& es) {
    ll best=LLONG_MAX;
    for(int mask=0;mask<(1<<n);++mask) if((mask&1)&&!(mask>>(n-1)&1)) {
        ll cap=0;
        for(auto [u,v,c]:es) if((mask>>u&1)&&!(mask>>v&1)) cap+=c;
        best=min(best,cap);
    }
    return best;
}
void graph_tests() {
    for(int it=0;it<1000;++it) {
        int n=2+rnd(6), m=rnd(25);
        dinic d(n); vector<tuple<int,int,ll>> es;
        for(int i=0;i<m;++i) {
            int u=rnd(n),v=rnd(n); ll c=rnd(100);
            if(it%10==0) c*=1000000000LL;
            d.add_edge(u,v,c); es.eb(u,v,c);
        }
        assert(d.max_flow(0,n-1)==brute_cut(n,es));
        assert(d.max_flow(0,n-1)==0);
    }
    for(int it=0;it<1000;++it) {
        int n=rnd(7), m=rnd(7);
        vector<vi> g(n);
        for(auto& a:g)for(int j=0;j<m;++j)if(rnd(2))a.eb(j);
        function<int(int,int)> go=[&](int v,int mask) {
            if(v==n)return 0;
            int ans=go(v+1,mask);
            for(int u:g[v])if(!(mask>>u&1))ans=max(ans,1+go(v+1,mask|(1<<u)));
            return ans;
        };
        kuhn k;
        assert(k.solve(g,m)==go(0,0));
        assert(k.solve(g,m)==go(0,0));
    }
    for(int it=0;it<1200;++it) {
        int n=2+rnd(4), m=rnd(7), limit=rnd(7);
        // Potentials + nonnegative reduced costs => no negative cycles.
        vi pot(n); for(int& x:pot)x=rnd(11)-5;
        vector<tuple<int,int,int,int>> es;
        min_cost_flow flow(n);
        for(int i=0;i<m;++i) {
            int u=rnd(n),v=rnd(n),cap=rnd(3),cost=rnd(5)+pot[v]-pot[u];
            es.eb(u,v,cap,cost); flow.add_edge(u,v,cap,cost);
        }
        pair<ll,ll> best{0,0}; vector<int> balance(n);
        function<void(int,ll)> enumerate=[&](int e,ll cost) {
            if(e==m) {
                for(int v=1;v<n-1;++v)if(balance[v])return;
                int f=-balance[0];
                if(f<0||f>limit||balance[n-1]!=f)return;
                if(f>best.first||(f==best.first&&cost<best.second))best={f,cost};
                return;
            }
            auto [u,v,c,w]=es[e];
            for(int x=0;x<=c;++x) {
                balance[u]-=x;balance[v]+=x;
                enumerate(e+1,cost+ll(x)*w);
                balance[u]+=x;balance[v]-=x;
            }
        };
        enumerate(0,0);
        assert(flow.solve(0,n-1,limit)==best);
    }
    for(int it=0;it<300;++it) {
        int n=1+rnd(200);
        vector<vi> g(n);
        for(int v=1;v<n;++v) {int u=rnd(v);g[u].eb(v);g[v].eb(u);}
        centroid_decomposition cd(g);
        vector<bool> removed(n);
        function<void(int,int)> verify=[&](int start,int par) {
            vi component,stack{start},visited(n);
            visited[start]=1;
            while(!stack.empty()) {
                int v=stack.back();stack.pop_back();component.eb(v);
                for(int u:g[v])if(!removed[u]&&!visited[u])visited[u]=1,stack.eb(u);
            }
            int c=-1;
            for(int v:component)if(cd.parent[v]==par){assert(c==-1);c=v;}
            assert(c!=-1); removed[c]=true;
            for(int u:g[c])if(!removed[u]) {
                vi q{u}; vector<bool> seen(n);seen[u]=true;
                for(int j=0;j<int(q.size());++j)for(int v:g[q[j]])
                    if(!removed[v]&&!seen[v])seen[v]=true,q.eb(v);
                assert(q.size()*2<=component.size());
                verify(u,c);
            }
        };
        verify(0,-1);
    }
}
void anneal_tests() {
    mt19937 rng(337);
    for(int n=0;n<30;++n) {
        vi p(n);iota(all(p),0);reverse(all(p));
        auto cost=[](const vi& p) {double c=0;for(int i=0;i<int(p.size());++i)c+=abs(p[i]-i);return c;};
        auto [best,res]=anneal(p,cost,1000,10,0.01,rng);
        assert(best<=cost(p)&&best==cost(res));
        sort(all(res));
        for(int i=0;i<n;++i)assert(res[i]==i);
        assert(anneal(p,cost,0,1,1,rng).second==p);
    }
}
int main() {
    math_tests(); fft_tests(); string_tests(); structure_tests();
    circle_tests(); graph_tests(); anneal_tests();
    cout << "Team reference: all differential and boundary tests passed\n";
}
