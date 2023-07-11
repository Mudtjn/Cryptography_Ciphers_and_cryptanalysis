#include <bits/stdc++.h>
#define int long long int
#define vpi vector<pair<int, int>>
#define p 10007
using namespace std;

int fastPow(int g, int n)
{
    // base case
    if (n == 0)
        return 1;
    // recursive case
    int a = fastPow(g, n / 2) % p;
    int x = (a * a) % p;
    if (n % 2 == 0)
        return x;
    return (x * g) % p;
}

int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    // Update x and y using results of
    // recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

void print(vpi v)
{
    for (auto x : v)
    {
        cout << x.first << ' ' << x.second << endl;
    }
    cout << "--------------------------------------" << endl;
}

signed main()
{
    int r = 13;
    int gen = 5, x;
    x = fastPow(gen, r);

    int m = 0;
    for (; m * m <= p; m++)
    {
    };

    vpi v1, v2;
    for (int j = 0; j < m; j++)
    {
        v1.push_back({(fastPow(gen, m * j) + p) % p, j});
    }

    for (int j = 0; j < m; j++)
    {
        int gj_inverse, y_garbage = 0;
        gcdExtended(fastPow(gen, j), p, &gj_inverse, &y_garbage);
        gj_inverse = (gj_inverse + p) % p;
        v2.push_back({(x * gj_inverse) % p, j});
    }

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end()); 

    print(v1);
    print(v2);

    for (int i = 0; i < v1.size(); i++){
        for (int j = 0; j < v2.size(); j++){
            if(v1[i].first == v2[j].first){
                cout << (m * v1[i].second + v2[j].second) % (p - 1) << endl;
            }
        }
    }

    return 0;
}
