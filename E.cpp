#include<bits/stdc++.h>
using namespace std;

template<int MOD_> struct modint {
  static constexpr int MOD = MOD_;
  static_assert(MOD_ > 0, "MOD must be positive");
  private:
  using ll = long long;
  int v;
  static int minv(int a, int m) {a %= m; assert(a); return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);}
  public:
  modint() : v(0) {}
  modint(ll v_) : v(int(v_ % MOD)) {if (v < 0) v += MOD;}
  explicit operator int() const {return v;}
  friend ostream& operator << (ostream& out, const modint& n) {return out << int(n);}
  friend istream& operator >> (istream& in, modint& n) {ll v_; in >> v_; n = modint(v_); return in;}
  friend bool operator == (const modint& a, const modint& b) {return a.v == b.v;}
  friend bool operator != (const modint& a, const modint& b) {return a.v != b.v;}
  modint inv() const {modint res; res.v = minv(v, MOD); return res;}
  friend modint inv(const modint& m) {return m.inv();}
  modint neg() const {modint res; res.v = v ? MOD - v : 0; return res;}
  friend modint neg(const modint& m) {return m.neg();}
  modint operator - () const {return neg();}
  modint operator + () const {return modint(*this);}
  modint& operator ++ () {v++; if (v == MOD) v = 0; return *this;}
  modint& operator -- () {if (v == 0) v = MOD; v--; return *this;}
  modint& operator += (const modint& o) {v += o.v; if (v >= MOD) v -= MOD; return *this;}
  modint& operator -= (const modint& o) {v -= o.v; if (v < 0) v += MOD; return *this;}
  modint& operator *= (const modint& o) {v = int(ll(v) * ll(o.v) % MOD); return *this;}
  modint& operator /= (const modint& o) {return *this *= o.inv();}
  friend modint operator ++ (modint& a, int) { modint r = a; ++a; return r; }
  friend modint operator -- (modint& a, int) { modint r = a; --a; return r; }
  friend modint operator + (const modint& a, const modint& b) {return modint(a) += b;}
  friend modint operator - (const modint& a, const modint& b) {return modint(a) -= b;}
  friend modint operator * (const modint& a, const modint& b) {return modint(a) *= b;}
  friend modint operator / (const modint& a, const modint& b) {return modint(a) /= b;}
};

const int MOD = (119 << 23) + 1;
using mint = modint<MOD>;

mint pw(mint x, int y) {
    mint z = 1;
    while (y) {
        if (y & 1) z *= x;
        x *= x;
        y >>= 1;
    }
    return z;
}

struct event {
    int u, v, x;
    event(int u_, int v_, int x_) {u = u_, v = v_, x = x_;}
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n), v(m);
    for (int &t : x) {
        cin >> t;
        t = -t;
    }
    for (int &t : v) {
        cin >> t;
    }

    vector<event> events;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            events.push_back(event(i, v[i], x[j]));
        }
    }
    sort(events.begin(), events.end(), [&](const event &a, const event &b) {
        return 1ll * a.x * b.v < 1ll * b.x * a.v;
    });

    mint ans = 0;
    vector<mint> f(m + 1, 0);
    vector<int> c(m, 0);
    f[0] = pw(n, m);
    for (auto e : events) {
        int u = e.u, v = e.v, x = e.x;
        f[0] /= (n - c[u]);
        for (int i = 1; i <= m / 2; ++i) {
            f[i] -= f[i - 1] * c[u];
        }
        ans += f[m / 2] * x / v;
        c[u] += 1;
        for (int i = m / 2; i >= 0; --i) {
            f[i] += f[i - 1] * c[u];
        }
        f[0] *= (n - c[u]);
    }
    cout << ans << '\n';
}