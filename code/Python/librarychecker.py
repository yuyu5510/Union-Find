class UnionFind():

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

#t=0の時つないで、1の時に同じグループが判定するだけです。
n, q = map(int, input().split())

uf = UnionFind(n)

for i in range(q):
    t, u, v = map(int, input().split())
    if t == 0:
        uf.unite(u, v)
    else:
        if uf.same(u, v):
            print(1)
        else:
            print(0)


exit(0)


