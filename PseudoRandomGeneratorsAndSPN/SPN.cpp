#include <bits/stdc++.h>
using namespace std;
#define N 16

time_t current_time = time(NULL);

int sbox[] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
int permutation[] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
int revPermutation[N];
int revSBox[N];
int arr[N];

void sBoxFunc()
{

    for (int i = 0; i < N;)
    {
        int j = 0;
        int sum = 0;
        for (; j < 4; j++)
        {
            sum += arr[i + j] << (3 - j);
        }
        // cout << sum << endl;
        int val = sbox[sum];
        j = 0;
        for (; j < 4; j++)
        {
            arr[i + j] = (val & (1 << (3 - j))) >> (3 - j);
        }
        i += j;
    }
}

void revSBoxFunc()
{

    for (int i = 0; i < N;)
    {
        int j = 0;
        int sum = 0;
        for (; j < 4; j++)
        {
            sum += arr[i + j] << (3 - j);
        }
        // cout << sum << endl;
        int val = revSBox[sum];
        j = 0;
        for (; j < 4; j++)
        {
            arr[i + j] = (val & (1 << (3 - j))) >> (3 - j);
        }
        i += j;
    }
}

void permute()
{

    int cpArray[N];
    for (int i = 0; i < 16; i++)
    {
        cpArray[i] = arr[i];
    }

    for (int i = 0; i < 16; i++)
    {
        arr[permutation[i]] = cpArray[i];
    }
}

void revPermute()
{
    int cpArray[N];
    for (int i = 0; i < 16; i++)
    {
        cpArray[i] = arr[i];
    }

    for (int i = 0; i < 16; i++)
    {
        arr[revPermutation[i]] = cpArray[i];
    }
}

vector<int> keyScheduling(int it, int masterKey[])
{
    vector<int> key(16, 0);
    for (int i = 0; i < 16; i++)
    {
        key[i] = masterKey[(it + i) % 16];
    }
    return key;
}

int main()
{
    srand((unsigned)time(NULL));

    for (int i = 0; i < N; i++)
    {
        permutation[i]--;
    }

    for (int i = 0; i < N; i++)
    {
        revPermutation[permutation[i]] = i;
    }

    for (int i = 0; i < N; i++){
        revSBox[sbox[i]] = i;
    }

    string s = "/~";
    cout << s << endl;

    int it = 0;
    for (int i = 0; i < s.length() && it < 16; i++)
    {
        int x = int(s[i]);
        // cout << x << endl;
        for (int j = 7; j >= 0 && it < 16; j--)
        {
            arr[it++] = (x & (1 << j)) >> j;
        }
    }

    vector<vector<int>> keys;

    vector<int> arrOriginal;

    for (int i = 0; i < 16; i++)
    {
        cout << arr[i] << ' ';
        arrOriginal.push_back(arr[i]);
    }
    cout << endl;

    int masterKey[48];
    for (int i = 0; i < 48; i++)
    {
        masterKey[i] = rand() % 2;
    }

    // cout << "hello" << endl;

    for (int round = 0; round < 4; round++)
    {
        vector<int> key = keyScheduling(round, masterKey);
        keys.push_back(key);
        for (int i = 0; i < 16; i++)
        {
            arr[i] = arr[i] ^ key[i];
        }
        // cout << "iteratiion" << endl;
        sBoxFunc();
        permute();
    }
    // cout <   < "finish" << endl;

    // for (int i = 0; i < 16; i++)
    // {
    //     cout << arr[i] << ' ';
    // }
    // cout << endl;

    for (int round = 0; round < 4; round++)
    {
        // cout << "iteratiion" << endl;
        revPermute();
        revSBoxFunc();
        for (int i = 0; i < 16; i++)
        {
            arr[i] = arr[i] ^ keys[3 - round][i];
        }
    }

    for (int i = 0; i < 16; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}
