#include <bits/stdc++.h>
#define int long long int
#define vpi vector<pair<int, int>>
#define vvi vector<vector<int>>
#define vi vector<int>
#define p 10007
#define primeOne 10006
using namespace std;

time_t current_time = time(NULL);

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

bool luckCheck(int x, vi &primes)
{
    for (int i = 0; i < primes.size(); i++)
    {
        while (x % primes[i] == 0)
        {
            x /= primes[i];
        }
    }
    return x == 1;
}

void print(vvi &p1)
{
    for (auto v : p1)
    {
        for (int x : v)
        {
            cout << x << ' ';
        }
        cout << endl;
    }
    cout << "-------------------------------------" << endl;
}

int calcDeterminant(vector<vector<int>> matrix)
{
    // base case
    if (matrix.size() == 1)
        return matrix[0][0];

    // recursive case
    int ans = 0, n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        // generate submatrix
        vector<vector<int>> submatrix;
        for (int row = 1; row < n; row++)
        {
            vector<int> subrow;
            for (int col = 0; col < n; col++)
            {
                if (col != i)
                {
                    subrow.push_back(matrix[row][col]);
                }
            }
            submatrix.push_back(subrow);
        }
        if (i % 2 == 0)
            ans = (ans + matrix[0][i] * calcDeterminant(submatrix)) % primeOne;
        else
            ans = (ans - matrix[0][i] * calcDeterminant(submatrix)) % primeOne;
    }
    return ans;
}

vector<vector<int>> matrixInverse(vector<vector<int>> key, int det)
{
    vvi adjointMatrix(key.size(), vi(key[0].size()));
    for (int i = 0; i < key.size(); i++)
    {
        for (int j = 0; j < key[0].size(); j++)
        {
            vvi subMatrix;
            for (int k = 0; k < key.size(); k++)
            {
                vi subvec;
                for (int l = 0; l < key[0].size(); l++)
                {
                    if(i==k || j==l) continue; 
                    subvec.push_back(key[k][l]);
                }
                if (subvec.size())
                {
                    subMatrix.push_back(subvec);
                }
            }
            int det = calcDeterminant(subMatrix);
            det = (det + primeOne) % primeOne;
            // cout << det << endl;
            // cout << "HELLO" << endl;
            adjointMatrix[i][j] = (key[i][j]*det)%primeOne ;
            if((i+j)%2)
                adjointMatrix[i][j] *= -1; 
            adjointMatrix[i][j] = (adjointMatrix[i][j] + primeOne)%primeOne ; 
        }
    }

    for (int i = 0; i < adjointMatrix.size(); i++)
    {
        for (int j = i; j < adjointMatrix[i].size(); j++)
        {
            swap(adjointMatrix[i][j], adjointMatrix[j][i]);
        }
    }

    int detInverse , y_garbage ;
    gcdExtended(det, p, &detInverse, &y_garbage);

    detInverse = (detInverse + p)%p ;
    for (int i = 0; i < adjointMatrix.size(); i++){
        for (int j = 0; j < adjointMatrix[0].size(); j++){
            adjointMatrix[i][j] *= detInverse;
            adjointMatrix[i][j] = (adjointMatrix[i][j] + primeOne) % primeOne; 
        }
    }

    return adjointMatrix; 
}

vi matMul(vvi v1, vi v2){
    vi ans;
    for (int i = 0; i < v1.size(); i++){
        int s = 0; 
        for (int j = 0; j < v1[0].size(); j++)
        {
            s = (s + v1[i][j] * v2[j]) % primeOne; 
        }
        ans.push_back(s); 
    }
    return ans; 
}

signed main()
{
    srand((unsigned)time(NULL));
    int r = 19;
    int gen = 5, x;
    x = fastPow(gen, r);

    vi primes = {2, 3, 7};
    set<int> luckyExponents;

    vvi solveMatrix;
    for (int i = 1; i < p && luckyExponents.size() < primes.size(); i++)
    {
        int x1 = fastPow(gen, i) % p;
        if (luckCheck(x1, primes) && luckyExponents.find(i % (p - 1)) == luckyExponents.end())
        {
            cout << i << endl;
            cout << "x is " << x1 << endl;
            vi subans;
            for (int j = 0; j < primes.size(); j++)
            {
                int cnt = 0;
                while (x1 % primes[j] == 0)
                {
                    x1 /= primes[j];
                    cnt++;
                }
                subans.push_back(cnt);
            }
            subans.push_back(i % (p - 1));
            solveMatrix.push_back(subans);
            luckyExponents.insert(i % (p - 1));
        }
    }

    print(solveMatrix);
    vi vals;
    for (int i = 0; i < solveMatrix.size(); i++){
        vals.push_back(solveMatrix[i][solveMatrix.size()-1]);
        solveMatrix[i].pop_back();
    }

    vvi inverse = matrixInverse(solveMatrix, calcDeterminant(solveMatrix));
    print(inverse);

    vi ans = matMul(inverse, vals); 
    for(int x: ans){
        cout << x << ' '; 
    }
    cout << endl;

    vi primes2 = primes;
    primes2.push_back(gen);

    int s, product; 
    for (int i = 1; i < p; i++)
    {
        int x1 = fastPow(gen, i); 
        if (luckCheck((x*x1)%p, primes2)){
            cout << "FOUND " << i << endl;
            s = i, product = x1 ; 
            break;
        }
    }

    vi facNum;
    for (int i = 0; i < primes2.size(); i++)
    {
        int cnt = 0;
        while (product % primes2[i] == 0)
        {
            cnt++;
            product /= primes2[i]; 
        }
        facNum.push_back(cnt); 
    }

    int subsum = 0;
    for (int i = 0; i<primes.size();  i++){
        subsum = (subsum + primes[i] * facNum[i]) % primeOne; 
    }

    subsum = (subsum + facNum[facNum.size() - 1])%primeOne;

    subsum = (subsum - s + primeOne) % primeOne;

    cout << subsum << endl;

    return 0;
}
