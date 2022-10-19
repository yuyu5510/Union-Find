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
#一度切れたらその後ずっと切れたままなので、先に切れることのない線は繋いでしまいます。
#その後、切れる順番が後ろの方から繋いでいけば答えが後ろからもとまります。
#ここで、発電所はM個ありますが、一つにまとめても支障はないため、まとめることで実装を楽にしています。

n, m, e = map(int, input().split())
uf = UnionFind(n+1)

uv = []
for _ in range(e):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    if u >= n:
        u = n
    if v >= n:
        v = n
        
    uv.append([u, v])

q = int(input())
x = [int(input()) - 1 for _ in range(q)]

connect = [True]*e
for xnum in x:
    connect[xnum] = False

for i in range(e):
    if connect[i]:
        uf.unite(uv[i][0], uv[i][1])


ans = []
for i in reversed(range(q)):
    ans.append(uf.size(n) - 1)
    uf.unite(uv[x[i]][0], uv[x[i]][1])

for a in reversed(ans):
    print(a)
