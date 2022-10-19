#include<iostream>
#include<vector>

#include<algorithm>
#include<string>

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
//つなげる必要があるかどうかは2点が連結かどうかを調べれば良いです
//クエリの部分も同じリストに入れてsortしてクラスカル法を適用していきます
//この時にクエリの場合は各回独立(別のクエリでは使えないので)、uniteではなくsameを使って判定します。

int main(){
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::pair<int,int>> ci(m+q);
    std::vector<int> a(m+q), b(m+q);
    UnionFind uf(n);

    for(int i = 0;i < m;++i){
        int c;
        std::cin >> a[i] >> b[i] >> c;
        --a[i]; --b[i];
        ci[i] = std::make_pair(c, i);
    }
    for(int i = m;i < m+q;++i){
        int c;
        std::cin >> a[i] >> b[i] >> c;
        --a[i]; --b[i];
        ci[i] = std::make_pair(c, i);
    }

    std::vector<std::string> ans(q);
    std::sort(ci.begin(), ci.end());
    for(int i = 0;i < m+q;++i){
        int idx = ci[i].second;
        if(idx < m){
            uf.unite(a[idx], b[idx]);
        }
        else{
            if(uf.same(a[idx], b[idx])){
                ans[idx - m] = "No";
            }
            else{
                ans[idx - m] = "Yes";
            }
        }
    }

    for(int i = 0;i < q;++i){
        std::cout << ans[i] << std::endl;
    }

    return 0;
}
