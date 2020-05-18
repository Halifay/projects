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
const ld eps = 1e-9;
const ll settled = 1000007;


int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> plates(n);
    for(int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        if(a < b)
            swap(a, b);
        plates[i] = {a, b};
    }
    sort(plates.begin(), plates.end());
    int m = 0;
    int lastm = 0;
    int ans = 0;
    for(int i = n-1; i>=0; i--)
    {
        if(i < n-1 && plates[i].first != plates[i+1].first)
            m = max(m, lastm);
        if(plates[i].second >= m)
        {
            ans++;
            lastm = max(lastm, plates[i].second);
        }
    }
    cout << ans;
    return 0;
}

