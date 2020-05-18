#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
int main() {
#define not_at_home
#ifdef at_home
    freopen("/home/mikhail/Garage/C/Competition/input.txt", "r", stdin);
    freopen("/home/mikhail/Garage/C/Competition/output.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    for(int i = 0;i < n; i++)
    {
        string s;
        int length, period;
        cin >> length >> period;
        cin >> s;
        vector<vector<int>> from_left = vector<vector<int>>(length, vector<int>(2, 0)),
        from_right = vector<vector<int>>(length, vector<int>(2, 0));
        int sum = 0;
        for(int j = 0; j < length; j++)
        {
            int anc = j - period;
            vector<int> ch = vector<int>(2, 0);
            if(anc >= 0)
               ch = from_left[anc];
            if(j - 1 >= 0)
                sum += (s[j-1]=='1');
            if(j - period >= 0)
                sum -=(s[j-period]=='1');
            from_left[j][0] = ch[0] + sum + (s[j]=='1');
            from_left[j][1] = sum + (s[j]=='0') + min(ch[0], ch[1]);
        }
        sum = 0;
        for(int j = length-1; j >= 0; j--)
        {
            int anc = j + period;
            vector<int> ch = vector<int>(2, 0);
            if(anc < length)
                ch = from_right[anc];
            if(j + 1 < length)
                sum += (s[j+1]=='1');
            if(j + period < length)
                sum -=(s[j+period]=='1');
            from_right[j][0] = ch[0] + sum + (s[j]=='1');
            from_right[j][1] = sum + (s[j]=='0') + min(ch[0], ch[1]);
        }

        int ans = length;
        for(int j = 0; j < length; j++)
        {
            int zero = from_left[j][0] + from_right[j][0] - (s[j]=='1');
            int one = from_left[j][1] + from_right[j][1] - (s[j]=='0');
            ans = min(ans, min(zero, one));
        }
        cout << ans << endl;
    //     int w, h;
    //     cin >> h >> w;
    //     vector<vector<int>> field = vector<vector<int>>(h, vector<int>(w, 0));
    //     vector<vector<int>> used = vector<vector<int>>(h, vector<int>(w, 0));
    //     for(int j = 0; j < h; j++)
    //     {
    //         for (int k = 0; k < w; k++)
    //         {
    //             cin >> field[j][k];
    //         }
    //     }
    }
    return 0;
}
