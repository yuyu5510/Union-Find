#include<iostream>
#include<vector>

#include<algorithm>

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
//交易所の設置を要素n+1と連結にするコストとすることで,1~n+1の要素が連結になることを条件にできます。
//それによって、クラスカル法で求めることができます。


int main(){
    int n, m;
    std::cin >> n >> m;
    UnionFind uf(n+1);
    std::vector<long long> a(n+m), b(n+m);
    std::vector<std::pair<long long, int>> ci(n+m);
    for(int i = 0;i < n;++i){
        long long c;
        std::cin >> c;
        ci[i] = std::make_pair(c, i);
        a[i] = i;
        b[i] = n;
    }

    for(int i = n;i < n+m;++i){
        std::cin >> a[i];
        std::cin >> b[i];
        --a[i];
        --b[i];
        long long c;
        std::cin >> c;
        ci[i] = std::make_pair(c, i);
    }

    std::sort(ci.begin(), ci.end());

    long long ans = 0;
    for(int  i = 0;i < n+m;++i){
        if(uf.unite(a[ci[i].second], b[ci[i].second])){
            ans += ci[i].first;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
