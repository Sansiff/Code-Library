#include <iostream>
#include <vector>

struct SegmentTree{
    struct node{
        int l, r;
        long long tag, sum;
    };
    std::vector<node> tr;
    std::vector<long long> w;
    
    SegmentTree(int _n) : tr((_n + 1) << 2), w(_n + 1) { }  
    
    void pushup(int u){
        tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;  
    }

    void pushdown(int u){
        if(tr[u].tag){
            tr[u<<1].tag += tr[u].tag, tr[u<<1|1].tag += tr[u].tag;
            tr[u<<1].sum += (tr[u<<1].r - tr[u<<1].l + 1) * tr[u].tag;
            tr[u<<1|1].sum += (tr[u<<1|1].r - tr[u<<1|1].l + 1) * tr[u].tag;
            tr[u].tag = 0;
        }
    }

    void build(int u, int l, int r){
        tr[u] = {l, r, 0, w[r]};
        if(l == r) return;
        int mid = (l + r) >> 1;
        build(u<<1, l, mid), build(u<<1|1, mid+1, r);
        pushup(u);
    }

    void modify(int u, int l, int r, int v){
        if(l <= tr[u].l && tr[u].r <= r){
            tr[u].sum += (tr[u].r - tr[u].l + 1) * v;
            tr[u].tag += v;
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) modify(u<<1, l, r, v);
        if(r > mid) modify(u<<1|1, l, r, v);
        pushup(u);
    }

    long long query(int u, int l, int r){
        if(l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
        if(l > tr[u].r || r < tr[u].l) return 0;
        pushdown(u);
        return query(u<<1, l, r) + query(u<<1|1, l, r);
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m; std::cin >> n >> m;
    SegmentTree tr(n);
    for(int i = 1; i <= n; i ++){
        std::cin >> tr.w[i];
    }
    tr.build(1, 1, n);
    while(m --){
        int op, l, r, v; std::cin >> op;
        if(op == 1){
            std::cin >> l >> r >> v;
            tr.modify(1, l, r, v);
        } else{
            std::cin >> l >> r;
            std::cout << tr.query(1, l, r) << "\n";
        }
    }
    return 0;
}
