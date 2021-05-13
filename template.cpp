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
#define repr(i, a, b) for (ll i = (b) - 1; i >= (a); i -= 1)
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
const ll MOD = 1e9 + 7;
const ll FFT = 998244353;
const ll INF = 1e18;
const char nl = '\n';
const double PI = acos(-1);

// Overload for common input & output
template <typename T, typename U> istream& operator>>(istream& is, pair<T, U> &p) { cin >> p.first >> p.second; return is; }
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T, U> &p) { cout << p.first << p.second ; return os; }
template <typename T> istream& operator>>(istream& is, vector<T> &v) { rep(i, 0, sz(v)) cin >> v[i]; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T> &v) { trav(x, v) cout << x << ' '; return os; }
template <typename T> istream& operator>>(istream& is, vector<vector<T>> &v) { rep(i, 0, sz(v)) rep(j, 0, sz(v[0])) cin >> v[i][j]; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<vector<T>> &v) { trav(x, v) { trav(y, x) cout << y << ' '; cout << nl; } return os; }

// Common Use functions
template <typename T, typename U> inline void amin(T &x, U y) { if((y) < (x)) x = y; }
template <typename T, typename U> inline void amax(T &x, U y) { if((x) < (y)) x = y; }

ll totient(ll n) {
    ll number = n % 2 == 0 ? n / 2 : n; 
    while (n % 2 == 0) n /= 2;
    for (ll i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            while (n % i == 0) n /= i; 
            number = (number / i * (i - 1));
        }
    } 
    if (n > 1) number = (number / n * (n - 1)); 
    return number;
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

ll addMod(ll a, ll b, ll mod) { a = a % mod; b = b % mod; return (((a + b) % mod) + mod) % mod; }
ll subMod(ll a, ll b, ll mod) { a = a % mod; b = b % mod; return (((a - b) % mod) + mod) % mod; }
ll mulMod(ll a, ll b, ll mod) { a = a % mod; b = b % mod; return (((a * b) % mod) + mod) % mod; }

ll modInv(ll a, ll mod) { a = a % mod; return powMod(a, mod - 2, mod); }
ll divPrimeMod(ll a, ll b, ll mod) { a = a % mod; b = b % mod; return (mulMod(a, modInv(b, mod), mod) + mod) % mod; }

ll permutation(ll n, ll r, ll mod, vector<ll> &fact, vector<ll> &ifact) { return mulMod(fact[n], ifact[n - r], mod); }
ll combination(ll n, ll r, ll mod, vector<ll> &fact, vector<ll> &ifact) { return mulMod(mulMod(fact[n], ifact[n - r], mod), ifact[r], mod); }

vector<string> split(string &s, char delim) {
    vector<string> words;
    string word;
    istringstream tokenStream(s);
    while (getline(tokenStream, word, delim)) words.pb(word);
    return words;
}

string join(vector<string> &words, char delim) {
    ostringstream tokenStream;
    copy(words.begin(), words.end() - 1, ostream_iterator<int>(tokenStream, delim + ""));
    tokenStream << words.back();
    return tokenStream.str();
}

void sieve(vector<bool> &primes) {
    primes[2] = true;
    for (ll i = 3; i < sz(primes); i += 2) primes[i] = true;
    for (ll i = 3; i < sz(primes); i += 2) if (primes[i]) for (ll j = i * i; j < sz(primes); j += 2 * i) primes[j] = false;
}

void invFact(vector<ll> &factorial, vector<ll> &invFactorial, ll mod) {
    invFactorial[sz(invFactorial) - 1] = modInv(factorial[sz(invFactorial) - 1], mod);
	repr(i, 0, sz(invFactorial) - 1) invFactorial[i] = (invFactorial[i + 1] * (i + 1)) % mod;
}

void fact(vector<ll> &factorial, ll mod) {
    factorial[0] = 1;
    rep(i, 1, sz(factorial)) factorial[i] = (factorial[i - 1] * i) % mod;
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