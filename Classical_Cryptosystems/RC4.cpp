#include <bits/stdc++.h>
using namespace std;

time_t current_time = time(NULL);

vector<int> keyScheduling(vector<int> &k)
{
    vector<int> s(256, 0);
    for (int i = 0; i < 256; i++)
        s[i] = i;
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + s[i] + k[i % k.size()]) % 256;
        swap(s[i], s[j]);
    }
    return s;
}

int main()
{

    srand((unsigned)time(NULL));
    freopen("msg_processed.txt", "r", stdin);
    string s;
    cin >> s; 

    string en = "";


// key generation algo
    vector<int> k(256, 0);
    for (int i = 0; i < 256; i++)
        k[i] = i;
    vector<int> z;
    int x1 = rand();
    x1 %= 10;
    // adding some randomnesss to string before permutation
    while (x1--)
    {
        int x2 = rand() % 256, x3 = rand() % 256;
        swap(k[x2], k[x3]);
    }

    vector<int> stream = keyScheduling(k);

// encryption
    int i = 0, j = 0;
    for (int l = 0; l < s.length(); l++)
    {
        i = (i + 1) % 256;
        j = (j + stream[i]) % 256;
        swap(stream[i], stream[j]);
        z.push_back(stream[(stream[i] + stream[j]) % 256] % 256);
        en += char(int(s[l]) ^ (z[z.size() - 1]));
    }


    // decryption
    string dec = "";
    for (int i = 0; i < en.length(); i++)
    {
        dec += char(int(en[i]) ^ z[i]);
    }

    if (dec == s)
    {
        cout << "STRING DECRYPTED CORRECTLY" << endl;
    }

    // taking input and encryption
    return 0;
}
