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

