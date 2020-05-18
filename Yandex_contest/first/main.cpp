#include<iostream>
#include<string>
#include<vector>

using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
const ld eps = 1e-9;
const ll settled = 1000007;
int cur_size = 1e6;

struct node{
    vector<int> ch = vector<int>(26, -1);
    string value = "1";;
}origin;

void tl()
{
    for(;;)
        cout << 1 << endl;
}

int last = 0;
vector<node> trie;

int main()
{
    string input;
    trie.push_back(origin);
        while (cin.peek() != '\n') {
            cin >> input;
            int cur = 0;
            for (int i = 0; i < input.size() - 1; i++) {
                int move = (input[i + 1] - input[i] + 26) % 26;
                if (trie[cur].ch[move] == -1) {
                    trie[cur].ch[move] = trie.size();
                    trie.push_back(origin);
                    // if (last == cur_size - 1) {
                    //     cur_size *= 2;
                    //     trie.resize(cur_size);
                    // }
                    if (last > ll(1e6))
                        tl();
                }
                cur = trie[cur].ch[move];
            }
            trie[cur].value = input;
        }

    int amount;
    cin >> amount;
    vector<int> ans(amount);
    for(int i = 0; i < amount; i++)
    {
        cin >> input;
        int cur = 0;
        for(int j = 0; j < input.size()-1; j++)
        {
            int move = (input[j + 1] - input[j] + 26)%26;
            cur = trie[cur].ch[move];
            if(cur <= 0)
                tl();
        }
        ans[i] = cur;
    }
    for(int i = 0; i < amount; i++) {
        if(trie[ans[i]].value == "1")
            tl();
        cout << trie[ans[i]].value << '\n';
    }
    return 0;
}