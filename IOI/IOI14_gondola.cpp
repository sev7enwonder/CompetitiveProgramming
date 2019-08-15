// #include "gondola.h"
#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000009
typedef long long ll;
using namespace std;

ll valid(ll n, ll inputSeq[]) {
    vector<ll> gondolas;
    FOR(i, 0, n) gondolas.push_back(inputSeq[i]);
    sort(gondolas.begin(), gondolas.end());
    FOR(i, 1, n) if (gondolas[i] == gondolas[i - 1]) return 0;

    FOR(i, 0, n) {
        if (inputSeq[i] <= n) {
            FOR(j, 1, n + 1) {
                ll k = (i + j - inputSeq[i]) % n;
                while (k < 0) k += n;
                if (inputSeq[k] <= n && inputSeq[k] != j) return 0;
            }
            return 1;
        }
    }
    return 1;
}

//----------------------

ll replacement(ll n, ll gondolaSeq[], ll replacementSeq[]) {
    vector<pair<ll, ll>> broken;
    ll offset = 0;
    FOR(i, 0, n) {
        if (gondolaSeq[i] > n)
            broken.push_back({gondolaSeq[i], i + 1});
        else
            offset = i - gondolaSeq[i] + 1;
    }
    FOR(i, 0, broken.size()) {
        broken[i].second = (broken[i].second - offset - 1 + n) % n + 1;
    }

    ll indx = 0, curr = n;
    sort(broken.begin(), broken.end());
    for (pair<ll, ll> i : broken) {
        replacementSeq[indx++] = i.second;
        curr++;
        FOR(j, curr, i.first)
        replacementSeq[indx++] = j;
        curr = i.first;
    }

    return indx;
}

//----------------------

ll expo(ll x, ll y) {
    ll res = 1;
    x = x % MOD;
    while (y > 0) {
        if (y & 1) res = (res * x) % MOD;
        y = y >> 1;
        x = (x * x) % MOD;
    }
    return res;
}

ll countReplacement(ll n, ll inputSeq[]) {
    if (!valid(n, inputSeq)) return 0;
    // If there are k replaced cars {a, b}, {c, d}, ...
    // Then ans is k^(d - b) * (k - 1)^(f - d) + ...
    vector<ll> broken;
    broken.push_back(0);
    FOR(i, 0, n) {
        if (inputSeq[i] > n)
            broken.push_back((ll) (inputSeq[i] - n));
    }
    sort(broken.begin(), broken.end());
    ll ans = 1;
    FOR(i, 1, broken.size()) {
        ans = (ans * expo(broken.size() - i, broken[i] - broken[i - 1] - 1)) % MOD;
    }
    if (broken.size() == n + 1) ans = (ans * (ll)(n)) % MOD;
    return ans;
}

ll gondolas[100000], replacements[100000];

int main() {
    ll T, n;
    cin >> T >> n;
    FOR(i, 0, n) cin >> gondolas[i];
    if (T < 4) cout << valid(n, gondolas);
    else if (T < 7) {
        ll k = replacement(n, gondolas, replacements);
        cout << k << ' ';
        FOR(i, 0, k) cout << replacements[i] << ' ';
    }
    else cout << countReplacement(n, gondolas);
}