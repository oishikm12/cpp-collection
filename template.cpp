#include <bits/stdc++.h>
using namespace std;

// Shorthand Type Definitions
typedef long long int ll;
typedef long double ld;
typedef complex<ld> cd;

// Short Utility Texts
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

// Macros for faster access to properties
#define rep(i, a, b) for (ll i = (a); i < (b); i += 1)
#define repr(i, a, b) for (ll i = (a) - 1; i >= (b); i -= 1)
#define trav(a, x) for (auto &a : (x))
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define present(c, x) (c).find(x) != (c).end()
#define cpresent(c, x) find(all(c), (x)) != (c).end()
#define mset(x, y) memset ((x), (y), sizeof (x))
#define mcpy(x, y) memcpy ((x), (y), sizeof (x))
#define sz(a) (ll)(a).size()

// Constant Value Declarations
const ll MAX = 1e9;
const ll MIN = -MAX;
const ll MOD = 1e9 + 7;
const ll FFT = 998244353;
const ll INF = 1e18;
const ll NINF = -INF;
const char nl = '\n';
const double PI = acos(-1);

// Overload for common input & output
template <typename T, typename U> istream& operator>>(istream& is, pair<T, U> &p) { cin >> p.first >> p.second; return is; }
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T, U> &p) { cout << p.first << p.second ; return os; }
template <typename T> istream& operator>>(istream& is, vector<T> &v) { trav(x, v) cin >> x; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T> &v) { trav(x, v) cout << x << ' '; return os; }
template <typename T> istream& operator>>(istream& is, vector<vector<T>> &v) { trav(x, v) trav(y, x) cin >> y; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<vector<T>> &v) { trav(x, v) { trav(y, x) cout << y << ' '; cout << nl; } return os; }

// Common Use functions
template <typename T, typename U> inline void amin(T &x, U y) { if((y) < (x)) x = y; }
template <typename T, typename U> inline void amax(T &x, U y) { if((x) < (y)) x = y; }

ll totient(ll n) {
    ll res = n;
    for (ll i = 2; i <= sqrt(n); i += 1) {
        if (n % i != 0) continue;
        while (n % i == 0) n /= i; 
        res = (res * (i - 1) / i);
    } 
    if (n > 1) res = (res * (n - 1) / n); 
    return res;
}

ll powMod(ll a, ll b, ll mod) {
    ll res = 1; 
    while (b > 0) {
        if (b & 1) res = (res * a) % mod; 
        a = (a * a) % mod; 
        b = b >> 1;
    }
    return res;
}

ll addMod(ll a, ll b, ll mod) { return (a + b + mod) % mod; }
ll subMod(ll a, ll b, ll mod) { return (a - b + mod) % mod; }
ll mulMod(ll a, ll b, ll mod) { return ((a % mod * b % mod) + mod) % mod; }

ll modInv(ll a, ll mod) { return powMod(a % mod, mod - 2, mod); }
ll divPrimeMod(ll a, ll b, ll mod) { return mulMod(a, modInv(b, mod), mod); }

ll permutation(ll n, ll r, ll mod, vector<ll> &fact, vector<ll> &ifact) { return mulMod(fact[n], ifact[n - r], mod); }
ll combination(ll n, ll r, ll mod, vector<ll> &fact, vector<ll> &ifact) { return mulMod(mulMod(fact[n], ifact[n - r], mod), ifact[r], mod); }

vector<string> split(string &s, string delim) {
    vector<string> words;
    string word;
    istringstream tokenStream(s);
    while (getline(tokenStream, word, delim[0])) words.pb(word);
    return words;
}

string join(vector<string> &words, string delim) {
    ostringstream tokenStream;
    copy(words.begin(), words.end() - 1, ostream_iterator<int>(tokenStream, delim.data()));
    tokenStream << words.back();
    return tokenStream.str();
}

void sieve(vector<bool> &primes, ll range) {
    primes[0] = primes[1] = false;
    ll lim = sqrtl(range);
    rep(i, 2, lim + 1) if (primes[i]) for (ll j = i * i; j <= range; j += i) primes[j] = false;
}

void invFact(vector<ll> &factorial, vector<ll> &invFactorial, ll mod) {
    ll size = sz(invFactorial) - 1;
    invFactorial[size] = modInv(factorial[size], mod);
    repr(i, size, 0) invFactorial[i] = mulMod(invFactorial[i + 1], i + 1, mod);
}

void fact(vector<ll> &factorial, ll mod) {
    ll size = sz(factorial);
    factorial[0] = 1;
    rep(i, 1, size) factorial[i] = mulMod(factorial[i - 1], i, mod);
}

void google(ll t) { cout << "Test #" << t << ": "; }

// Debug Functionality
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(char *x) {cerr << '\"' << x << '\"';}
void __print(string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V> void __print(pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T> void __print(T &x) {int f = 0; cerr << '{'; trav(i, x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V> void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)

// Main function
void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    ll t;
    cin >> t;
    
    rep(i, 0, t) {
        solve();
    }
    
    return 0;
}

void solve() {
    /**
     * This is a template for competitive coding.
     * Write your solution here
     */ 
}