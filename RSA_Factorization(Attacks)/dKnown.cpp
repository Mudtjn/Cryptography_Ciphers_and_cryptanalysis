#include<bits/stdc++.h>
#define int long long int
#define N 17
using namespace std;
time_t current_time = time(NULL);
int arr[N];

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

int power(int x, unsigned int y, int p)
{
    int res = 1; // Initialize result
    x = x % p;   // Update x if it is more than or
                 // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}


bool miillerTest(int d, int n)
{
    int a = 2 + rand() % (n - 4);

    int x = power(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }
    return false;
}


bool isPrime(int n, int k)
{
    // Corner cases
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++)
        if (!miillerTest(d, n))
            return false;

    return true;
}

int generatePrimes(){
    int p = 0;
    bool primeFound = false;
    while(!primeFound){
        p = 0; 
        for (int i = 1; i < N - 1; i++)
        {
            arr[i] = rand() % 2;
        }
        for (int i = 0; i < N; i++){
            p = 2 * p + arr[i]; 
        }
        primeFound = isPrime(p, 10); 
    }
    return p;
}

signed main(){

    srand((unsigned)time(NULL));
    int p, q;
    arr[0] = arr[N-1] = 1;

    p = generatePrimes();
    q = generatePrimes();
    while (q == p)
    {
        q = generatePrimes(); 
    }

    cout << "p is " << p << endl;
    cout << "q is " << q << endl;
    int e = generatePrimes();
    int phi_n = (p - 1) * (q - 1);
    while(phi_n%e==0){
        e = generatePrimes(); 
    }
    int n = p * q; 

    int d, garbage; 
    int ans = gcdExtended(e, phi_n, &d, &garbage);

    cout << "n is " << n << endl;
    cout << "e is " << e << endl;

    while(d<0){
        d += n;
    }
    cout << "d is " << d << endl;

    int r = phi_n;
    while(r%2==0){
        r /= 2; 
    }

    int oneFactor = 0; 
    bool factorFound = false;
    while(!factorFound){
        int w = 0;
        for (int i = 0; i < N ; i++){
            w = 2 * w + rand() % 2; 
        }
        w = w%n ; 
        if(w==0){
            for (int i = 0; i < N; i++)
            {
                w = 2 * w + rand() % 2;
            }
            w = w % n;
        }
        cout << w << endl;
        int g1, g2;
        int x = gcdExtended(w, n, &g1, &g2); 
        if(x>1 && x<n){
            oneFactor = x ; 
            factorFound = true; 
        }
        else{
            int v = power(w, r, n);
             
            if (v % n == 1)
            {
                continue; 
            }
            else{
                int v0 = 0;
                while(v%n!=1){
                    v0 = v;
                    v = power(v, 2, n); 
                }
                if(v0%n==n-1){
                    continue; 
                }
                else{
                    g1 = 0;
                    g2 = 0;
                    oneFactor = gcdExtended(v0 + 1, n, &g1, &g2);
                    factorFound = true; 
                }
            }
        }
    }

    cout << "one of the factors is " << oneFactor << endl;

    return 0; 
}
