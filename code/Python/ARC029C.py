class UnionFind:
    def __init__(self, n):
        self.par = [-1]*n
        self.siz = [1]*n

    #経路圧縮あり
    def root(self, x):
        if self.par[x] == -1:
            return x

        self.par[x] = self.root(self.par[x])
        return self.par[x]

    #経路圧縮なし
    """     
    def root(self, x):
        if self.par[x] == -1:
            return x
        return self.root(self.par[x])
    """
    
    def unite(self, x, y):
        rx = self.root(x)
        ry = self.root(y)
        if rx == ry:
            return False
        if self.size(rx) < self.size(ry):
            rx, ry = ry, rx

        self.par[ry] = rx
        self.siz[rx] += self.siz[ry]
        return True


    def same(self, x, y):
        return self.root(x) == self.root(y)

    def size(self, x):
        return self.siz[self.root(x)]

#解答の方針
#交易所の設置を要素n+1と連結にするコストとすることで,1~n+1の要素が連結になることを条件にできます。
#それによって、クラスカル法で求めることができます。

n, m = map(int, input().split())
uf = UnionFind(n+1)

ci = [(0, 0)]*(n+m)
a = [0]*(n+m)
b = [0]*(n+m)

for i in range(n):
    c = int(input())
    ci[i] = (c, i)
    a[i] = i
    b[i] = n


for i in range(m):
    a[i+n], b[i+n], c = map(int, input().split())
    a[i+n] -= 1
    b[i+n] -= 1
    ci[i+n] = (c, i+n)

ci.sort()
ans = 0

for i in range(n+m):
    if uf.unite(a[ci[i][1]], b[ci[i][1]]):
        ans += ci[i][0]

print(ans)

exit()
