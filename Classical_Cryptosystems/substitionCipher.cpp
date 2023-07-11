#include <bits/stdc++.h>
using namespace std;

time_t current_time = time(NULL);

vector<pair<float, char>> freq = {{0.082, 'a'}, {0.015, 'b'}, {0.028, 'c'}, {0.043, 'd'}, {0.127, 'e'}, {0.022, 'f'}, {0.020, 'g'}, {0.061, 'h'}, {0.070, 'i'}, {0.002, 'j'}, {0.008, 'k'}, {0.04, 'l'}, {0.024, 'm'}, {0.067, 'n'}, {0.075, 'o'}, {0.019, 'p'}, {0.001, 'q'}, {0.06, 'r'}, {0.063, 's'}, {0.091, 't'}, {0.028, 'u'}, {0.01,'v'}, {0.023, 'w'}, {0.001, 'x'}, {0.020, 'y'}, {0.001, 'z'}};

void removeSpaces(string &s1)
{
    string ans = "";
    for (int i = 0; i < s1.length(); i++)
    {
        int j = 0;
        for (; j < s1.length() && s1[j] != ' '; j++)
        {
            ans += s1[j];
        }
        i = j;
    }
    s1 = ans;
}

void removeCapsAndCapitals(string &s)
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            ans += char(s[i] + 32);
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
            ans += s[i];
    }
    s = ans;
}

string encrypt(string &s, vector<int> &key)
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        ans += char(key[s[i] - 'a'] + 'a');
    }
    return ans;
}

string decrypt(string &s, vector<int> &revKey)
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        ans += char(revKey[s[i] - 'a'] + 'a');
    }
    return ans;
}

int main()
{
    srand((unsigned)time(NULL));
    freopen("msg_processed.txt", "r", stdin);
    string s;
    cin >> s; 

    // generate vec of mapping
    vector<int> mp(26, 0);
    for (int i = 0; i < 26; i++)
    {
        mp[i] = i;
    }
    // generate random mapping

    int x1 = 100;

    while (x1--)
    {
        int x2 = rand() % 26, x3 = rand() % 26;
        swap(mp[x2], mp[x3]);
    }

    string en = encrypt(s, mp);
    cout << en << endl;
    // generate mp inverse
    vector<int> mpInverse(26, 0);
    for (int i = 0; i < 26; i++)
    {
        mpInverse[mp[i]] = i;
    }
    string dec = decrypt(en, mpInverse);
    cout << dec << endl;

    // cryptanalysis

    sort(freq.rbegin(), freq.rend());
    // construct freq table
    vector<int> freq1(26, 0);
    for (int i = 0; i < en.length(); i++){
        freq1[en[i] - 'a']++; 
    }
    priority_queue < pair< int, char >, vector< pair<int, char> >, greater<pair<char, int>> > pq;
    for (int i = 0; i < freq.size(); i++){
        pq.push({freq1[i], char('a' + i)}); 
    }
    unordered_map<char, char> mp1;
    for (int i = 0; i < 26 && !pq.empty(); i++){
        mp1[pq.top().second] = freq[i].second;
        pq.pop(); 
    }

    string ans = "";
    for (int i = 0; i < en.length(); i++ ){
        ans += mp1[en[i]];
    }
    // cout << ans << endl;

    return 0;
}
