#include<iostream>
#include<vector>

#include<algorithm>

long long gcd (long long a, long long b){
    if(a % b == 0) return b;
    return gcd(b, a % b);
}

//解答の方針
//これはクラスカル法で解けますが、愚直にUnionFindで行うと当然制約からTLEします。
//クラスカル法のアイデアからコストが小さい順に要素aと要素bにパスがない時に繋ぎます。
//グループ数はgcd(グループ数,a[i])に減少することを用いることで高速に計算できます。

int main(){
    long long n, m;
    std::cin >> n >> m;
    std::vector<std::pair<long long,long long>> ac(m);
    for(int i = 0;i < m;++i){
        std::cin >> ac[i].second >> ac[i].first;
    }

    std::sort(ac.begin(), ac.end());
    long long ans = 0;
    for(int i = 0;i < m;++i){
        long long nxt = gcd(n, ac[i].second);
        ans += ac[i].first*(n - nxt);
        n = nxt;
    }

    if(n == 1)std::cout << ans << std::endl;
    else std::cout << -1 << std::endl;
    
    return 0;
}
