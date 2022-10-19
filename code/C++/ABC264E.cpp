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
//一度切れたらその後ずっと切れたままなので、先に切れることのない線は繋いでしまいます。
//その後、切れる順番が後ろの方から繋いでいけば答えが後ろからもとまります。
//ここで、発電所はM個ありますが、一つにまとめても支障はないため、まとめることで実装を楽にしています。

int main(){
    int n, m, e;
    std::cin >> n >> m >> e;
    std::vector<std::pair<int,int>> uv(e);
    for(int i = 0;i < e;++i){
        std::cin >> uv[i].first >> uv[i].second;
        --uv[i].first;
        --uv[i].second;

        if(uv[i].first >= n) uv[i].first = n;
        if(uv[i].second >= n) uv[i].second = n;
    }

    int q;
    std::cin >> q;
    
    std::vector<int> x(q);
    std::vector<bool> connect(e, true);
    for(int i = 0;i < q;++i){
        std::cin >> x[i];
        --x[i];
        connect[x[i]] = false;
    }

    UnionFind uf(n+1);

    for(int i = 0;i < e;++i){
        if(connect[i]) uf.unite(uv[i].first, uv[i].second);
    }

    std::vector<int> ans(q);
    for(int i = q-1;i >= 0;--i){
        ans[i] = uf.size(n) - 1;
        uf.unite(uv[x[i]].first, uv[x[i]].second);
    }

    for(int i = 0;i < q;++i){
        std::cout << ans[i] << std::endl;
    }

    return 0;
}
