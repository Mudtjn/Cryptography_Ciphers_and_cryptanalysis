#include <bits/stdc++.h>
using namespace std;

time_t current_time = time(NULL);

vector<int> coPrimeNums = {3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
vector<int> numInverses;

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

void genInverses()
{
    for (int i = 0; i < coPrimeNums.size(); i++)
    {
        for (int j = 1; j < 26; j++)
        {
            if ((coPrimeNums[i] * j) % 26 == 1)
            {
                numInverses.push_back(j);
                break;
            }
        }
    }
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
            ans += matrix[0][i] * calcDeterminant(submatrix);
        else
            ans -= matrix[0][i] * calcDeterminant(submatrix);
    }
    return ans;
}

vector<vector<int>> multiplyMatrix(vector<vector<int>> m1, vector<vector<int>> m2)
{
    int r1 = m1.size(), c1 = m1[0].size();
    int r2 = m2.size(), c2 = m2[0].size();
    vector<vector<int>> ans(r1, vector<int>(c2, 0));
    if (c1 != r2)
    {
        cout << "CANNOT MULTIPLY MATRICES" << endl;
        return ans;
    }
    for (int i = 0; i < r1; i++)
    {
        // multiply each row with each column in the matrix
        for (int col = 0; col < c2; col++)
        {
            int subAns = 0;
            for (int l = 0; l < c1; l++)
            {
                subAns += (m1[i][l] * m2[l][col]);
            }
            ans[i][col] = subAns;
            while (ans[i][col] < 0)
            {
                ans[i][col] += 26;
            }
            ans[i][col] %= 26;
        }
    }
    return ans;
}

vector<vector<int>> genMatrixFromString(string &s, int r)
{
    int x = s.size();
    int rowSize = (x / r) + 1, colSize = r;
    if (x % r == 0)
    {
        rowSize--;
    }
    vector<vector<int>> message(rowSize, vector<int>(colSize, 0));
    int row = -1;
    int it = 0;
    for (int i = 0; i < x; i++)
    {
        if (i % r == 0)
        {
            it = 0;
            row++;
        }
        message[row][it] = s[i] - 'a';
        it++;
    }
    return message;
}

string encryptString(string &s, vector<vector<int>> &key, int r)
{

    vector<vector<int>> message = genMatrixFromString(s, r);

    vector<vector<int>> cipherText = multiplyMatrix(message, key);
    string cipher = "";
    int it = s.length();
    for (int i = 0; i < cipherText.size(); i++)
    {
        for (int j = 0; j < cipherText[0].size(); j++)
        {
            cipher += char(cipherText[i][j] + 'a');
        }
    }
    return cipher;
}

vector<vector<int>> matrixInverse(vector<vector<int>> key, int det)
{
    int n = key.size();
    vector<vector<int>> revMat(n, vector<int>(n, 0));

    // getting adjoint
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // generate matrix excluding row and col
            vector<vector<int>> sub(n - 1, vector<int>(n - 1, 0));
            int it1 = 0, it2 = 0;

            for (int i = 0; i < n; i++)
            {
                if (i != row)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (j != col)
                        {
                            sub[it1][it2] = key[i][j];
                            it2++;
                        }
                    }
                    it2 = 0;
                    it1++;
                }
            }

            int y = calcDeterminant(sub);
            if ((row + col) % 2)
                y *= -1;
            revMat[row][col] = y;
        }
    }

    // take transpose
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            swap(revMat[i][j], revMat[j][i]);
        }
    }

    // getting inverse of det
    int m = -1;
    for (int i = 0; i < coPrimeNums.size(); i++)
    {
        if (coPrimeNums[i] == det)
        {
            m = i;
            break;
        }
    }

    m = numInverses[m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            revMat[i][j] *= m;
            while (revMat[i][j] < 0)
                revMat[i][j] += 26;
            revMat[i][j] %= 26;
        }
    }

    return revMat;
}

int gcd(int a, int b)
{
    // base case
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int main()

{
    srand((unsigned)time(NULL));
    // get inverses for all nums
    genInverses();

    // generate matrix
    int r = 4;
    int x = 0;

// generate an matrix of integers such that the det of matrix is coprime with 26
    vector<vector<int>> key(r, vector<int>(r, 0));
    do
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < r; j++)
            {
                int y = rand() % 26;
                key[i][j] = y;
                // cout << key[i][j] << ' ';
            }
        }
        for (int i = 0; i < 2; i++)
        {
            int x1 = rand() % r, x2 = rand() % r;
            key[x1][x2] = 0;
        }

        x = calcDeterminant(key);
        x %= 26;
        while (x < 0)
        {
            x += 26;
        }
        if (gcd(x, 26) != 1)
        {
        }
    } while (gcd(x, 26) != 1);

    cout << "THE KEY IS: " << endl; 
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cout << key[i][j] << ' ';
        }
        cout << endl;
    }

// string input and processing string
    string s = "helloeveryoneone";
    removeSpaces(s);
    cout << s << endl;
   
// string encryption
    string cipher = encryptString(s, key, r);
    cout << "ENCRYPTED STRING IS :" << endl;
    for (int i = 0; i < s.length(); i++)
    {
        cout << cipher[i];
    }
    cout << endl;

// string decryption is similar to encryption just the difference is key inverse is mutlipied by cipher
    vector<vector<int>> revMat = matrixInverse(key, x);
    string decrypt = encryptString(cipher, revMat, r);

    cout << "STRING DECRYPTION IS :" << endl;
    for (int i = 0; i < s.length(); i++)
    {
        cout << decrypt[i];
    }
    cout << endl;

    // cryptanalysis
    // here the input size should be equal to r**2
    vector<vector<int>> mes = genMatrixFromString(s, r);
    vector<vector<int>> ciph = genMatrixFromString(cipher, r);
    vector<vector<int>> mesInverse = matrixInverse(mes, calcDeterminant(mes));
    vector<vector<int>> keyCheck = multiplyMatrix(mesInverse, ciph);

    return 0;
}
