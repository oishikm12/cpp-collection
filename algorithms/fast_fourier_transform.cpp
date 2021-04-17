#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll MOD = 998244353;

/** FTT Template Start **/

struct base {
    double x, y;

    base() {
        x = y = 0;
    }

    base(double a, double b): x(a), y(b) {}
};

inline base operator+(base a, base b) {
    return base(a.x + b.x, a.y + b.y);
}

inline base operator-(base a, base b) {
  return base(a.x - b.x, a.y - b.y);
}

inline base operator*(base a, base b) {
  return base(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

inline base conjugate(base a) {
  return base(a.x, -a.y);
}

ll lim = 1;

vector<base> roots = {{0, 0}, {1, 0}};
vector<ll> rev = {0, 1};

const double PI = acosl(-1.0);

void ensure_base(ll p) {
    if (p <= lim) return;

    ll size = 1 << p;

    rev.resize(size);

    for (ll i = 0; i < size; i += 1) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (p - 1));
    roots.resize(1 << p);

    while (lim < p) {
        double angle = 2 * PI / (1 << (lim + 1));
        for (ll i = 1 << (lim - 1); i < (1 << lim); i += 1) {
            roots[i << 1] = roots[i];
            double angle_i = angle * (2 * i + 1 - (1 << lim));
            roots[(i << 1) + 1] = base(cos(angle_i), sin(angle_i));
        }
        lim++;
    }
}

void fft(vector<base> &a, ll n = -1) {
    if (n == -1) n = a.size();

    assert((n & (n - 1)) == 0);
    ll zeros = __builtin_ctz(n);
    ensure_base(zeros);

    ll shift = lim - zeros;

    for (ll i = 0; i < n; i += 1) {
        if (i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
    }

    for (ll k = 1; k < n; k <<= 1) { 
        for (ll i = 0; i < n; i += 2 * k) {
            for (ll j = 0; j < k; j++) {
                base z = a[i + j + k] * roots[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b, ll eq = 0) {
    ll need = a.size() + b.size() - 1;
    ll p = 0;

    while ((1 << p) < need) p += 1;
    ensure_base(p);
    ll sz = 1 << p;
    vector<base> A, B;

    if (sz > (ll)A.size()) A.resize(sz);

    for (ll i = 0; i < (ll)a.size(); i += 1) {
        ll x = (a[i] % MOD + MOD) % MOD;
        A[i] = base(x & ((1 << 15) - 1), x >> 15);
    }

    fill(A.begin() + a.size(), A.begin() + sz, base {0, 0});
    fft(A, sz);

    if (sz > (ll)B.size()) B.resize(sz);

    if (eq) copy(A.begin(), A.begin() + sz, B.begin());
    else {
        for (ll i = 0; i < (ll)b.size(); i += 1) {
            ll x = (b[i] % MOD + MOD) % MOD;
            B[i] = base(x & ((1 << 15) - 1), x >> 15);
        }

        fill(B.begin() + b.size(), B.begin() + sz, base {0, 0});
        fft(B, sz);
    }

    double ratio = 0.25 / sz;

    base r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);

    for (ll i = 0; i <= (sz >> 1); i += 1) {
        ll j = (sz - i) & (sz - 1);

        base a1 = (A[i] + conjugate(A[j])), a2 = (A[i] - conjugate(A[j])) * r2;
        base b1 = (B[i] + conjugate(B[j])) * r3, b2 = (B[i] - conjugate(B[j])) * r4;

        if (i != j) {
            base c1 = (A[j] + conjugate(A[i]));
            base c2 = (A[j] - conjugate(A[i])) * r2;
            base d1 = (B[j] + conjugate(B[i])) * r3;
            base d2 = (B[j] - conjugate(B[i])) * r4;

            A[i] = c1 * d1 + c2 * d2 * r5;
            B[i] = c1 * d2 + c2 * d1;
        }

        A[j] = a1 * b1 + a2 * b2 * r5;
        B[j] = a1 * b2 + a2 * b1;
    }

    fft(A, sz);
    fft(B, sz);

    vector<ll> res(need);

    for (ll i = 0; i < need; i++) {
        ll aa = A[i].x + 0.5;
        ll bb = B[i].x + 0.5;
        ll cc = A[i].y + 0.5;
        res[i] = (aa + ((bb % MOD) << 15) + ((cc % MOD) << 30)) % MOD;
    }

    return res;
}

template<int32_t MOD> 
struct modint {
    int32_t value;

    modint() = default;
    modint(int32_t value_): value(value_) {}
    
    inline modint<MOD> operator+(modint<MOD> other) const {
        int32_t c = this->value + other.value;
        return modint<MOD> (c >= MOD ? c - MOD : c);
    }

    inline modint<MOD> operator-(modint<MOD> other) const {
        int32_t c = this->value - other.value;
        return modint<MOD> (c < 0 ? c + MOD : c);
    }

    inline modint<MOD> operator*(modint<MOD> other) const {
        int32_t c = (int64_t) this -> value * other.value % MOD;
        return modint<MOD> (c < 0 ? c + MOD : c);
    }

    inline modint<MOD>& operator+=(modint<MOD> other) {
        this -> value += other.value;
        if (this -> value >= MOD) this -> value -= MOD;
        return *this;
    }

    inline modint<MOD>& operator-=(modint<MOD> other) {
        this -> value -= other.value;
        if (this -> value < 0) this -> value += MOD;
        return *this;
    }

    inline modint<MOD>& operator*=(modint<MOD> other) {
        this -> value = (int64_t) this -> value * other.value % MOD;
        if (this -> value < 0) this -> value += MOD;
        return *this;
    }

    inline modint<MOD> operator-() const {
        return modint<MOD> (this -> value ? MOD - this -> value : 0);
    }

    modint<MOD> pow(uint64_t k) const {
        modint<MOD> x = *this;
        modint<MOD> y = 1;

        for (; k; k >>= 1) {
            if (k & 1) y *= x;
            x *= x;
        }

        return y;
    }

    modint<MOD> inv() const {
        return pow(MOD - 2);
    }

    inline modint<MOD> operator/(modint<MOD> other) const {
        return *this * other.inv();
    }

    inline modint<MOD> operator/=(modint<MOD> other) {
        return *this *= other.inv();
    }

    inline bool operator==(modint<MOD> other) const {
        return value == other.value;
    }

    inline bool operator!=(modint<MOD> other) const {
        return value != other.value;
    }

    inline bool operator<(modint<MOD> other) const {
        return value < other.value;
    }

    inline bool operator>(modint<MOD> other) const {
        return value > other.value;
    }
};

template <int32_t MOD> 
modint<MOD> operator*(int64_t value, modint<MOD> n) {
    return modint<MOD> (value) * n;
}

template <int32_t MOD> 
modint<MOD> operator*(int32_t value, modint<MOD> n) {
    return modint<MOD> (value % MOD) * n;
}

template <int32_t MOD> 
ostream& operator<<(ostream &out, modint<MOD> n) {
    return out << n.value;
}

typedef modint<MOD> mint;

struct poly {
    vector<mint> a;

    inline void normalize() {
        while ((ll) a.size() && a.back() == 0) a.pop_back();
    }

    template<class...Args> 
    poly(Args...args): a(args...) {}

    poly(const initializer_list<mint> &x): a(x.begin(), x.end()) {}

    ll size() const {
        return (ll) a.size();
    }

    inline mint coef(const ll i) const {
        return (i < (ll)a.size() && i >= 0) ? a[i] : mint(0);
    }

    mint operator[](const ll i) const {
        return (i < (ll)a.size() && i >= 0) ? a[i] : mint(0);
    }

    bool is_zero() const {
        for (ll i = 0; i < size(); i += 1) if (a[i] != 0) return 0;
        return 1;
    }

    poly operator+(const poly &x) const {
        ll n = max(size(), x.size());
        vector<mint> ans(n);

        for (ll i = 0; i < n; i += 1) ans[i] = coef(i) + x.coef(i);

        while ((ll)ans.size() && ans.back() == 0) ans.pop_back();
        return ans;
    }

    poly operator-(const poly &x) const {
        ll n = max(size(), x.size());
        vector<mint> ans(n);

        for (ll i = 0; i < n; i += 1) ans[i] = coef(i) - x.coef(i);

        while ((ll)ans.size() && ans.back() == 0) ans.pop_back();
        return ans;
    }

    poly operator*(const poly &b) const {
        if (is_zero() || b.is_zero()) return {};

        vector<ll> A, B;

        for (auto x: a) A.push_back(x.value);
        for (auto x: b.a) B.push_back(x.value);

        auto res = multiply(A, B, (A == B));
        vector<mint> ans;

        for (auto x: res) ans.push_back(mint(x));

        while ((ll) ans.size() && ans.back() == 0) ans.pop_back();
        return ans;
    }

    poly operator*(const mint &x) const {
        ll n = size();
        vector<mint> ans(n);
        for (ll i = 0; i < n; i += 1) ans[i] = a[i] * x;
        return ans;
    }

    poly operator/(const mint &x) const {
        return (*this) * x.inv();
    }

    poly& operator+=(const poly &x) {
        return *this = (*this) + x;
    }

    poly& operator-=(const poly &x) {
        return *this = (*this) - x;
    }

    poly& operator*=(const poly &x) {
        return *this = (*this) * x;
    }

    poly& operator*=(const mint &x) {
        return *this = (*this) * x;
    }

    poly& operator/=(const mint &x) {
        return *this = (*this) / x;
    }

    poly mod_xk(ll k) const {
        return {a.begin(), a.begin() + min(k, size())};
    }

    poly mul_xk(ll k) const {
        poly ans( * this);
        ans.a.insert(ans.a.begin(), k, 0);
        return ans;
    }

    poly div_xk(ll k) const {
        return vector<mint> (a.begin() + min(k, (ll) a.size()), a.end());
    }

    poly substr(ll l, ll r) const {
        l = min(l, size());
        r = min(r, size());
        return vector<mint> (a.begin() + l, a.begin() + r);
    }

    poly reverse_it(ll n, bool rev = 0) const {
        poly ans(*this);

        if (rev) ans.a.resize(max(n, (ll)ans.a.size()));

        reverse(ans.a.begin(), ans.a.end());
        return ans.mod_xk(n);
    }

    poly differentiate() const {
        ll n = size();
        vector<mint> ans(n);
        for (ll i = 1; i < size(); i += 1) ans[i - 1] = coef(i) * i;
        return ans;
    }

    poly inverse(ll n) const {
        assert(!is_zero());
        assert(a[0] != 0);
        poly ans {mint(1) / a[0]};

        for (ll i = 1; i < n; i *= 2) {
            ans = (ans * mint(2) - ans * ans * mod_xk(2 * i)).mod_xk(2 * i);
        }
        return ans.mod_xk(n);
    }

    pair<poly, poly> divmod_slow(const poly &b) const {
        vector<mint> A(a);
        vector<mint> ans;

        while (A.size() >= b.a.size()) {
            ans.push_back(A.back() / b.a.back());
            if (ans.back() != mint(0)) {
                for (size_t i = 0; i < b.a.size(); i += 1) {
                    A[A.size() - i - 1] -= ans.back() * b.a[b.a.size() - i - 1];
                }
            }
            A.pop_back();
        }

        reverse(ans.begin(), ans.end());
        return {ans, A};
    }

    pair<poly, poly> divmod(const poly &b) const {
        if (size() < b.size()) return {poly {0}, *this};

        ll d = size() - b.size();
        if (min(d, b.size()) < 250) return divmod_slow(b);

        poly D = (reverse_it(d + 1) * b.reverse_it(d + 1).inverse(d + 1)).mod_xk(d + 1).reverse_it(d + 1, 1);
        return {D, *this - (D * b)};
    }

    poly operator/(const poly &t) const {
        return divmod(t).first;
    }

    poly operator%(const poly &t) const {
        return divmod(t).second;
    }

    poly& operator/=(const poly &t) {
        return *this = divmod(t).first;
    }

    poly& operator%=(const poly &t) {
        return *this = divmod(t).second;
    }

    mint eval(mint x) {
        mint ans(0);
        for (ll i = (ll) size() - 1; i >= 0; i -= 1) {
            ans *= x;
            ans += a[i];
        }
        return ans;
    }

    poly buidouble(vector<poly> &ans, ll v, ll l, ll r, vector<mint> &vec) {
        if (l == r) return ans[v] = poly({-vec[l], 1});
        ll mid = (l + r) >> 1;
        return ans[v] = buidouble(ans, 2 * v, l, mid, vec) * buidouble(ans, 2 * v + 1, mid + 1, r, vec);
    }

    vector<mint> eval(vector<poly> &tree, ll v, ll l, ll r, vector<mint> &vec) {
        if (l == r) return {eval(vec[l])};

        if (size() < 100) {
            vector<mint> ans(r - l + 1, 0);
            for (ll i = l; i <= r; i += 1) ans[i - l] = eval(vec[i]);
            return ans;
        }

        ll mid = (l + r) >> 1;
        auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, mid, vec);
        auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, mid + 1, r, vec);
        A.insert(A.end(), B.begin(), B.end());
        return A;
    }

    vector<mint> eval(vector<mint> x) {
        ll n = x.size();
        if (is_zero()) return vector<mint> (n, mint(0));

        vector<poly> tree(4 * n);
        buidouble(tree, 1, 0, n - 1, x);
        return eval(tree, 1, 0, n - 1, x);
    }
};

poly mul(ll l, ll r, vector<mint> &a) {
    if (l == r) return poly({-a[l], 1});
    ll mid = (l + r) >> 1;
    return mul(l, mid, a) * mul(mid + 1, r, a);
}

/** FTT Template End **/