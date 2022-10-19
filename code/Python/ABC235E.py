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
#つなげる必要があるかどうかは2点が連結かどうかを調べれば良いです
#クエリの部分も同じリストに入れてsortしてクラスカル法を適用していきます
#この時にクエリの場合は各回独立(別のクエリでは使えないので)、uniteではなくsameを使って判定します。

n, m, q = map(int, input().split())

uf = UnionFind(n)

a = [0]*(m+q)
b = [0]*(m+q)
ci = []
for i in range(m+q):
    a[i], b[i], c = map(int, input().split())
    a[i] -= 1
    b[i] -= 1
    ci.append((c, i))

ci.sort()
ans = ["Yes"]*q

for i in range(m+q):
    if ci[i][1] < m:
        uf.unite(a[ci[i][1]], b[ci[i][1]])
    else:
        if uf.same(a[ci[i][1]], b[ci[i][1]]):
            ans[ci[i][1] - m] = "No"


for i in range(q):
    print(ans[i])

exit()