#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
#include<iomanip>
#include<deque>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
const ll mod = 1e9 + 7;
const ld eps = 1e-6;
const ll settled = 1000007;

class sqdec{
public:
    deque<deque<int>> sects;
    int psize, pnumb;
    deque<int> whats;
    sqdec(int size)
    {
        psize = int(sqrt(size))+100;
        pnumb = size/psize + (size/psize*psize != size);
        sects = deque<deque<int>>(pnumb, deque<int>(psize));
        whats = deque<int>(psize*pnumb + 1);
        for(int i = 0; i < pnumb; i++)
        {
            for(int j = 0; j < psize; j++)
            {
                sects[i][j] = i*psize + j + 1;
                whats[i*psize + j + 1] = i;
            }
        }
    }

    void move(int part, int pos)
    {
        int val = sects[part][pos];
        for(int i = pos; i > 0; i--)
            sects[part][i] = sects[part][i-1];
        sects[part].pop_front();
        for(int i = part; i > 0; i--) {
            sects[i].push_front(sects[i - 1].back());
            whats[sects[i][0]] = i;
            sects[i-1].pop_back();
        }
        sects[0].push_front(val);
        whats[val] = 0;
    }

    int get_by_val(int val)
    {
        int part = whats[val];
        int pos = 0;
        while(sects[part][pos] != val)
            pos++;
        move(part, pos);
        // for(int i = pos; i > 0; i--)
        //     sects[part][i] = sects[part][i-1];
        // sects[part].pop_front();
        // for(int i = part; i > 0; i--) {
        //     sects[i].push_front(sects[i - 1].back());
        //     whats[sects[i][0]] = i;
        //     sects[i-1].pop_back();
        // }
        // sects[0].push_front(val);
        // whats[val] = 0;
        return part * psize + pos + 1;
    }

    int get_by_position(int abspos)
    {
        abspos--;
        int part = abspos/psize;
        int pos = abspos%psize;
        int ans = sects[part][pos];
        move(part, pos);
        return ans;
    }
};

int main()
{
    int n, m, mode;
    cin >> n >> m >> mode;
    sqdec seq(m);
    vector<int> ans(n);
    for(int i = 0; i < n; i++)
    {
        int ch;
        cin >> ch;
        if(mode == 1)
            ans[i] = seq.get_by_val(ch);
        else
            ans[i] = seq.get_by_position(ch);
    }

    for(int i = 0; i < n; i++)
        cout << ans[i] << ' ';

    return 0;
}

