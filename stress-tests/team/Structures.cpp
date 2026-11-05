#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
#define all(x) std::begin(x), std::end(x)
#define eb(...) emplace_back(__VA_ARGS__)
#include "../../content/data-structures/SegmentTreeExample.h"
#include "../../content/data-structures/PersistentVersions.h"
#include "../../content/graph/BridgesAndCuts.h"
#include "../../content/graph/HLD.h"

mt19937 gen(246810);
int rnd(int n) { return int(gen() % unsigned(n)); }
namespace affine {
using node_t = range_sum::node_t;
struct tag { ll mul = 1, add = 0; };
node_t combine(node_t a, node_t b) { return range_sum::combine(a,b); }
node_t neutral_node() { return {0,0}; }
tag composition(tag old_p, tag new_p) {
    return {new_p.mul * old_p.mul, new_p.mul * old_p.add + new_p.add};
}
node_t sync(node_t x, tag f) { return {x.sum*f.mul+x.len*f.add,x.len}; }
tag neutral_push() { return {}; }
using tree_t = seg_tree_t<node_t, combine, neutral_node, tag,
    composition, sync, neutral_push>;
}
void lazy_tests() {
    segment_tree_example();
    for (int n=0;n<=45;++n) {
        range_sum::tree_t zero(n);
        assert(zero.get(0,n).sum==0 && zero.get(0,n).len==n);
        zero.update(0,n,7);
        assert(zero.get(0,n).sum==7LL*n);
        vector<ll> a(n);
        vector<affine::node_t> nodes;
        for (ll &x:a) { x=rnd(11)-5; nodes.eb(x,1); }
        affine::tree_t st(nodes);
        for (int it=0;it<1500;++it) {
            int l=rnd(n+1),r=rnd(n+1);
            if (l>r) swap(l,r);
            affine::tag f{rnd(3)-1,rnd(21)-10};
            if (it%3==0 && n) {
                int p=rnd(n); st.update(p,f); a[p]=a[p]*f.mul+f.add;
            } else if (it%3==1) {
                st.update(l,r,f);
                for(int i=l;i<r;++i) a[i]=a[i]*f.mul+f.add;
            }
            auto ans=st.get(l,r);
            assert(ans.sum==accumulate(a.begin()+l,a.begin()+r,0LL));
            assert(ans.len==r-l);
            assert(st.get(0,n).sum==accumulate(all(a),0LL));
            if(n) { int p=rnd(n); assert(st.get(p).sum==a[p]); }
        }
    }
}
void persistent_tests() {
    SumTree<ll> st(3);
    int v1=st.update(1,4000000000LL,0);
    int v2=st.update(0,-6000000000LL,v1);
    int v3=st.update(1,9,v1);
    assert(st.get_sum(0,3,0)==0);
    assert(st.get_sum(0,3,v1)==4000000000LL);
    assert(st.get_sum(0,3,v2)==-2000000000LL);
    assert(st.get_sum(0,3,v3)==9);
    for(int n=1;n<=30;++n) for(int k=0;k<=n+1;++k) {
        vector<int>a(n); for(int& x:a)x=rnd(8);
        SumTree<int> tree(n);
        auto roots=capped_versions(a,k,7,tree);
        for(int l=0;l<n;++l) for(int r=l+1;r<=n;++r) {
            int count[8]={},want=0;
            for(int i=l;i<r;++i)++count[a[i]];
            for(int x:count)want+=min(k,x);
            assert(tree.get_sum(l,r,roots[r-1])==want);
        }
    }
    // Exercise the exact printed online decoding example.
    string input="5 2\n1 1 1 2 2\n4\n0 4\n0 0\n1 3\n8 9\n";
    istringstream in(input); ostringstream out;
    auto* old_in=cin.rdbuf(in.rdbuf()); auto* old_out=cout.rdbuf(out.rdbuf());
    persistent_example();
    cin.rdbuf(old_in); cout.rdbuf(old_out);
    assert(out.str()=="4 1 3 2 ");
}
int components(int n,const vector<pair<int,int>>& edges,int skip_v=-1,int skip_e=-1) {
    vector<vector<int>> adj(n);
    for(int i=0;i<int(edges.size());++i) {
        auto [a,b]=edges[i];
        if(i!=skip_e&&a!=skip_v&&b!=skip_v) {adj[a].eb(b);adj[b].eb(a);}
    }
    int ans=0;vector<bool> seen(n);
    for(int s=0;s<n;++s) if(s!=skip_v&&!seen[s]) {
        ++ans;vector<int>q{s};seen[s]=true;
        for(int j=0;j<int(q.size());++j)for(int v:adj[q[j]])if(!seen[v]){seen[v]=true;q.eb(v);}
    }
    return ans;
}
void check_graph(int n,const vector<pair<int,int>>& edges) {
    bridges_and_cuts bc(n,edges);
    int base=components(n,edges);
    vector<int> want;
    for(int e=0;e<int(edges.size());++e)if(components(n,edges,-1,e)>base)want.eb(e);
    sort(all(bc.bridges)); assert(bc.bridges==want);
    for(int v=0;v<n;++v)assert(bc.is_cut[v]==(components(n,edges,v)>base));
}
void bridges_tests() {
    check_graph(0,{});
    for(int n=1;n<=5;++n) {
        vector<pair<int,int>> possible;
        for(int i=0;i<n;++i)for(int j=i+1;j<n;++j)possible.eb(i,j);
        for(int mask=0;mask<(1<<possible.size());++mask) {
            vector<pair<int,int>> e;
            for(int i=0;i<int(possible.size());++i)if(mask>>i&1)e.eb(possible[i]);
            check_graph(n,e);
        }
    }
    for(int it=0;it<5000;++it) {
        int n=1+rnd(12),m=rnd(35);vector<pair<int,int>>e;
        while(m--)e.eb(rnd(n),rnd(n));
        check_graph(n,e);
    }
}
void hld_edge_tests() {
    for(int n=1;n<=40;++n) {
        vector<vector<int>>adj(n);vector<int>par(n,-1),depth(n),value(n);
        for(int v=1;v<n;++v){par[v]=rnd(v);depth[v]=depth[par[v]]+1;adj[v].eb(par[v]);adj[par[v]].eb(v);}
        HLD<true> hld(adj);
        for(int it=0;it<800;++it) {
            int a=rnd(n),b=rnd(n),u=a,v=b;
            vector<int>path;
            while(u!=v){if(depth[u]<depth[v])swap(u,v);path.eb(u);u=par[u];}
            if(it%2){int delta=rnd(41)-20;hld.modifyPath(a,b,delta);for(int x:path)value[x]+=delta;}
            int best=INT_MIN;for(int x:path)best=max(best,value[x]);
            assert(hld.queryPath(a,b)==best);
            int root=rnd(n);best=INT_MIN;
            for(int x=1;x<n;++x){int y=par[x];while(y!=-1&&y!=root)y=par[y];if(y==root)best=max(best,value[x]);}
            assert(hld.querySubtree(root)==best);
        }
    }
}
int main(){lazy_tests();persistent_tests();bridges_tests();hld_edge_tests();cout<<"Structure tests passed\n";}
