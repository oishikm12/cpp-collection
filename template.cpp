#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

#define rep(i, a, b) for (ll i = (a); i < (b); i += 1)
#define repr(i, a, b) for (ll i = (b) - 1; i >= (a); i -= 1)
#define trav(a, x) for (auto &a : (x))

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c),x) != (c).end())

#define sz(a) long long int((a).size())

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef complex<ld> cd;

const ll MAX = 1e9;
const ll MOD = 1e9 + 7;
const char nl = '\n';

template <typename T, typename U>
inline void amin(T &x, U y) { 
    if((y) < (x)) x = y; 
}

template <typename T, typename U>
inline void amax(T &x, U y) { 
    if((x) < (y)) x = y; 
}

template <typename T>
inline istream& operator>>(istream& is, vector<T> &vec) {
    rep(i, 0, vec.size()) cin >> vec[i];
    return is;
}

template <typename T>
inline ostream& operator<<(ostream& os, vector<T> &vec) {
    trav(x, vec) cout << x << nl; 
    return os;
}

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    ll t;
    cin >> t;
    
    while (t--) solve();
    
    return 0;
}

void solve() {
    /**
     * This is a template for competitive coding.
     * Write your solution here
     */ 
}