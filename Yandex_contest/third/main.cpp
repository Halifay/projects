#define _CRT_SECURE_NO_WARNINGS
#define forn(i, a, n) for(ll i = a; i < n; i++)

#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<iomanip>
#include <cassert>
#include<stack>
#include<deque>
#include<list>
#include<sstream>
#include<unordered_map>
#include<time.h>

#pragma comment(linker, "/STACK:88999999")
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef pair<pll, pll> ppp;
const ll mod = 1e9 + 7;
const ld eps = 1e-6;
const ll settled = 1000007;

void tl()
{
    for(;;)
        cout << 1 << endl;
}

class pol{
public:
    long double a = 0, b = 0, c = 0;
    long double le, ri;
};

pair<ld, ld> solve(pol third)
{
    pair<ld, ld> ans = {third.le - 1, third.le - 1};

    if(fabs(third.a) <= eps)
    {
        if(fabs(third.b) >= eps)
            ans.first = -third.c/third.b;
        return ans;
    }

    ld d = third.b * third.b - 4*third.a *third.c;
    if(d < 0)
        return ans;
    ans.first = (-third.b + sqrt(d))/(2*third.a);
    ans.second = (-third.b - sqrt(d))/(2*third.a);
    return ans;
}

pol get_third(pol first, pol second)
{
    pol third;
    third.le = max(first.le, second.le);
    third.ri = min(first.ri, second.ri);
    third.a = first.a - second.a;
    third.b = first.b - second.b;
    third.c = first.c - second.c;
    return third;
}

ld integrate(pol third, ld le, ld ri)
{
    ld ans = third.a*(ri*ri*ri - le*le*le)/3 + third.b*(ri*ri - le*le)/2 + third.c*(ri - le);
    if(ans < 0)
        ans *= -1;
    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<ld> ext;
    vector<pol> f(n), g(m);
    cin >> f[0].le;
    // cout << 1 << endl;
    for(int i = 0; i < n-1; i++)
    {
        ld border;
        cin >> border;
        f[i].ri = border;
        f[i + 1].le = border;
        ext.push_back(border);
    }
    cin >> f[n-1].ri;
    for(int i = 0; i < n; i++)
    {
        ld a, b, c;
        cin >> a >> b >> c;
        f[i].a = a;
        f[i].b = b;
        f[i].c = c;
    }

    cin >> g[0].le;
    for(int i = 0; i < m-1; i++)
    {
        ld border;
        cin >> border;
        g[i].ri = border;
        g[i + 1].le = border;
        ext.push_back(border);
    }
    cin >> g[m-1].ri;
    for(int i = 0; i < m; i++)
    {
        ld a, b, c;
        cin >> a >> b >> c;
        g[i].a = a;
        g[i].b = b;
        g[i].c = c;
    }

    // cout << 2 << endl;
    int fit = 0, git = 0;
    while(fit < n - 1 || git < m - 1) {
        pol first = f[fit], second = g[git];
        pol third = get_third(first, second);
        pair<ld, ld> roots = solve(third);
        if(roots.first >= third.le + eps && roots.first <= third.ri - eps)
            ext.push_back(roots.first);
        if(roots.second >= third.le + eps && roots.second <= third.ri - eps)
            ext.push_back(roots.second);
        if(first.ri < second.ri)
            fit++;
        else
            git++;
    }

    ext.push_back(f[0].le);
    ext.push_back(f[n-1].ri);
    sort(ext.begin(), ext.end());

    // cout << 3 << endl;

    fit = 0;
    git = 0;

    ld sum = 0;
    for(int i = 1; i < ext.size(); i++)
    {
        if(ext[i] >= f[fit].ri + eps)
            fit++;
        if(ext[i] >= g[git].ri + eps)
            git++;
        pol first = f[fit], second = g[git];
        pol third = get_third(first, second);
        sum += integrate(third, ext[i - 1], ext[i]);
    }
    cout << fixed;
    cout << setprecision(10);
    cout << sum;
    return 0;
}
