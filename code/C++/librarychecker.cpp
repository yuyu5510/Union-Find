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

//t=0の時つないで、1の時に同じグループが判定するだけです。
int main(){
    int n, q;
    std::cin >> n >> q;
    UnionFind uf(n);
    for(int i = 0;i < q;++i){
        int t, u, v;
        std::cin >> t >> u >> v;
        if(t == 0){
            uf.unite(u, v);
        }
        else{
            std::cout << uf.same(u, v) << std::endl;
        }
    }

    return 0;
}