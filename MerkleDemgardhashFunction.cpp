#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vector<int>>
#define N 16

vi sBox = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
vi perm = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
vi pad8(16, 0);
// mp construction for compression
// h(m(i-1), y(i-1)) = E(y(i-1), m(i-1)) ^ (m(i-1)^y(i-1))

void print(vi &v)
{
    for (int x : v)
        cout << x << ' ';
    cout << endl;
}
void sBoxFunc(vi &ans)
{
    for (int i = 0; i < N;)
    {
        int j = 0;
        int sum = 0;
        for (; j < 4; j++)
        {
            sum += ans[i + j] << (3 - j);
        }
        int val = sBox[sum];
        j = 0;
        for (; j < 4; j++)
        {
            ans[i + j] = (val & (1 << (3 - j))) >> (3 - j);
        }
        i += j;
    }
}

vi SPN(vi &ip, vi &masterKey)
{
    vi ans = ip;
    for (int i = 0; i < 4; i++)
    {
        vi key;
        for (int j = 0; j < N; j++)
        {
            key.push_back(masterKey[(i + j) % N]);
        }
        for (int j = 0; j < N; j++)
        {
            ans[j] = ans[j] ^ key[j];
        }
        // cout << "hello2" << endl;
        sBoxFunc(ans);
        vi cp = ans;
        for (int j = 0; j < N; j++)
        {
            // cout << "jscnksdvdsv" << endl; 
            ans[perm[j]] = cp[j];
        }
    }
    return ans;
}

vi MP(vi &m, vi &y)
{
    // cout << "hello MOP" << endl;
    vi ans = SPN(m, y);
    // vi ans(16, 0); 
    for (int i = 0; i < N; i++)
        ans[i] = (ans[i] ^ m[i] ^ y[i]);
    return ans;
}


vi helperFunc(int x)
{
    vi ans;
    for (int i = 7; i >= 0; i--)
    {
        ans.push_back((x & (1 << i)) >> i);
    }
    return ans;
}

int main()
{
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin); //file input.txt is opened in reading mode i.e "r"
    // freopen("output.txt","w",stdout);  //file output.txt is opened in writing mode i.e "w"
    // #endif

    for (int i = 0; i < N; i++){
        perm[i]--; 
    }
    // print(perm); 
    string ip = "THIS IS A HASH FUNCTION I HAVE USED MIYAGUCHI PRENEEL COMPRESSIOM";
    // string ip = "devjain"; 
    vi IV(16, 0);
    pad8[0] = 1;
    // pick two characters at a time make 16 bit vector
    vi ipBit;
    for (int i = 0; i < ip.length(); i++)
    {
        vi sub = helperFunc(int(ip[i]));
        ipBit.insert(ipBit.end(), sub.begin(), sub.end());
    }
    print(ipBit);
    int n = ipBit.size();
    // cout << n << endl;
    int it = 0;
    for (int i = 0; it < n; i++)
    {
        vi ans;
        if (i == 0)
        {
            ans.push_back(0);
        }
        else
        {
            ans.push_back(1);
        }
        for (; ans.size() < 16 && it < n; it++)
        {
            ans.push_back(ipBit[it]);
        }
        int cnt = 0;
        if (it == n && ans.size() < 16)
        {
            while (ans.size() != 16)
            {
                cnt++;
                ans.push_back(0);
            }
        }
        // print(IV); 
        vi IV1 = MP(ans, IV);
        IV = IV1 ; 
        // print(IV); 
        if (cnt > 0)
        {
            vi padding = helperFunc(cnt);
            // cout<<"PADDING IS: "; 
            // print(padding);
            for (int i = 0; i < padding.size(); i++)
            {
                pad8[i + 8] = padding[i];
            }
            // cout << "FINAL VECTOR IS : ";
            // print(pad8);
            vi IV1 = MP(pad8, IV);
            IV = IV1; 
        }
        // cout << it << endl;
    }

    print(IV);


    return 0;
}
