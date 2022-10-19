#include<iostream>
#include<vector>

class UnionFind {
    public:
        std::vector<int> par, siz;
        UnionFind(int n): par(n, -1), siz(n, 1){}

        //経路圧縮あり
        int root(int x){
            if(par[x] == -1) return x;
            return par[x] = root(par[x]);
        }

        //経路圧縮なし
        /*int root(int x){
            if(par[x] == -1) return x;
            return root(par[x]);
        } */

        bool unite(int x, int y){
            int rx = root(x), ry = root(y);
            if(rx == ry) return false;
            if(size(rx) < size(ry)) std::swap(rx, ry);
            
            par[ry] = rx;
            siz[rx] += siz[ry];
            return true; 
        }

        bool same(int x, int y){
            return root(x) == root(y);
        }

        int size(int x){
            return siz[root(x)];
        }

};

//解答の方針
//隣合う人がひとつに対して3人以上いる、もしくは隣合う関係を辺で結んだ時閉路になると不可能なことがわかります。
//隣合う関係性は有向グラフではなく無向グラフで表せるのでUnion-Findで検出できます。

int main(){
    int n, m;
    std::cin >> n >> m;
    bool exist = true;
    std::vector<int> cnt(n, 0);
    UnionFind uf(n);
    for(int i = 0;i < m;++i){
        int a, b;
        std::cin >> a >> b;
        --a;--b;
        if(uf.unite(a, b) == false) exist = false;
        ++cnt[a];
        ++cnt[b];
        if(cnt[a] >= 3 || cnt[b] >= 3) exist = false;
    }

    if(exist) std::cout << "Yes" << std::endl;
    else std::cout << "No" << std::endl;

    return 0;
}
