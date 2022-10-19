#解答の方針
#これはクラスカル法で解けますが、愚直にUnionFindで行うと当然制約からTLEします。
#クラスカル法のアイデアからコストが小さい順に要素aと要素bにパスがない時に繋ぎます。
#考察するとグループ数はgcd(グループ数,a[i])に減少するのでこれをを用いることで高速に計算できます。

def gcd(a, b):
    if a % b == 0:
        return b
    return gcd(b, a % b)

n, m = map(int, input().split())

ca = [(0, 0)]*m
for i in range(m):
    a, c = map(int, input().split())
    ca[i] = (c, a)

ca.sort()
ans = 0

for i in range(m):
    nxt = gcd(n, ca[i][1])
    ans += (n - nxt)*ca[i][0]
    n = nxt

if nxt != 1:
    print(-1)
else: 
    print(ans)

exit()


