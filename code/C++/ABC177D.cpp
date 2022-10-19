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
//友達が一人もいないグループになるようにするには
//それぞれの人において（友達の数+自分の数）になることが必要です。
//したがって、友達が最も多い人の(友達の数 + 1)が答えになります

int main(){
    int n, m;
    std::cin >> n >> m;
    UnionFind uf(n);
    for(int i = 0;i < m;++i){
        int a, b;
        std::cin >> a >> b;
        --a;--b;
        uf.unite(a, b);
    }

    int ans = 1;
    for(int i = 0;i < n;++i){
        ans = std::max(ans, uf.size(i));
    }
    std::cout << ans << std::endl;

    return 0;
}
